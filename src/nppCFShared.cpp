//this file is part of nppColdFusion
//Copyright (C)2011 Ben Bluemel ( ben1982@gmail.com )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "nppCFShared.h"
#include <vector>
#include <algorithm>

namespace nppColdFusionNS
{
using namespace AutoCompleteData;

// Meyers Singleton - thread-safe, no manual memory management
nppCFShared& nppCFShared::Instance()
{
    static nppCFShared instance;
    return instance;
}

    // Helper: build space-separated string from tags in a namespace
    static std::string buildTagList(NamespaceId ns_id, bool forautoc) {
        std::string result;
        if (static_cast<uint8_t>(ns_id) == 0 || static_cast<uint8_t>(ns_id) > sizeof(namespace_tags) / sizeof(NamespaceTags)) {
            return result;
        }
        const auto& nt = namespace_tags[static_cast<uint8_t>(ns_id) - 1];
        const char* sep = forautoc ? "?1 " : " ";
        for (size_t i = 0; i < nt.count; ++i) {
            uint16_t tag_idx = nt.indices[i];
            if (tag_idx < sizeof(all_tags) / sizeof(TagInfo)) {
                const TagInfo* tag = &all_tags[tag_idx];
                if (!result.empty()) result += sep;
                result += tag->name;
            }
        }
        return result;
    }

