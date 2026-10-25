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
#include "nppColdFusion.h"
#include "AutoCompleteData.h"

namespace nppColdFusionNS
{
    class LexerColdFusion;
    class Status
    {
    public:
        bool tagClosing;
        bool tagOpening;
        int stateHistory[32];
        int lastState;
        bool preCFTagisHTMLTagOpening;
        char currentCFTag[100];
        char currentHTMLTag[100];
        char openTagsBuffer[512];
        int openTagsPositions[25];
        int currentopenTag;

        Status() {
            tagClosing = false;
            tagOpening = false;
            stateHistory[0] = 0;
            lastState = 0;
            preCFTagisHTMLTagOpening = false;
            currentopenTag = 0;
            currentCFTag[0] = '\0';
            currentHTMLTag[0] = '\0';
        }
        ~Status() {}
    };

    static const int B_CFQUERY = 0;
    static const int B_CFSCRIPT = 1;
    static const int B_JS = 2;
    static const int B_CSS = 3;

    class DBNamespace
    {
    protected:
        int ns;
        AutoCompleteData::NamespaceId namespace_id;
        
    public:
        DBNamespace() : ns(0), namespace_id(AutoCompleteData::NamespaceId::COUNT) { }
        DBNamespace(AutoCompleteData::NamespaceId nid) : ns(0), namespace_id(nid) { }

        const char* listAllTags(bool forautoc = false);
        const char* listAllKeywords(bool lowered = false, bool forautoc = false);

        bool isKeyword(const char* keyword);
        virtual bool isCustomTag(const char* tag) {
            return false;
        }

        bool isTag(const char* tag);
        const char* listTagAttributes(const char* tag, bool onlyrequired = false, bool hasFingerText = false, bool forautoc = false);

        bool tagHasAttribute(const char* tag, const char* attribute);
        const char* listAttributeValues(const char* tag, const char* attribute);
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

    template <typename Tx>
    class SafeScalar
    {
        Tx* Pointer;
    public:
        SafeScalar(Tx* Pointer) : Pointer(Pointer) { }
        ~SafeScalar() {
            delete Pointer;
        }
        operator Tx* () {
            return Pointer;
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
        static nppCFShared* Instance();

        bool nppReady;
        char* originallists[10];
        char* loweredlists[10];
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

        // void setDB(char* dbfile);  // REMOVED - no SQLite
        // void cleanupDB();          // REMOVED - no SQLite

    protected:
        nppCFShared() {}
        nppCFShared(const nppCFShared&);
        nppCFShared& operator= (const nppCFShared&);

    private:
        static nppCFShared* pinstance;
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

        boost::shared_ptr<Lexilla::WordList> keywords;

        int getKeywordState() const;

        virtual bool hasKeyword(char* /*s*/) {
            return false;
        }

        virtual bool hasOperator(char* /*s*/) {
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
            boost::shared_ptr<Lexilla::WordList> keywords(new Lexilla::WordList);
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
        bool hasKeyword(char* keyword) override;
    };

    class JSBlock : public BlockType
    {
    public:
        JSBlock() {
            bitshift = 18;
            keywordstate = Styles::JS_KEYWORD;
        }
        bool validateforkeyword(Lexilla::StyleContext& sc) override;
        bool hasKeyword(char* keyword) override;
    };

    class CFScriptBlock : public BlockType
    {
    public:
        CFScriptBlock() {
            bitshift = 17;
            keywordstate = Styles::CF_FUNCTION;
        }
        bool validateforkeyword(Lexilla::StyleContext& sc) override;
        bool hasKeyword(char* keyword) override;
        bool hasOperator(char* operatorword) override;
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
        bool hasKeyword(char* keyword) override;
    };

    /* XPM */
    static const char* tags_red[] = {
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

    /* XPM */
    static const char* tags_blue[] = {
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

    /* XPM */
    static const char* shield[] = {
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

    /* XPM */
    static const char* tag_green[] = {
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

    /* XPM */
    static const char* cf_func[] = {
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

#endif