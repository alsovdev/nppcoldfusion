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

#include "core\NppMessager.h"
#include "core\SciMessager.h"
#include "nppColdFusion.h"

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
		sqlite3* database;
		char* allkeywords;
		char* alltags;
		bool keywordsset;
		bool tagsset;
	public:
		DBNamespace() { }
		DBNamespace(sqlite3* thedb);

		char* listAllTags();
		char* listAllTags(bool forautoc);

		char* listAllKeywords();
		char* listAllKeywords(bool lowered);
		char* listAllKeywords(bool lowered, bool forautoc);
			
		bool isKeyword(char* keyword);
		virtual bool isCustomTag(char* /* tag */) {
			return false;
		}

		bool isTag(char* tag);
		char* listTagAttributes(char* tag);
		char* listTagAttributes(char* tag, bool forautoc);
		char* listTagAttributes(char* tag, bool onlyrequired, bool hasFingerText);
		char* listTagAttributes(char* tag, bool onlyrequired, bool hasFingerText, bool forautoc);

		bool tagHasAttribute(char* tag, char* attribute);

		char* listAttributeValues(char* tag, char* attribute);
	};

	class CFNamespace : public DBNamespace
	{
	public:
		CFNamespace() {	}
		CFNamespace(sqlite3* thedb) : DBNamespace(thedb) {
			this->ns = 1;
		}
		bool isCustomTag(char* tag) {
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
		HTMLNamespace() {
		}
		HTMLNamespace(sqlite3* thedb) : DBNamespace(thedb) {
			this->ns = 2;
		}
	};

	class SQLNamespace : public DBNamespace
	{
	public:
		SQLNamespace() {
		}
		SQLNamespace(sqlite3* thedb) : DBNamespace(thedb) {
			this->ns = 3;
		}
	};

	class JSNamespace : public DBNamespace
	{
	public:
		JSNamespace() {
		}
		JSNamespace(sqlite3* thedb) : DBNamespace(thedb) {
			this->ns = 4;
		}
	};

	class CSSNamespace : public DBNamespace
	{
	public:
		CSSNamespace() {
		}
		CSSNamespace(sqlite3* thedb) : DBNamespace(thedb) {
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

		sqlite3* database;


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

		void setDB(char* dbfile);

		void cleanupDB();

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

		virtual bool validateforkeyword(Lexilla::StyleContext& sc, bool inCFSet) {// changed: byref
			return validateforkeyword(sc) && !inCFSet;
		}

		virtual bool validateforkeyword(Lexilla::StyleContext& /*sc*/) {// changed: byref
			return true;
		}

		virtual bool validateforkeyword() {
			return true;
		}

		boost::shared_ptr<Lexilla::WordList> keywords;

		int getKeywordState() const;

		virtual bool hasKeyword(char* /*s*/) {
			return false;//this->keywords->InList(s);
		}

		virtual bool hasOperator(char* /*s*/) {
			return false;//this->keywords->InList(s);
		}

		virtual bool hasReservedWord(char* /*s*/) {
			return false;//this->keywords->InList(s);
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
		virtual ~BlockType() {
			//delete keywords;
		}

	};

	class CSSBlock : public BlockType
	{
	public:
		CSSBlock() {
			bitshift = 19;
			keywordstate = Styles::CSS_KEYWORD;
		}
		bool validateforkeyword(Lexilla::StyleContext sc);
		bool hasKeyword(char* keyword);
	};

	class JSBlock : public BlockType
	{
	public:
		JSBlock() {
			bitshift = 18;
			keywordstate = Styles::JS_KEYWORD;
		}
		bool validateforkeyword(Lexilla::StyleContext sc);
		bool hasKeyword(char* keyword);
	};

	class CFScriptBlock : public BlockType
	{
	public:
		CFScriptBlock() {
			bitshift = 17;
			keywordstate = Styles::CF_FUNCTION;
		}
		bool validateforkeyword(Lexilla::StyleContext sc, bool inCFSet);

		bool validateforkeyword(Lexilla::StyleContext sc);

		bool hasKeyword(char* keyword);

		bool hasOperator(char* operatorword);

		bool hasReservedWord(const char* reservedword);
	};


	class CFQueryBlock : public BlockType
	{
	public:
		CFQueryBlock() {
			bitshift = 16;
			keywordstate = Styles::SQL_KEYWORD;
		}
		bool validateforkeyword(Lexilla::StyleContext sc);
		bool hasKeyword(char* keyword);
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
		"l c #AEE9FD",
		"z c #B4EAFD",
		"x c #BEE8FB",
		"c c #C4EBFD",
		"v c #D1EBF5",
		"b c #D7EBF4",
		"n c #D1EFFA",
		"m c #D2EFFC",
		"M c #D1F0FD",
		"N c #DAF0FA",
		"B c #EAEAEA",
		"V c #E8F2F7",
		"C c #E7F6FC",
		"Z c #FBFBFB",
		"A c None",
		/* pixels */
		"AAAAAAAAAAAAAAAA",
		"AAAAAAAAAAAAAAAA",
		"AAAAAAAAAAAAAAAA",
		"AAAAAAAAAAAAAAAA",
		"AAAAAAAAAvayAAAA",
		"AAAAAAAAnr49BAAA",
		"AAAAAAAAp2sbAAAA",
		"AA lzAAM22kVAAAA",
		"Atww9AAg-$$xAAAA",
		"9w&hjAC>$sfNAAAA",
		"49AAAAiXuZAAAAAA",
		"%>-w9:X-mAAAAAAA",
		"A@$$+X0cAAAAAAAA",
		"AAAAAAAAAAAAAAAA",
		"AAAAAAAAAAAAAAAA",
		"AAAAAAAAAAAAAAAA"
	};
	/* XPM */
	static const char* attr_blue[] = {
		/* columns rows colors chars-per-pixel */
		"16 16 76 1 ",
		"  c gray68",
		". c #B1B1B1",
		"X c #B4B4B4",
		"o c gray71",
		"O c #B6B6B6",
		"+ c #B7B7B7",
		"@ c gray72",
		"# c #B9B9B9",
		"$ c #BCBCBC",
		"% c gray74",
		"& c #8DCCF7",
		"* c #83CCFF",
		"= c #86CDFD",
		"- c #88CDFD",
		"; c #89CEFE",
		": c #89CEFF",
		"> c #8ACFFE",
		", c #8BCFFF",
		"< c #8CCFFF",
		"1 c #8ED0FF",
		"2 c #97D1FA",
		"3 c #97D2FD",
		"4 c #96D4FF",
		"5 c #98D4FF",
		"6 c #98D5FF",
		"7 c #9AD5FF",
		"8 c #9BD6FF",
		"9 c #9CD6FF",
		"0 c #9ED7FF",
		"q c #BAE1FD",
		"w c #BCE2FD",
		"e c #BDE3FD",
		"r c #C0C0C0",
		"t c #C3C3C3",
		"y c gray78",
		"u c #C8C8C8",
		"i c #CACACA",
		"p c #CBCBCB",
		"a c #CDCDCD",
		"s c #CECECE",
		"d c #D0D0D0",
		"f c gray82",
		"g c #D2D2D2",
		"h c LightGray",
		"j c gray83",
		"k c #D5D5D5",
		"l c #D7D7D7",
		"z c #D8D8D8",
		"x c gray85",
		"c c #DADADA",
		"v c gainsboro",
		"b c gray87",
		"n c #D3EBFB",
		"m c #D5ECFB",
		"M c #D6ECFB",
		"N c gray88",
		"B c #E2E2E2",
		"V c #E4E4E4",
		"C c gray90",
		"Z c #E7E7E7",
		"A c gray91",
		"S c #E9E9E9",
		"D c gray92",
		"F c #E7F3FB",
		"G c #E8F3FB",
		"H c #EAF5FD",
		"J c #F3F3F3",
		"K c gray97",
		"L c #F3F7F9",
		"P c #F7FBFD",
		"I c gray98",
		"U c #FBFBFB",
		"Y c #FBFCFD",
		"T c gray99",
		"R c #FDFDFD",
		"E c None",
		/* pixels */
		"kksssssEEEEEEEEE",
		"sRRURRVsEEEEEEEE",
		"sRNsNRRNsEEEEEEE",
		"sRsEiJRRN+EEEEEE",
		"sRbiiKGeRb+EEEEE",
		"sRRUKG,*wRx+EEEE",
		"sDRUF;45;wRx+EEE",
		"E+DRn*5051wRx+EE",
		"EE+DRm;500;qRl+E",
		"EEE+ARm;551&Yx+E",
		"EEEE+CRM;12Lx+EE",
		"EEEEE+CRm4Pz+EEE",
		"EEEEEE+NRRx+EEEE",
		"EEEEEEE+Nx+EEEEE",
		"EEEEEEEE++EEEEEE",
		"EEEEEEEEEEEEEEEE"
	};


	/* XPM */
	static const char* attr_red[] = {
		/* columns rows colors chars-per-pixel */
		"16 16 77 1 ",
		"  c gray68",
		". c #B1B1B1",
		"X c #B4B4B4",
		"o c gray71",
		"O c #B6B6B6",
		"+ c #B7B7B7",
		"@ c gray72",
		"# c #B9B9B9",
		"$ c #BCBCBC",
		"% c gray74",
		"& c #FA8987",
		"* c #FA8A87",
		"= c #F98D8A",
		"- c #F98E8C",
		"; c #FA8F8C",
		": c #FA8F8D",
		"> c #FA908D",
		", c #FA918E",
		"< c #FA928F",
		"1 c #F39391",
		"2 c #FA9492",
		"3 c #F59C9A",
		"4 c #FB9B99",
		"5 c #F99C9A",
		"6 c #FB9D9B",
		"7 c #FB9E9B",
		"8 c #FB9F9D",
		"9 c #FBA09E",
		"0 c #FBA19F",
		"q c #FBA3A1",
		"w c #FABDBC",
		"e c #FAC0BE",
		"r c #FAC1BF",
		"t c #C0C0C0",
		"y c #C3C3C3",
		"u c gray78",
		"i c #C8C8C8",
		"p c #CACACA",
		"a c #CBCBCB",
		"s c #CDCDCD",
		"d c #CECECE",
		"f c #D0D0D0",
		"g c gray82",
		"h c #D2D2D2",
		"j c LightGray",
		"k c gray83",
		"l c #D5D5D5",
		"z c #D7D7D7",
		"x c #D8D8D8",
		"c c gray85",
		"v c #DADADA",
		"b c gainsboro",
		"n c gray87",
		"m c #FAD6D5",
		"M c #FAD7D6",
		"N c #FAD8D8",
		"B c gray88",
		"V c #E2E2E2",
		"C c #E4E4E4",
		"Z c gray90",
		"A c #E7E7E7",
		"S c gray91",
		"D c #E9E9E9",
		"F c gray92",
		"G c #FBE8E8",
		"H c #FBE9E8",
		"J c #FCEBEB",
		"K c #F3F3F3",
		"L c gray97",
		"P c #F9F4F3",
		"I c #FDF7F7",
		"U c gray98",
		"Y c #FBFBFB",
		"T c #FDFBFB",
		"R c gray99",
		"E c #FDFDFD",
		"W c None",
		/* pixels */
		"lldddddWWWWWWWWW",
		"dEEYEEBdWWWWWWWW",
		"dEBdBEEBdWWWWWWW",
		"dEdWpKEEn+WWWWWW",
		"dEnppLHrEn+WWWWW",
		"dEEYLJ>&wEn+WWWW",
		"+FEYG-48>rEc+WWW",
		"W+FEm&6q0>rEc+WW",
		"WW+FEN>6q0>wEz+W",
		"WWW+AEN-6021Yc+W",
		"WWWW+ZEN=>3Pc+WW",
		"WWWWW+ZEM6Ic+WWW",
		"WWWWWW+BEEc+WWWW",
		"WWWWWWW+Bc+WWWWW",
		"WWWWWWWW++WWWWWW",
		"WWWWWWWWWWWWWWWW"
	};

	/* XPM */
	static const char* tag_green[] = {
		/* columns rows colors chars-per-pixel */
		"16 16 77 1 ",
		"  c #89AE67",
		". c #8AAF67",
		"X c #8DB06C",
		"o c #8EB16E",
		"O c #8FB26E",
		"+ c #8FB36F",
		"@ c #90B370",
		"# c #91B370",
		"$ c #92B472",
		"% c #93B275",
		"& c #94B674",
		"* c #9BBB7E",
		"= c #9CBA7F",
		"- c #9CBA81",
		"; c #9DBC80",
		": c #9EBC81",
		"> c #9FBE83",
		", c #A0BE84",
		"< c #A1BF86",
		"1 c gray68",
		"2 c #B1B1B1",
		"3 c #B4B4B4",
		"4 c gray71",
		"5 c #B6B6B6",
		"6 c #B7B7B7",
		"7 c gray72",
		"8 c #B9B9B9",
		"9 c #BCBCBC",
		"0 c gray74",
		"q c #A3C088",
		"w c #BDD1AA",
		"e c #C0D3AE",
		"r c #C1D3AF",
		"t c #C0C0C0",
		"y c #C3C3C3",
		"u c gray78",
		"i c #C8C8C8",
		"p c #CACACA",
		"a c #CBCBCB",
		"s c #CDCDCD",
		"d c #CECECE",
		"f c #D0D0D0",
		"g c gray82",
		"h c #D2D2D2",
		"j c LightGray",
		"k c gray83",
		"l c #D5D5D5",
		"z c #D7D7D7",
		"x c #D8D8D8",
		"c c gray85",
		"v c #DADADA",
		"b c gainsboro",
		"n c gray87",
		"m c #D6E2CA",
		"M c #D7E2CD",
		"N c #D8E3CE",
		"B c gray88",
		"V c #E2E2E2",
		"C c #E4E4E4",
		"Z c gray90",
		"A c #E7E7E7",
		"S c #E8EEE3",
		"D c #E9EFE3",
		"F c gray91",
		"G c #E9E9E9",
		"H c gray92",
		"J c #EBF1E6",
		"K c #F3F3F3",
		"L c #F4F5F2",
		"P c gray97",
		"I c #F7F9F6",
		"U c gray98",
		"Y c #FBFBFB",
		"T c #FBFCFA",
		"R c gray99",
		"E c #FDFDFD",
		"W c None",
		/* pixels */
		"lljjjdaWWWWWWWWW",
		"jEEYEECdWWWWWWWW",
		"jEBdBEEBpWWWWWWW",
		"dEdWpKEEBiWWWWWW",
		"dEnppPDrEnuWWWWW",
		"dEEYPJ@ eEctWWWW",
		"pHEYSO*>#eEc0WWW",
		"WuHEm =q,#eEc8WW",
		"WWtHEMO>q,+wEz4W",
		"WWWtAEM+>,&%Yc6W",
		"WWWW9ZENX#-Lc6WW",
		"WWWWW7ZEM=Ic6WWW",
		"WWWWWW4BEEc4WWWW",
		"WWWWWWW2Bc4WWWWW",
		"WWWWWWWW14WWWWWW",
		"WWWWWWWWWWWWWWWW"
	};

	/* XPM */
	static const char* shield[] = {
		/* columns rows colors chars-per-pixel */
		"16 16 59 1 ",
		"  c #D48F1D",
		". c #DA9B25",
		"X c #D5911F",
		"o c #E6B235",
		"O c #E5B033",
		"+ c #EBBC3C",
		"@ c #DC9F30",
		"# c #E2AB30",
		"$ c #DDA137",
		"% c #E1A82E",
		"& c #E1AA36",
		"* c #E8B838",
		"= c #EABB3B",
		"- c #EEC23C",
		"; c #F0C83D",
		": c #DEAA45",
		"> c #E1AA41",
		", c #E7B84D",
		"< c #E1AF51",
		"1 c #E7BA57",
		"2 c #EDC243",
		"3 c #F1CA49",
		"4 c #F2CD52",
		"5 c #F4D758",
		"6 c #F9E959",
		"7 c #F0CA61",
		"8 c #F5D766",
		"9 c #EBC876",
		"0 c #F5DA78",
		"q c #FFFE6F",
		"w c #F7E079",
		"e c #FEFC7A",
		"r c #EECE82",
		"t c #F4DA87",
		"y c #F2D895",
		"u c #F8E389",
		"i c #FDF789",
		"p c #F9E895",
		"a c #FCF296",
		"s c #F8E7A7",
		"d c #FEF8AB",
		"f c #FBEDBA",
		"g c #FAEEC6",
		"h c #FCF4CD",
		"j c #FDF7D7",
		"k c #FDF8E5",
		"l c #FEFCF2",
		"z c #DEA32B",
		"x c #D38C1B",
		"c c #D28B1A",
		"v c #E5B033",
		"b c #ECBE3D",
		"n c #DA9A24",
		"m c #DEA42B",
		"M c #E4AE32",
		"N c #DA9B25",
		"B c #DEA32A",
		"V c #D79421",
		"C c None",
		/* pixels */
		"CCCCCCCCCCCCCCCC",
		"CCCCCCC=;CCCCCCC",
		"C2-NbO*tt*OMN@-C",
		"C;p89skllks04t%C",
		"CC2kjjfkktfhh1cC",
		"CC*kuuukl044h&CC",
		"CC-kuutfs843g,NC",
		"CC*ku0taa83;g3NC",
		"CC*kw0wpa53-f&CC",
		"CC&js00ai5;-g$NC",
		"CCO9jtwai5;h0oCC",
		"CCC%rhiie6fy$zCC",
		"CCCC-ykdqjp4VCCC",
		"CCCCN*9hjy>MCCCC",
		"CCCCCcx-9XVNCCCC",
		"CCCCCCCNxCCCCCCC"
	};


	/*class NotABlock : public BlockType
	{
	public:
		NotABlock()
		{
		}
		bool validateforkeyword(StyleContext /*sc*//*) {
			return false;
		}
	};
	*/




}

#endif