    // Helper: build space-separated string from keywords in a namespace
    static std::string buildKeywordList(NamespaceId ns_id, bool lowered, bool forautoc) {
        std::string result;
        if (static_cast<uint8_t>(ns_id) == 0 || static_cast<uint8_t>(ns_id) > sizeof(namespace_keyword_sets) / sizeof(NamespaceKeywordSets)) {
            return result;
        }
        const auto& nks = namespace_keyword_sets[static_cast<uint8_t>(ns_id) - 1];
        for (size_t i = 0; i < nks.count; ++i) {
            uint8_t set_id = nks.set_ids[i];
            if (set_id > 0 && set_id <= sizeof(keyword_sets) / sizeof(KeywordSet)) {
                const auto& ks = keyword_sets[set_id - 1];
                for (size_t j = 0; j < ks.count; ++j) {
                    if (!result.empty()) result += " ";
                    if (lowered) {
                        // Convert to lowercase - safe for signed char
                        std::string kw = ks.keywords[j];
                        std::transform(kw.begin(), kw.end(), kw.begin(),
                            [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
                        result += kw;
                    } else {
                        result += ks.keywords[j];
                    }
                }
            }
        }
        return result;
    }

    std::string_view DBNamespace::listAllTags(bool forautoc) {
        static thread_local std::string cached_tags[6]; // ns 1-5
        if (ns > 0 && ns <= 5) {
            if (cached_tags[ns].empty()) {
                cached_tags[ns] = buildTagList(namespace_id, forautoc);
            }
            return cached_tags[ns];
        }
        return "";
    }

    std::string_view DBNamespace::listAllKeywords(bool lowered, bool forautoc) {
        static thread_local std::string cached_keywords[6][2]; // ns 1-5, lowered/normal
        if (ns > 0 && ns <= 5) {
            int idx = lowered ? 1 : 0;
            if (cached_keywords[ns][idx].empty()) {
                cached_keywords[ns][idx] = buildKeywordList(namespace_id, lowered, forautoc);
            }
            return cached_keywords[ns][idx];
        }
        return "";
    }

    bool DBNamespace::isKeyword(const char* keyword) {
        size_t length = strnlen_s(keyword, 100);
        if (strstr(keyword, ".") != NULL || strstr(keyword, "'") != NULL) {
            return false;
        }

        if (this->ns > 0 && length > 0) {
            return isKeywordInNamespace(keyword, namespace_id);
        }
        return false;
    }

    bool DBNamespace::isTag(const char* tag) {
        size_t length = strnlen_s(tag, 100);

        if (length == 0 || strstr(tag, ".") != NULL || strstr(tag, "'") != NULL) {
            return false;
        }

        if (this->ns > 0) {
            if (this->isCustomTag(tag)) {
                return true;
            }
            return findTagInNamespace(tag, namespace_id) != nullptr;
        }
        return false;
    }

const char* DBNamespace::listTagAttributes(const char* tag, bool onlyrequired, bool hasFingerText, bool forautoc) {
        // Cache key includes namespace, tag name, onlyrequired, hasFingerText, forautoc
        // Use a map of string to string, but return a copy to avoid pointer invalidation on rehash
        // Since autocomplete is not performance-critical, we skip caching for safety
        
        if (this->ns > 0 && this->ns <= 5) {
            size_t attr_count = 0;
            const TagAttribute* attrs = findTagAttributes(tag, namespace_id, attr_count);
            if (attrs && attr_count > 0) {
                static thread_local std::string result; // thread-local buffer, reused per call
                result.clear();
                const char* extra = forautoc ? "?1" : "";
                
                // Collect attribute names and sort them alphabetically for proper autocomplete prefix matching
                std::vector<std::string> attr_names;
                attr_names.reserve(attr_count);
                for (size_t i = 0; i < attr_count; ++i) {
                    attr_names.push_back(attrs[i].name);
                }
                std::sort(attr_names.begin(), attr_names.end(), 
                    [](const std::string& a, const std::string& b) {
                        return _stricmp(a.c_str(), b.c_str()) < 0; // case-insensitive sort
                    });
                
                for (size_t i = 0; i < attr_names.size(); ++i) {
                    if (!result.empty()) {
                        result += " ";
                    }
                    result += attr_names[i];
                    if (onlyrequired) {
                        if (hasFingerText) {
                            result += "=\"\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"$[![]!]\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\"";
                        } else {
                            result += "=\"\"";
                        }
                    } else {
                        result += "=";
                    }
                    if (forautoc) {
                        result += extra;
                    }
                }
                return result.c_str();
            }
        }
        return "";
    }

    bool DBNamespace::tagHasAttribute(const char* tag, const char* attribute) {
        if (this->ns <= 0) return false;
        size_t attr_count = 0;
        const TagAttribute* attrs = findTagAttributes(tag, namespace_id, attr_count);
        if (!attrs) return false;
        for (size_t i = 0; i < attr_count; ++i) {
            if (strcmp(attrs[i].name, attribute) == 0) return true;
        }
        return false;
    }

    std::string_view DBNamespace::listAttributeValues(const char* tag, const char* attribute) {
        // Not implemented in new system - return empty
        return "";
    }

    unsigned int nppCFShared::registerLexer(LexerColdFusion* thisLexer) {
        lexers.push_back(thisLexer);
        return static_cast<unsigned int>(lexers.size() - 1);
    }

    bool nppCFShared::linkDocToLexer(unsigned int const& lexID, unsigned int const& docID) {
        if (lexID < lexers.size()) {
            doclinks[docID] = lexID;
            lexlinks[lexID] = docID;
            return true;
        }
        return false;
    }

    LexerColdFusion* nppCFShared::getLexerForDoc(unsigned int const& docID) {
        auto it = doclinks.find(docID);
        if (it != doclinks.end()) {
            unsigned int lexID = it->second;
            if (lexID < lexers.size() && lexers[lexID] != nullptr) {
                return lexers[lexID];
            }
        }
        return nullptr;
    }

    bool nppCFShared::unregisterLexer(unsigned int const& lexID, unsigned int const& docID) {
        if (lexID < lexers.size()) {
            doclinks.erase(docID);
            lexlinks.erase(lexID);
            // Mark lexer as unregistered (don't remove from vector to preserve indices)
            lexers[lexID] = nullptr;
            return true;
        }
        return false;
    }

    int BlockType::getKeywordState() const {
        return keywordstate;
    }

    void BlockType::updatefromlinestate(int linestate) {
        inBlock = (linestate >> bitshift) & bitmask;
    }

    void BlockType::updatelinestate(int& linestate) const {
        linestate = (linestate & ~(bitmask << bitshift)) | (inBlock << bitshift);
    }

    void BlockType::updateWordList(Lexilla::WordList& wl) {
        keywords.reset(new Lexilla::WordList);
        // Copy words from the provided WordList
        // Build a space-separated string from the source WordList
        std::string wordString;
        for (int i = 0; i < wl.Length(); ++i) {
            const char* word = wl.WordAt(i);
            if (word && word[0]) {
                if (!wordString.empty()) {
                    wordString += ' ';
                }
                wordString += word;
            }
        }
        if (!wordString.empty()) {
            keywords->Set(wordString.c_str());
        }
    }

    // CSSBlock
    bool CSSBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return sc.state == Styles::CSS_KEYWORD || sc.state == Styles::CSS_PROPERTY;
    }
    bool CSSBlock::hasKeyword(const char* keyword) {
        return keywords->InList(keyword);
    }

    // JSBlock
    bool JSBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return sc.state == Styles::JS_KEYWORD;
    }
    bool JSBlock::hasKeyword(const char* keyword) {
        return keywords->InList(keyword);
    }

