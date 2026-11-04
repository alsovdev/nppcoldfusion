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

#ifndef NPP_CF_SHARED
#define NPP_CF_SHARED

#include "nppLexCommon.h"
#include "core/NppMessager.h"
#include "core/SciMessager.h"
#include "AutoCompleteData.h"
#include "Constants.h"
#include <array>
#include <string_view>

namespace nppColdFusionNS
{
    class LexerColdFusion;
    class Status
    {
    public:
        bool tagClosing;
        bool tagOpening;
        std::array<int, Constants::MAX_STATE_HISTORY> stateHistory{};
        int lastState;
        bool preCFTagIsHTMLTagOpening;
        std::array<char, Constants::MAX_TAG_LENGTH> currentCFTag{};
        std::array<char, Constants::MAX_TAG_LENGTH> currentHTMLTag{};
        std::array<char, Constants::OPEN_TAGS_BUFFER_SIZE> openTagsBuffer{};
        std::array<int, Constants::MAX_OPEN_TAGS_POSITIONS> openTagsPositions{};
        int currentOpenTag;

        Status() {
            tagClosing = false;
            tagOpening = false;
            stateHistory[0] = 0;
            lastState = 0;
            preCFTagIsHTMLTagOpening = false;
            currentOpenTag = 0;
        }
        ~Status() {}
    };

    enum class BlockTypeId {
        CFQuery = 0,
        CFScript = 1,
        JS = 2,
        CSS = 3
    };

    class DBNamespace
    {
    protected:
        int ns;
        AutoCompleteData::NamespaceId namespace_id;
        
    public:
        DBNamespace() : ns(0), namespace_id(AutoCompleteData::NamespaceId::COUNT) { }
        DBNamespace(AutoCompleteData::NamespaceId nid) : ns(0), namespace_id(nid) { }

        std::string_view listAllTags(bool forautoc = false);
        std::string_view listAllKeywords(bool lowered = false, bool forautoc = false);

        bool isKeyword(const char* keyword);
        virtual bool isCustomTag(const char* tag) {
            return false;
        }

        bool isTag(const char* tag);
        const char* listTagAttributes(const char* tag, bool onlyrequired = false, bool hasFingerText = false, bool forautoc = false);

        bool tagHasAttribute(const char* tag, const char* attribute);
        std::string_view listAttributeValues(const char* tag, const char* attribute);
    };

    class CFNamespace : public DBNamespace
    {
    public:
        CFNamespace() : DBNamespace(AutoCompleteData::NamespaceId::COLDFUSION_9) {
            this->ns = 1;
        }
        bool isCustomTag(const char* tag) {
            // Lets take into account cf_ and cfx_
            if (tag[0] == ' ') {
                tag++;
            }
            if ((tag[0] == 'c' && tag[1] == 'f' && (tag[2] == '_' || (tag[2] == 'x' && tag[3] == '_'))) || strchr(tag, ':') != NULL) {
                return true;
            }
            return false;
        }
    };

    class HTMLNamespace : public DBNamespace
    {
    public:
        HTMLNamespace() : DBNamespace(AutoCompleteData::NamespaceId::HTML) {
            this->ns = 2;
        }
    };

    class SQLNamespace : public DBNamespace
    {
    public:
        SQLNamespace() : DBNamespace(AutoCompleteData::NamespaceId::SQL) {
            this->ns = 3;
        }
    };

    class JSNamespace : public DBNamespace
    {
    public:
        JSNamespace() : DBNamespace(AutoCompleteData::NamespaceId::JAVASCRIPT) {
            this->ns = 4;
        }
    };

    class CSSNamespace : public DBNamespace
    {
    public:
        CSSNamespace() : DBNamespace(AutoCompleteData::NamespaceId::CSS) {
            this->ns = 5;
        }
    };

    class BlockType;
    class nppCFShared
    {
    private:
        std::vector<LexerColdFusion*> lexers;
        typedef std::map<unsigned int, unsigned int> docLinks;
        typedef std::map<unsigned int, unsigned int> lexLinks;
        docLinks doclinks;
        lexLinks lexlinks;
    public:
        static nppCFShared& Instance();

        bool nppReady;
        char* originallists[31];
        char* loweredlists[31];
        TCHAR plugindir[MAX_PATH];
        std::vector<BlockType*> blocks;
        CNppMessager m_nppMsgr;
        Scintilla::IDocument* currentdoc;
        CFNamespace* coldfusionNS;
        HTMLNamespace* htmlNS;
        SQLNamespace* sqlNS;
        JSNamespace* javascriptNS;
        CSSNamespace* cssNS;
        bool isFingerTextInstalled;
        bool integrateWithFingerText;
        bool alwaysCompleteReqAttributes;
        bool completeCFsqltype;

