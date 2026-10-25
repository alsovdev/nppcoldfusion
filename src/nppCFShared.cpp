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

namespace nppColdFusionNS
{
using namespace AutoCompleteData;

nppCFShared* nppCFShared::pinstance( 0 );

nppCFShared* nppCFShared::Instance() {
    if (!pinstance) {
        pinstance = new nppCFShared();
    }
    return pinstance;
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
                        // Convert to lowercase
                        std::string kw = ks.keywords[j];
                        std::transform(kw.begin(), kw.end(), kw.begin(), ::tolower);
                        result += kw;
                    } else {
                        result += ks.keywords[j];
                    }
                }
            }
        }
        return result;
    }

    const char* DBNamespace::listAllTags(bool forautoc) {
        static thread_local std::string cached_tags[6]; // ns 1-5
        if (ns > 0 && ns <= 5) {
            if (cached_tags[ns].empty()) {
                cached_tags[ns] = buildTagList(namespace_id, forautoc);
            }
            return cached_tags[ns].c_str();
        }
        return "";
    }

    const char* DBNamespace::listAllKeywords(bool lowered, bool forautoc) {
        static thread_local std::string cached_keywords[6][2]; // ns 1-5, lowered/normal
        if (ns > 0 && ns <= 5) {
            int idx = lowered ? 1 : 0;
            if (cached_keywords[ns][idx].empty()) {
                cached_keywords[ns][idx] = buildKeywordList(namespace_id, lowered, forautoc);
            }
            return cached_keywords[ns][idx].c_str();
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
        static thread_local std::string cached_attrs[6][2][2]; // ns, onlyrequired, hasFingerText
        // Simple cache key
        int onlyreq_idx = onlyrequired ? 1 : 0;
        int finger_idx = hasFingerText ? 1 : 0;
        
        if (this->ns > 0 && this->ns <= 5) {
            if (cached_attrs[ns][onlyreq_idx][finger_idx].empty()) {
                size_t attr_count = 0;
                const TagAttribute* attrs = findTagAttributes(tag, namespace_id, attr_count);
                if (attrs && attr_count > 0) {
                    const char* extra = forautoc ? "?1" : "";
                    for (size_t i = 0; i < attr_count; ++i) {
                        if (!cached_attrs[ns][onlyreq_idx][finger_idx].empty()) {
                            cached_attrs[ns][onlyreq_idx][finger_idx] += " ";
                        }
                        cached_attrs[ns][onlyreq_idx][finger_idx] += attrs[i].name;
                        if (onlyrequired) {
                            if (hasFingerText) {
                                cached_attrs[ns][onlyreq_idx][finger_idx] += "=\\\\\\\"$[![]!]\\\\\\\"";
                            } else {
                                cached_attrs[ns][onlyreq_idx][finger_idx] += "=\"\"";
                            }
                        } else {
                            cached_attrs[ns][onlyreq_idx][finger_idx] += "=";
                        }
                        if (forautoc) {
                            cached_attrs[ns][onlyreq_idx][finger_idx] += extra;
                        }
                    }
                }
            }
            return cached_attrs[ns][onlyreq_idx][finger_idx].c_str();
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

    const char* DBNamespace::listAttributeValues(const char* tag, const char* attribute) {
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
            if (lexID < lexers.size()) {
                return lexers[lexID];
            }
        }
        return nullptr;
    }

    bool nppCFShared::unregisterLexer(unsigned int const& lexID, unsigned int const& docID) {
        if (lexID < lexers.size()) {
            doclinks.erase(docID);
            lexlinks.erase(lexID);
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
        // Copy from shared wordlist if needed
    }

    // CSSBlock
    bool CSSBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return sc.state == Styles::CSS_KEYWORD || sc.state == Styles::CSS_PROPERTY;
    }
    bool CSSBlock::hasKeyword(char* keyword) {
        return keywords->InList(keyword);
    }

    // JSBlock
    bool JSBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return sc.state == Styles::JS_KEYWORD;
    }
    bool JSBlock::hasKeyword(char* keyword) {
        return keywords->InList(keyword);
    }

    // CFScriptBlock
    bool CFScriptBlock::validateforkeyword(Lexilla::StyleContext& sc, bool inCFSet) {
        return validateforkeyword(sc) && !inCFSet;
    }
    bool CFScriptBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return sc.state == Styles::CF_FUNCTION || sc.state == Styles::CF_KEYWORD;
    }
    bool CFScriptBlock::hasKeyword(char* keyword) {
        return keywords->InList(keyword);
    }
    bool CFScriptBlock::hasOperator(char* operatorword) {
        return false;
    }
    bool CFScriptBlock::hasReservedWord(const char* reservedword) {
        return false;
    }

    // CFQueryBlock
    bool CFQueryBlock::validateforkeyword(Lexilla::StyleContext& sc) {
        return sc.state == Styles::SQL_KEYWORD;
    }
    bool CFQueryBlock::hasKeyword(char* keyword) {
        return keywords->InList(keyword);
    }

} // namespace nppColdFusionNS