    // CFScriptBlock
    bool CFScriptBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return sc.state == Styles::CF_FUNCTION || sc.state == Styles::CF_KEYWORD;
    }
    bool CFScriptBlock::hasKeyword(const char* keyword) {
        return keywords->InList(keyword);
    }
    bool CFScriptBlock::hasOperator(const char* operatorword) {
        return false;
    }
    bool CFScriptBlock::hasReservedWord(const char* reservedword) {
        return false;
    }

    // CFQueryBlock
    bool CFQueryBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return inBlock && (sc.state == Styles::SQL_KEYWORD || sc.state == Styles::_DEFAULT);
    }
    bool CFQueryBlock::hasKeyword(const char* keyword) {
        return keywords->InList(keyword);
    }

    // XPM arrays
    const char* tags_red[] = {
        /* columns rows colors chars-per-pixel */
        "16 16 32 1 ",
        "  c #DB4040",
        ". c #DF4848",
        "X c #E04D4D",
        "o c #E15454",
        "O c #E25C5C",
        "+ c #E56161",
        "@ c #E76666",
        "# c #E76A6A",
        "$ c #E86A6A",
        "% c #E97070",
        "& c #E87171",
        "* c #EB7070",
        "= c #EC7070",
        "- c #EC7474",
        "; c #EB7878",
        ": c #ED7A7A",
        "> c #EE7A7A",
        ", c #ED7F7F",
        "< c #EB8080",
        "1 c #EE8181",
        "2 c #EE8585",
        "3 c #ED8686",
        "4 c #EF8686",
        "5 c #EE8989",
        "6 c #F08484",
        "7 c #EF9494",
        "8 c #F29090",
        "9 c #F09696",
        "0 c #F19797",
        "q c #F19B9B",
        "w c #F29D9D",
        "e c None",
        /* pixels */
        "eeeeeeeeeeeeeeee",
        "eeeeeeeeeeeeeeee",
        "eeeeeeeeeeeeeeee",
        "eeeeeeeeeeeeeeee",
        "eeeeeeeeeeeeeeee",
        "eeeee-4ee8:eeeee",
        "eeee=9-ee6w=eeee",
        "eee49*eeee:9,eee",
        "ee<q<eeeeee,7*ee",
        "eee:5+eeee$5*eee",
        "eeeeX<oee@4Xeeee",
        "eeeee Oee$.eeeee",
        "eeeeeeeeeeeeeeee",
        "eeeeeeeeeeeeeeee",
        "eeeeeeeeeeeeeeee",
        "eeeeeeeeeeeeeeee"
    };

    const char* tags_blue[] = {
        /* columns rows colors chars-per-pixel */
        "16 16 34 1 ",
        "  c #3977D9",
        ". c #3C7DDC",
        "X c #3D80DC",
        "o c #4584DD",
        "O c #4B89DE",
        "+ c #488EE0",
        "@ c #4A92E2",
        "# c #4B95E2",
        "$ c #4F94E1",
        "% c #489BE5",
        "& c #4E9AE5",
        "* c #499EE5",
        "= c #4F9DE5",
        "- c #5199E3",
        "; c #5299E2",
        ": c #559FE5",
        "> c #4BA3E7",
        ", c #50A2E6",
        "< c #57A7E7",
        "1 c #58A5E6",
        "2 c #58A5E7",
        "3 c #58AAE7",
        "4 c #54AAE9",
        "5 c #5BABE9",
        "6 c #5EB3EB",
        "7 c #65A3E5",
        "8 c #68A8E7",
        "9 c #6AAAE8",
        "0 c #75B2E9",
        "q c #71B5EA",
        "w c #72B6EB",
        "e c #76BBEC",
        "r c #79B8EC",
        "t c None",
        /* pixels */
        "tttttttttttttttt",
        "tttttttttttttttt",
        "tttttttttttttttt",
        "tttttttttttttttt",
        "tttttttttttttttt",
        "ttttt*5tt6>ttttt",
        "tttt%q=tt4e%tttt",
        "ttt5q&tttt,q2ttt",
        "tt<r2tttttt20;tt",
        "ttt:9+tttt#9;ttt",
        "ttttX7ott@8Xtttt",
        "ttttt Ott$.ttttt",
        "tttttttttttttttt",
        "tttttttttttttttt",
        "tttttttttttttttt",
        "tttttttttttttttt"
    };

    const char* shield[] = {
        /* columns rows colors chars-per-pixel */
        "16 16 5 1 ",
        "  c #000000",
        ". c #FFFFFF",
        "X c #808080",
        "o c #C0C0C0",
        "+ c #FFFF00",
        /* pixels */
        "                ",
        "    XXXXXXXX    ",
        "   X........X   ",
        "  X..........X  ",
        " X............X ",
        " X..XX....XX..X ",
        " X..XX....XX..X ",
        " X............X ",
        " X..XXXXXXXX..X ",
        " X............X ",
        " X............X ",
        "  X..........X  ",
        "   X........X   ",
        "    XXXXXXXX    ",
        "                ",
        "                "
    };

    const char* tag_green[] = {
        /* columns rows colors chars-per-pixel */
        "16 16 4 1 ",
        "  c #000000",
        ". c #FFFFFF",
        "X c #00FF00",
        "o c #008000",
        /* pixels */
        "                ",
        "      XXXXXX    ",
        "     X......X   ",
        "    X........X  ",
        "   X........X   ",
        "  X........X    ",
        " X........X     ",
        " X........X     ",
        " X......XXXXX   ",
        " X........X     ",
        "  X........X    ",
        "   X........X   ",
        "    X........X  ",
        "     X......X   ",
        "      XXXXXX    ",
        "                ",
        "                "
    };

    const char* cf_func[] = {
        /* columns rows colors chars-per-pixel */
        "16 16 61 1 ",
        "  c #43A2C2",
        ". c #4AC6FF",
        "X c #4BC6FF",
        "o c #4DC7FD",
        "O c #4CC7FF",
        "+ c #4DC7FF",
        "@ c #4BC9FF",
        "# c #4DC8FF",
        "$ c #4FC9FF",
        "% c #4FCEFF",
        "& c #53C7F3",
        "* c #51C9FD",
        "= c #50C8FF",
        "- c #51C8FF",
        "; c #52CBFF",
        ": c #55CAFF",
        "> c #57CCFF",
        ", c #56CDFF",
        "< c #58CDFF",
        "1 c #59CEFF",
        "2 c #59CFFF",
        "3 c #5FCFFF",
        "4 c #5BD0FF",
        "5 c #5BD1FF",
        "6 c #5BD3FF",
        "7 c #5CD0FF",
        "8 c #5DD1FF",
        "9 c #5ED0FE",
        "0 c #61CDFE",
        "q c #61CFFF",
        "w c #60D2FF",
        "e c #62D3FF",
        "r c #65D3FE",
        "t c #61D5FF",
        "y c #6DD6FF",
        "u c #70D1FE",
        "i c #7DD7FE",
        "p c #7EDAFE",
        "a c #80D8F9",
        "s c #83D9FC",
        "d c #81D8FE",
        "f c #85D8FE",
        "g c #85DBFE",
        "h c #90DFFE",
        "j c #98E1FE",
        "k c #9EE0FC",
    };

} // namespace nppColdFusionNS