        unsigned int registerLexer(LexerColdFusion* thisLexer); 

        bool linkDocToLexer(unsigned int const& lexID, unsigned int const& docID);

        LexerColdFusion* getLexerForDoc(unsigned int const& docID);

        bool unregisterLexer(unsigned int const& lexID, unsigned int const& docID);

    protected:
        nppCFShared() : coldfusionNS(nullptr), htmlNS(nullptr), sqlNS(nullptr), javascriptNS(nullptr), cssNS(nullptr) {
            // Initialize namespace objects
            coldfusionNS = new CFNamespace();
            htmlNS = new HTMLNamespace();
            sqlNS = new SQLNamespace();
            javascriptNS = new JSNamespace();
            cssNS = new CSSNamespace();
            nppReady = false;
            currentdoc = nullptr;
            isFingerTextInstalled = false;
            integrateWithFingerText = false;
            alwaysCompleteReqAttributes = false;
            completeCFsqltype = false;
            // Initialize string arrays to nullptr
            for (int i = 0; i < 31; ++i) {
                originallists[i] = nullptr;
                loweredlists[i] = nullptr;
            }
        }
        ~nppCFShared() {
            delete coldfusionNS;
            delete htmlNS;
            delete sqlNS;
            delete javascriptNS;
            delete cssNS;
            // Clean up originallists and loweredlists
            for (int i = 0; i < 31; ++i) {
                delete[] originallists[i];
                delete[] loweredlists[i];
            }
        }
        nppCFShared(const nppCFShared&);
        nppCFShared& operator= (const nppCFShared&);
    };

    class BlockType
    {
    protected:
        int bitshift;
        int bitmask;
        bool allowscommentblock;
        int keywordstate;
    public:
        int inBlock;

        virtual bool validateforkeyword(Lexilla::StyleContext& sc) = 0;

        bool validateforkeyword(Lexilla::StyleContext& sc, bool inCFSet) {
            return validateforkeyword(sc) && !inCFSet;
        }

        std::shared_ptr<Lexilla::WordList> keywords;

        int getKeywordState() const;

        virtual bool hasKeyword(const char* /*s*/) {
            return false;
        }

        virtual bool hasOperator(const char* /*s*/) {
            return false;
        }

        virtual bool hasReservedWord(const char* /*s*/) {
            return false;
        }

        void updatefromlinestate(int linestate);
        void updatelinestate(int& linestate) const;
        void updateWordList(Lexilla::WordList& wl);

        BlockType() {
            inBlock = 0;
            bitshift = 0;
            bitmask = 0x01;
            allowscommentblock = true;
            keywordstate = nppColdFusionNS::Styles::_DEFAULT;
            keywords = std::make_shared<Lexilla::WordList>();
        }
        virtual ~BlockType() {}
    };

    class CSSBlock : public BlockType
    {
    public:
        CSSBlock() {
            bitshift = 19;
            keywordstate = Styles::CSS_KEYWORD;
        }
        bool validateforkeyword(Lexilla::StyleContext& sc) override;
        bool hasKeyword(const char* keyword) override;
    };

    class JSBlock : public BlockType
    {
    public:
        JSBlock() {
            bitshift = 18;
            keywordstate = Styles::JS_KEYWORD;
        }
        bool validateforkeyword(Lexilla::StyleContext& sc) override;
        bool hasKeyword(const char* keyword) override;
    };

    class CFScriptBlock : public BlockType
    {
    public:
        CFScriptBlock() {
            bitshift = 17;
            keywordstate = Styles::CF_FUNCTION;
        }
        bool validateforkeyword(Lexilla::StyleContext& sc) override;
        bool hasKeyword(const char* keyword) override;
        bool hasOperator(const char* operatorword) override;
        bool hasReservedWord(const char* reservedword) override;
    };

    class CFQueryBlock : public BlockType
    {
    public:
        CFQueryBlock() {
            bitshift = 16;
            keywordstate = Styles::SQL_KEYWORD;
        }
        bool validateforkeyword(Lexilla::StyleContext& sc) override;
        bool hasKeyword(const char* keyword) override;
    };

    // XPM arrays moved to nppCFShared.cpp
    extern const char* tags_red[];
    extern const char* tags_blue[];
    extern const char* shield[];
    extern const char* tag_green[];
    extern const char* cf_func[];

} // namespace nppColdFusionNS

#endif