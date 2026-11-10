//this file 
// part of nppColdFusion
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


#include "nppColdFusion.h"
#include "DllEntry.h"
#include "Constants.h"
#include <unordered_set>
#include <string_view> ///*** 
namespace sID = nppColdFusionNS::Styles;		//  All of the style state codes.
namespace lex = nppColdFusionNS;				//  This lexer's namespace.

using namespace nppColdFusionNS;
const Lexilla::CharacterSet setTagContinue(Lexilla::CharacterSet::setAlphaNum, ".-_:!#[", 0x80, true);

// Static tag sets for O(1) lookup instead of strstr
static const std::unordered_set<std::string_view> CF_SINGLE_TAGS = {
    "meta", "link", "img", "area", "br", "hr", "input",
    "cfabort", "cfajaximport", "cfajaxproxy", "cfapplet",
    "cfapplication", "cfargument", "cfassociate", "cfbreak",
    "cfcache", "cfcalendar", "cfchartdata", "cfchartseries",
    "cfcol", "cfcollection", "cfcontent", "cfcontinue",
    "cfcookie", "cfdbinfo", "cfdirectory", "cfdiv",
    "cfdump", "cferror", "cfexchangecalendar", "cfexchangeconnection",
    "cfexchangecontact", "cfexchangefilter", "cfexchangemail",
    "cfexchangetask", "cfexit", "cffeed", "cffile",
    "cfflush", "cfftp", "cfgridcolumn", "cfgridrow",
    "cfgridupdate", "cfheader", "cfhtmlhead", "cfhttp",
    "cfhttpparam", "cfimage", "cfimport", "cfinclude",
    "cfindex", "cfinput", "cfinsert", "cfinvoke",
    "cfinvokeargument", "cfldap", "cflocation", "cflog",
    "cfloginuser", "cflogout", "cfmailparam", "cfmodule",
    "cfntauthenticate", "cfobject", "cfobjectcache", "cfparam",
    "cfpdf", "cfpdfformparam", "cfpdfparam", "cfpop",
    "cfpresenter", "cfprint", "cfprocessingdirective", "cfprocparam",
    "cfprocresult", "cfproperty", "cfqueryparam", "cfregistry",
    "cfreport", "cfreportparam", "cfrethrow", "cfreturn",
    "cfschedule", "cfsearch", "cfset", "cfsetting",
    "cfsilent", "cfslider", "cfsprydataset", "cfstoredproc",
    "cftextinput", "cfthrow", "cftrace", "cftreeitem",
    "cfupdate", "cfwddx", "cfzip", "cfzipparam",
    "cfwebsocket", "cfclient", "cfpdfform", "cfpdfformparam", "cfpdfsubform"
};

static const std::unordered_set<std::string_view> HTML_SINGLE_TAGS = {
    "meta", "link", "img", "area", "br", "hr", "input"
};

static const std::unordered_set<std::string_view> CF_ELSE_TAGS = {
    "cfelse", "cfelseif"
};

static const std::unordered_set<std::string_view> CF_IF_ELSE_TAGS = {
    "cfif", "cfelse", "cfelseif"
};


namespace {
    const std::string LEXER_NAME_UTF8 = []() {
#ifdef UNICODE
        char buffer[64];
        wcstombs_s(nullptr, buffer, sizeof(buffer), nppColdFusionNS::LEXER_NAME, _TRUNCATE);
        return std::string(buffer);
#else
        return std::string(nppColdFusionNS::LEXER_NAME);
#endif
    }();
}

static const char* nppColdFusionNS::LexerName() {
    return LEXER_NAME_UTF8.c_str();
}

LexerColdFusion::LexerColdFusion() {
	cfs = &nppCFShared::Instance();
	isScriptCFC = false;
	hasDeterminedType = false;
	sharedid = cfs->registerLexer(this);
	inScriptComment = false;
	inScriptLineComment = false;
	componentPos = 0;
	currentDoc = 0;
	invalidPos = 0;
}

LexerColdFusion::~LexerColdFusion() {
	cfs->unregisterLexer(sharedid, currentDoc);
}


static inline bool IsAWordChar(const int ch)
{
	// Allow ASCII alphanum, underscore, dot + Unicode letters (including Cyrillic)
	// ch >= 0x80 includes most non-ASCII scripts (Cyrillic starts at 0x0400)
	if (ch < 0x80) {
		return isalnum(static_cast<unsigned char>(ch)) || ch == '.' || ch == '_';
	}
	// For Unicode, treat as word char if it's a letter (simplified: allow all >= 0x80 except control chars)
	// This allows Cyrillic, Greek, etc. to be part of identifiers
	return ch >= 0x80 && ch != 0xFFFD; // exclude replacement char
}

static inline int SafeMakeLowerCase(int ch)
{
	// Lexilla::MakeLowerCase only handles ASCII; for Unicode return as-is
	if (ch < 0x80) {
		return Lexilla::MakeLowerCase(ch);
	}
	return ch; // pass through Unicode unchanged
}


void SCI_METHOD LexerColdFusion::Lex(Sci_PositionU startPos, Sci_Position length, int initStyle, Scintilla::IDocument* pAccess)
{
	try {

		cfs->currentdoc = pAccess;

		Lexilla::LexAccessor astyler(pAccess);
		bool closingcomment = false;
		if (startPos == 0) {
			hasDeterminedType = false;
			isScriptCFC = false;
			inScriptComment = false;
			inScriptLineComment = false;
		}
		// Don't set any docs up in the startup phase, as it seems to cause issues.
		if (currentDoc == 0 && cfs->nppReady) {
			currentDoc = cfs->m_nppMsgr.SendNppMsg(NPPM_GETCURRENTBUFFERID);
			cfs->linkDocToLexer(sharedid, currentDoc);
		}
		if (!hasDeterminedType) {

			char s[10];
			char component[10] = { 'c', 'o', 'm', 'p', 'o', 'n', 'e', 'n', 't' };
			unsigned int wordlength = 0;
			for (unsigned int a = startPos; a <= startPos + length; a++) {
				int ch = astyler.SafeGetCharAt(a);
				int chNext = astyler.SafeGetCharAt(a + 1);
				closingcomment = false;
				if (inScriptComment) {
					if (ch == '*' && chNext == '/') {
						inScriptComment = false;
						closingcomment = true;
						wordlength = 0;
						a += 2;
					}
				}
				else if (inScriptLineComment) {
					if (ch == '\r' || ch == '\n') {
						inScriptLineComment = false;
						closingcomment = true;
						wordlength = 0;
						a++;
					}
				}
				else {
					if (ch == '/' && chNext == '*') {
						inScriptComment = true;
						isScriptCFC = true;
						a++;
					}
					else if (ch == '/' && chNext == '/') {
						inScriptLineComment = true;
						isScriptCFC = true;
						a++;
					}
					else {
						if (IsAWordChar(ch)) {
							s[wordlength] = SafeMakeLowerCase(ch); ///
							if (s[wordlength] == component[wordlength]) {
								wordlength++;
								if (wordlength >= 9) {
									s[wordlength] = '\0';
									if (strcmp(s, "component") == 0) {
										invalidPos = 0;
										componentPos = a;
										isScriptCFC = true;
										hasDeterminedType = true;
										break;
									}
									isScriptCFC = false;
									invalidPos = a;
									componentPos = 0;
									hasDeterminedType = true;
									break;
								}
							}
							else {
								isScriptCFC = false;
								invalidPos = a;
								componentPos = 0;
								hasDeterminedType = true;
								break;

							}
						}
						else if (Lexilla::IsASpace(ch)) {
							/* it's OK to have spaces */
						}
						else {
							isScriptCFC = false;
							invalidPos = a;
							componentPos = 0;
							hasDeterminedType = true;
							break;
						}
					}
				}
			}
		}
		else if (!hasDeterminedType || (isScriptCFC && (startPos <= componentPos)) || (!isScriptCFC && (startPos <= invalidPos))) {
			astyler.StartAt(0);
			return;
		}
		// Always colourise if we have a valid document, not just when type is determined
		// This ensures syntax highlighting works on startup with files already open
		Colourise_Doc(startPos, length, initStyle, astyler);
		astyler.Flush();
	}
	catch (...) {
		// Should not throw into caller as may be compiled with different compiler or options
		pAccess->SetErrorStatus(SC_STATUS_FAILURE);
	}
}
void SCI_METHOD LexerColdFusion::Fold(Sci_PositionU startPos, Sci_Position length, int initStyle, Scintilla::IDocument* pAccess)
{
	try {
		Lexilla::LexAccessor styler(pAccess);
		unsigned int endPos = startPos + length;
		int visibleChars = 0;
		int lineCurrent = styler.GetLine(startPos);
		int levelCurrent = SC_FOLDLEVELBASE;
		if (lineCurrent > 0)
			levelCurrent = styler.LevelAt(lineCurrent - 1) >> 16;
		int levelMinCurrent = levelCurrent;
		int levelNext = levelCurrent;
		char chNext = styler[startPos];
		char chPrev = '\0';
		char tagCF[100];

		int tagCFpos = 0;
		bool tagCFcomplete = false;
		bool tagCFOpening = false;
		bool tagCFClosing = false;

		char tagHTML[100];
		int tagHTMLpos = 0;
		bool tagHTMLcomplete = false;
		bool tagHTMLOpening = false;
		bool tagHTMLClosing = false;
		int styleNext = styler.StyleAt(startPos);
		int style = initStyle;
		for (unsigned int i = startPos; i < endPos; i++) {
			char ch = chNext;
			chNext = styler.SafeGetCharAt(i + 1);
			int stylePrev = style;
			style = styleNext;
			styleNext = styler.StyleAt(i + 1);
			bool atEOL = (ch == '\r' && chNext != '\n') || (ch == '\n');
			if (style == sID::CF_COMMENT) {
				if (!(stylePrev == sID::CF_COMMENT)) {
					levelNext++;
				}
				else if (!(styleNext == sID::CF_COMMENT) && !atEOL) {
					// Comments don't end at end of line and the next character may be unstyled.
					levelNext--;
				}
			}
			if (style == sID::_COMMENT) {
				if (!(stylePrev == sID::_COMMENT)) {
					levelNext++;
				}
				else if (!(styleNext == sID::_COMMENT) && !atEOL) {
					// Comments don't end at end of line and the next character may be unstyled.
					levelNext--;
				}
			}

			if ((ch == ' ' || ch == '\t')) {
				if (tagCFOpening && !tagCFcomplete) {
					tagCFcomplete = true;
				}
				else if (tagHTMLOpening && !tagHTMLcomplete) {
					tagHTMLcomplete = true;
				}
			}

			if (style == sID::CF_TAG) {
				if (ch == '<') {
					tagCFpos = 0;
					tagCFOpening = true;
					tagCFClosing = false;
					tagCFcomplete = false;
					if (chNext == '/') {
						tagCFClosing = true;
					}
				}
				else if (ch == ' ' || ch == '\t') {
					tagCFcomplete = true;
				}
				else if (ch == '>') {
				                tagCFcomplete = true;
				                tagCF[tagCFpos] = ' ';
				                tagCF[tagCFpos + 1] = '\0';
				                nppCFShared& ref = nppCFShared::Instance();
				                if (chPrev != '/' && CF_SINGLE_TAGS.find(tagCF) == CF_SINGLE_TAGS.end() && !cfs->coldfusionNS->isCustomTag(tagCF)) {
				                    if (tagCFClosing) {
							levelNext--;
						}
						else {
							if (CF_ELSE_TAGS.find(tagCF) != CF_ELSE_TAGS.end()) {
								levelNext--;
							}
							if (CF_IF_ELSE_TAGS.find(tagCF) != CF_IF_ELSE_TAGS.end()) {
								if (levelMinCurrent > levelNext) {
									levelMinCurrent = levelNext;
								}
							}
							levelNext++;
						}
					}
				}
				else {
					if (!tagCFcomplete && (IsAWordChar(ch) || ch == ':') && tagCFpos < 98) {
						tagCF[tagCFpos++] = tolower(ch);
					}
				}
			}

			if (style == sID::_TAG) {
				if (ch == '<') {
					tagHTMLpos = 0;
					tagHTMLOpening = true;
					tagHTMLClosing = false;
					tagHTMLcomplete = false;
					if (chNext == '/') {
						tagHTMLClosing = true;
					}
				}
				else if (ch == ' ' || ch == '\t') {
					tagHTMLcomplete = true;
				}
				else if (ch == '>') {
					tagHTMLcomplete = true;
					tagHTML[tagHTMLpos] = ' ';
					tagHTML[tagHTMLpos + 1] = '\0';
					if (chPrev != '/' && HTML_SINGLE_TAGS.find(tagHTML) == HTML_SINGLE_TAGS.end()) {
						if (tagHTMLClosing) {
							levelNext--;
						}
						else {
							levelNext++;
						}
					}
				}
				else {
					if (!tagHTMLcomplete && IsAWordChar(ch) && tagHTMLpos < 98) {
						tagHTML[tagHTMLpos++] = tolower(ch);
					}
				}
			}

			if (style == sID::_OPERATOR) {
				if (ch == '{') {
					// Measure the minimum before a '{' to allow
					// folding on "} else {"
					if (levelMinCurrent > levelNext) {
						levelMinCurrent = levelNext;
					}
					levelNext++;
				}
				else if (ch == '}') {
					levelNext--;
				}
			}
			if (!Lexilla::IsASpace(ch))
				visibleChars++;
			if (atEOL || (i == endPos - 1)) {
				int levelUse = levelCurrent;
				levelUse = levelMinCurrent;
				int lev = levelUse | levelNext << 16;
				//if (visibleChars == 0 && options.foldCompact)
				//	lev |= SC_FOLDLEVELWHITEFLAG;
				if (levelUse < levelNext)
					lev |= SC_FOLDLEVELHEADERFLAG;
				if (lev != styler.LevelAt(lineCurrent)) {
					styler.SetLevel(lineCurrent, lev);
				}
				lineCurrent++;
				levelCurrent = levelNext;
				levelMinCurrent = levelCurrent;
				if (atEOL && (i == static_cast<unsigned int>(styler.Length() - 1))) {
					// There is an empty line at end of file so give it same level and empty
					styler.SetLevel(lineCurrent, (levelCurrent | levelCurrent << 16) | SC_FOLDLEVELWHITEFLAG);
				}
				visibleChars = 0;
			}
			chPrev = ch;
		}

		styler.Flush();
	}
	catch (...) {
		// Should not throw into caller as may be compiled with different compiler or options
		pAccess->SetErrorStatus(SC_STATUS_FAILURE);
	}
}

//int SCI_METHOD LexerColdFusion::WordListSet(int n, const char* wl)
Sci_Position SCI_METHOD LexerColdFusion::WordListSet(int n, const char* wl)
{

	if (n < numWordLists) {
		auto wllength = strnlen_s(wl, 20480) + 1;
		char* loweredwl = new char[wllength];
		strcpy_s(loweredwl, wllength, wl);
		// Use SafeMakeLowerCase for Unicode safety (CharLowerA only handles ASCII)
		for (size_t i = 0; i < wllength - 1; ++i) {
			loweredwl[i] = static_cast<char>(SafeMakeLowerCase(static_cast<unsigned char>(loweredwl[i])));
		}
		cfs->originallists[n] = new char[wllength];
		cfs->loweredlists[n] = new char[wllength];
		strcpy_s(cfs->loweredlists[n], wllength, loweredwl);
		strcpy_s(cfs->originallists[n], wllength, wl);
		delete[] loweredwl;
		return 0;
	}

	return -1;

}

const char* SCI_METHOD LexerColdFusion::DescribeWordListSets()
{
	// Word list sets for Notepad++ XML config:
	// 0 = (unused)
	// 1 = CF tags/functions
	// 2 = (unused)
	// 3 = (unused)
	// 4 = CSS pseudo-classes
	// 5 = JavaScript keywords
	// 6 = SQL keywords
	// 7 = CSS keywords/properties
	return "CF Tags;CSS Pseudo-classes;JavaScript Keywords;SQL Keywords;CSS Keywords";
}



//  <---  Colourise --->
Status LexerColdFusion::Colourise_Doc(Sci_PositionU startPos, Sci_Position length, int initStyle, Lexilla::LexAccessor& styler, bool dostyling)
{
	Status status = Status();

	status.openTagsBuffer.fill(0);

	std::shared_ptr<BlockType> cfqueryblock = std::make_shared<CFQueryBlock>();
	std::shared_ptr<BlockType> cssblock = std::make_shared<CSSBlock>();
	std::shared_ptr<BlockType> jsblock = std::make_shared<JSBlock>();
	std::shared_ptr<BlockType> cfscriptblock = std::make_shared<CFScriptBlock>();

	using BlockId = BlockTypeId;

	std::vector<std::shared_ptr<BlockType>> blocks;

	blocks.push_back(cfqueryblock);
	blocks.push_back(cfscriptblock);
	blocks.push_back(jsblock);
	blocks.push_back(cssblock);

	// Populate BlockType keywords from stored word lists (set via WordListSet)
	// Index 1 = CF tags, 5 = JS keywords, 6 = SQL keywords, 7 = CSS keywords
	if (cfs->loweredlists[6]) {
		Lexilla::WordList wl;
		wl.Set(cfs->loweredlists[6]);
		cfqueryblock->updateWordList(wl);
	}
	if (cfs->loweredlists[5]) {
		Lexilla::WordList wl;
		wl.Set(cfs->loweredlists[5]);
		jsblock->updateWordList(wl);
	}
	if (cfs->loweredlists[7]) {
		Lexilla::WordList wl;
		wl.Set(cfs->loweredlists[7]);
		cssblock->updateWordList(wl);
	}
	if (cfs->loweredlists[1]) {
		Lexilla::WordList wl;
		wl.Set(cfs->loweredlists[1]);
		cfscriptblock->updateWordList(wl);
	}

	int currentLine = styler.GetLine(startPos);
	int linestate = 0;

	linestate = styler.GetLineState(currentLine - 1);

	/*incfset.value	= getstoredbitvalue( linestate, incfset );
	status.inCFSet			= incfset.value;
	*/
	// No scintilla window access in lexer - use IDocument* directly
	// outsideeditingrange optimization removed: it breaks startup with files already open
	// Just always colourise the full range
	Lexilla::SparseState<std::string> cfTagsNew(startPos);
	Lexilla::SparseState<std::string> htmlTagsNew(startPos);

	Lexilla::SparseState<bool> scriptBlocksNew(startPos);
	Lexilla::SparseState<bool> cfQueryBlocksNew(startPos);
	Lexilla::SparseState<bool> jsBlocksNew(startPos);
	Lexilla::SparseState<bool> cssBlocksNew(startPos);
	Lexilla::SparseState<bool> inCFSetsNew(startPos);
	Lexilla::SparseState<unsigned int> cfCommentDepthsNew(startPos);
	Lexilla::SparseState<unsigned int> cfOutputDepthsNew(startPos);

	unsigned int cfCommentDepth = cfCommentDepths.ValueAt(startPos);
	unsigned int cfOutputDepth = cfOutputDepths.ValueAt(startPos);

	bool inCFScript = scriptBlocks.ValueAt(startPos);
	bool inCFQuery = cfQueryBlocks.ValueAt(startPos);
	bool inJSBlock = jsBlocks.ValueAt(startPos);
	bool inCSSBlock = cssBlocks.ValueAt(startPos);
	bool inCFSet = inCFSets.ValueAt(startPos);


	Lexilla::StyleContext sc(startPos, length, initStyle, styler);


	PublicSparseState<CFBaseType> argumentsNew;
	PublicSparseState<CFBaseType> localsNew;
	PublicSparseState<unsigned int> bracketDepthsNew;


	CFUserFunction currentCFFunction = cfUserFunctions.ValueAt(startPos);
	unsigned int cfFuncsStartPos = startPos;
	unsigned int bracketDepth = 0;
	if (currentCFFunction.pos != 0) {
		cfFuncsStartPos = currentCFFunction.pos;
		bracketDepth = currentCFFunction.bracketDepths.ValueAt(startPos);
		bracketDepthsNew.setPositionFirst(startPos);
	}

	Lexilla::SparseState<CFUserFunction> cfUserFunctionsNew(cfFuncsStartPos);
	argumentsNew.setPositionFirst(cfFuncsStartPos);
	localsNew.setPositionFirst(cfFuncsStartPos);

	if (startPos > cfFuncsStartPos) {
		argumentsNew.Merge(currentCFFunction.arguments, startPos);
		localsNew.Merge(currentCFFunction.locals, startPos);
	}
	//
	while (sc.More()) {
		unsigned int loopstartpos = sc.currentPos;
		if (dostyling) {
			if (sc.atLineEnd) {
				// Update the line state, so it can be seen by next line
				currentLine = styler.GetLine(sc.currentPos);

				switch (sc.state) {
				case sID::CF_COMMENT:
					// Inside a cf comment, we set the line state
					linestate = styler.GetLineState(currentLine);
					styler.SetLineState(currentLine, linestate);
					break;
				default:
					// Reset the line state
					if (sc.state == sID::_COMMENT && (inCFScript || inJSBlock)) {
						sc.SetState(sID::_DEFAULT);
					}
					linestate = styler.GetLineState(currentLine);
					for (auto& thisblock : blocks) {
						thisblock->updatelinestate(linestate);

					}
					styler.SetLineState(currentLine, linestate);
					break;

				}
				currentLine++;
			}
		}
		// CFComments aren't allows in script blocks
		if (isScriptCFC) {
			inCFScript = true;
			scriptBlocksNew.Set(sc.currentPos, true);
		}
		else {
			if (sc.Match("<!---") && !inCFScript && sc.state != sID::CF_VALUE) {
				if (dostyling) {
					cfCommentDepth++;

					if (sc.state != sID::CF_COMMENT) {
						status.stateHistory[++status.lastState] = sc.state;
					}
					styler.SetLineState(currentLine, linestate);
					sc.SetState(sID::CF_COMMENT);

				}
				sc.Forward(5);
				if (dostyling) {
					cfCommentDepthsNew.Set(sc.currentPos, cfCommentDepth);
				}
				continue;
			}
			// check comment depth so we're not erasing cfcomments when one doesn't exist
			if (sc.Match("--->") && cfCommentDepth > 0 && sc.state == sID::CF_COMMENT) {
				sc.Forward(3);
				if (dostyling) {
					cfCommentDepth--;

					currentLine = styler.GetLine(sc.currentPos);
					cfCommentDepthsNew.Set(sc.currentPos, cfCommentDepth);
					if (cfCommentDepth == 0) {
						sc.ForwardSetState(status.stateHistory[status.lastState--]);
						// Back round we go just incase someone does ---><!---
						continue;
					}
				}
			}
			// We can skip styling of other stuff if we're in a cfcomment :)
			if (sc.state == sID::CF_COMMENT) {
				// ignore anything from here on as we're in a CF comment
				sc.Forward();
				continue;
			}
			// lets look for html comments
			if (sc.Match("<!--") && !inCFQuery && !inCFScript && sc.state != sID::CF_VALUE) {
				if (dostyling) {
					sc.SetState(sID::_COMMENT);
				}
				sc.Forward(4);
				continue;


			}
			if (sc.Match("-->") && sc.state == sID::_COMMENT && !inCFQuery && !inCFScript) {
				sc.Forward(3);
				if (dostyling) {
					sc.SetState(sID::_DEFAULT);
				}
				continue;
			}

			if (sc.Match("<![CDATA")) {
				sc.Forward(8);
			}

			// We allow HTML comments to be further processed, as it's only HTML that gets ignored
		}
		if (sc.Match('/', '*') && (inCFQuery || inCFScript || inJSBlock || inCSSBlock) && sc.state != sID::_SINGLESTRING && sc.state != sID::_DOUBLESTRING && sc.state != sID::_COMMENT) {
			if (dostyling && sc.state != sID::_COMMENTBLOCK) {
				status.stateHistory[++status.lastState] = sc.state;
				sc.SetState(sID::_COMMENTBLOCK);
			}
			sc.Forward(2);


		}
		if (sc.state == sID::_COMMENTBLOCK && sc.Match('*', '/')) {
			sc.Forward(2);
			if (dostyling) {
				sc.SetState(status.stateHistory[status.lastState--]);
			}
			continue;
		}

		if (sc.Match('#')) {
			// # gets treated in different ways depending on where it appears
			if (
				(sc.state != sID::_COMMENT && sc.state != sID::_COMMENTBLOCK) &&
				cfOutputDepth > 0 ||
				(sc.state == sID::_DOUBLESTRING && (status.stateHistory[status.lastState] == sID::CF_TAG)
					) ||
				sc.state == sID::CF_VALUE ||
				inCFQuery) {
				if (sc.chNext != '#') {
					//status.inCFVal = (sc.state == sID::CF_VALUE);
					if (dostyling) {
						if (!(sc.state == sID::CF_VALUE)) {
							status.stateHistory[++status.lastState] = sc.state;
							sc.SetState(sID::CF_VALUE);
							sc.Forward();
						}
						else {
							sc.Forward();
							sc.SetState(status.stateHistory[status.lastState--]);
						}
					}
				}
				else {
					// double hash doesn't change state	so move along!
					sc.Forward(2);
					continue;
				}
			}
		}

		if (sc.Match('\'') && sc.state != sID::_DOUBLESTRING) {
			if ((sc.state == sID::CF_TAG || sc.state == sID::_TAG || sc.state == sID::CF_VALUE || inCFQuery || inCFScript || inCFSet || inJSBlock || sc.state == sID::_SINGLESTRING) && sc.state != sID::_COMMENT && sc.state != sID::_COMMENTBLOCK) {
				if (sc.chNext != '\'') {
					if (dostyling) {
						if (sc.state == sID::_SINGLESTRING) {
							sc.Forward();
							sc.SetState(status.stateHistory[status.lastState--]);
							continue;
						}
						else {
							status.stateHistory[++status.lastState] = sc.state;
							sc.SetState(sID::_SINGLESTRING);
						}
					}
				}
				else {
					sc.Forward(2);
					continue;
				}
			}
		}

		if (sc.Match('"') && sc.state != sID::_SINGLESTRING) {
			if ((sc.state == sID::CF_TAG || sc.state == sID::_TAG || sc.state == sID::CF_VALUE || inCFQuery || inCFScript || inCFSet || inJSBlock || sc.state == sID::_DOUBLESTRING) && sc.state != sID::_COMMENT && sc.state != sID::_COMMENTBLOCK) {
				if (sc.chNext != '"') {
					if (dostyling) {
						if (sc.state != sID::_DOUBLESTRING) {
							status.stateHistory[++status.lastState] = sc.state;
							sc.SetState(sID::_DOUBLESTRING);
						}
						else {
							sc.ForwardSetState(status.stateHistory[status.lastState--]);
							continue;
						}
					}
				}
				else {
					sc.Forward(2);
					continue;
				}
			}
		}


		if ((sc.state != sID::_COMMENTBLOCK) && ((inCFQuery && sc.state != sID::CF_TAG) || (inCFScript && sc.state != sID::_COMMENT) || inCFSet || (inJSBlock && sc.state != sID::_COMMENT) || (inCSSBlock && sc.state != sID::_COMMENT))) {
			if ((inCFScript || inJSBlock) && sc.state != sID::_SINGLESTRING && sc.state != sID::_DOUBLESTRING) {
				if (sc.Match('/', '/')) {
					if (dostyling) {
						sc.SetState(sID::_COMMENT);
					}
				}
			}
			if (Lexilla::isoperator(sc.ch) && sc.state == sID::_DEFAULT && !((inCFSet || inCFQuery) && (sc.ch == '<' || sc.ch == '>')) && !(sc.ch == '<' && sc.chNext == '/') && !(sc.Match("<cf"))) {
				if (dostyling) {
					sc.SetState(sID::_OPERATOR);
				}
				if (currentCFFunction.pos > 0 && currentCFFunction.scripted) {

					switch (sc.ch) {

					case '(':
						if (bracketDepth == 0) {
							// Only interested if we haven't entered the scope
							int a = 1;
							int ch = sc.GetRelative(a);
							int prevch = '\0';
							char word[100];
							int wordpos = 0;
							bool exit = false;
							CFBaseType newArgument;
							while (!exit) {

								/* skip over strings */
								if (ch == '"') {
									while (ch != '"' && ch != '\0') {
										a++;
										ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
									}
									a++;
									ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
								}
								if (ch == '\'') {
									while (ch != '\'' && ch != '\0') {
										a++;
										ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
									}
									a++;
									ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
								}

								switch (ch) {
								case ',':
								case '=':
								case ')':
									// take last word
									if (wordpos > 0) {
										word[wordpos] = '\0';
										newArgument = CFBaseType();
										newArgument.pos = sc.currentPos + a;
										newArgument.setName(word);
										argumentsNew.Set(sc.currentPos + a, newArgument);
																				wordpos = 0;
									}

									if (ch == '=') {

										while (ch != ',' && ch != ')') {
											/* skip over strings */
											a++;
											ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
											if (ch == '"') {
												while (ch != '"' && ch != '\0') {
													a++;
													ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
												}
											}
											if (ch == '\'') {
												while (ch != '\'' && ch != '\0') {
													a++;
													ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
												}
											}
											if (ch == '\0') break;
										}
										a--;
									}
									if (ch == ')') {
										exit = true;
									}
									break;
								default:
									if (prevch == ' ' && ch != ' ') {
										// new word
																				wordpos = 0;
									}
									if (ch != ' ') {
										word[wordpos++] = ch;
									}
									prevch = ch;

								}
								a++;
								ch = styler.SafeGetCharAt(sc.currentPos + a, '\0');
								if (ch == '\0') {
									exit = true;
								}
								if (wordpos > 99) {
									exit = true;
								}
							}
						}
						break;

					case '{':
						bracketDepth++;
						bracketDepthsNew.Set(sc.currentPos, bracketDepth);
						break;
					case '}':
						if (bracketDepth > 0 && --bracketDepth == 0) {
							CFUserFunction newFunc(sc.currentPos);
							bracketDepthsNew.Set(sc.currentPos, bracketDepth);
							newFunc.pos = 0;
							const bool argumentsChanged = currentCFFunction.arguments.Merge(argumentsNew, sc.currentPos);
							const bool localsChanged = currentCFFunction.locals.Merge(localsNew, sc.currentPos);
														if (localsChanged) {
								currentCFFunction.dirtyLocals = true;
							}
							if (argumentsChanged) {
								currentCFFunction.dirtyArguments = true;
							}
							cfUserFunctionsNew.Set(currentCFFunction.pos, currentCFFunction);
							const bool cfUserFunctionsChanged = cfUserFunctions.Merge(cfUserFunctionsNew, sc.currentPos);
							if (argumentsChanged || localsChanged || cfUserFunctionsChanged) {
															}
							cfUserFunctionsNew.Set(sc.currentPos, newFunc);
							currentCFFunction = newFunc;
							argumentsNew = PublicSparseState<CFBaseType>();
							argumentsNew.setPositionFirst(sc.currentPos);
							localsNew = PublicSparseState<CFBaseType>();
							localsNew.setPositionFirst(sc.currentPos);
							bracketDepthsNew = PublicSparseState<unsigned int>();
							bracketDepthsNew.setPositionFirst(sc.currentPos);
						}
						break;
					}
				}
				if (dostyling) {
					sc.ForwardSetState(sID::_DEFAULT);
				}
				else {
					sc.Forward();
				}
			}
			else if (isdigit(static_cast <unsigned char> (sc.ch)) && sc.state == sID::_DEFAULT) { //  fixes crash on non-ASCII chars
				int max = 100;
				if ((startPos - sc.currentPos) + length < 100) {
					max = (startPos - sc.currentPos) + length;
				}
				int len = 0;
				for (int a = 0; a < max; a++) {
					char s = sc.GetRelative(a);
					if (!isdigit(static_cast<unsigned char> (s)) && s != '.') { // fixes crash on non-ASCII chars
						len = a;
						break;
					}
				}
				sc.SetState(sID::_NUMBER);
				sc.Forward(len);
				sc.SetState(sID::_DEFAULT);

			}
			else if (IsAWordChar(sc.ch)) {
				char s[100];
				int max = 100;
				if ((startPos - sc.currentPos) + length < 100) {
					max = (startPos - sc.currentPos) + length;
				}
				for (int a = 0; a < max; a++) {
							int rel = sc.GetRelative(a);
							if (rel != '.' && IsAWordChar(rel) || (inCSSBlock && rel == '-')) {
								s[a] = SafeMakeLowerCase(sc.GetRelative(a));
							}
					else {
						s[a] = '\0';
						bool handledkeyword = false;
						// temp override
						blocks[static_cast<size_t>(BlockId::CFScript)]->inBlock = inCFScript;
						blocks[static_cast<size_t>(BlockId::CFQuery)]->inBlock = inCFQuery;
						blocks[static_cast<size_t>(BlockId::JS)]->inBlock = inJSBlock;
						blocks[static_cast<size_t>(BlockId::CSS)]->inBlock = inCSSBlock;
						for (auto& thisblock : blocks) {
							if (thisblock->inBlock &&
								thisblock->validateforkeyword(sc, inCFSet)) {
								if (thisblock->hasReservedWord(s)) {
								                int statebefore = sc.state;
								                if (dostyling) {
								                    sc.SetState(sID::CFS_RESERVED);
								                }

								                if (a > 0) {
								                    sc.Forward(a - 1);
								                }
									
									if ((strcmp(s, "var") == 0 && currentCFFunction.pos > 0) || strcmp(s, "function") == 0) {
										
										/* Read Ahead to get name */
																				int j = 0;
										char sName[100];
										for (int b = 2; b < max; b++) {
											int ch = styler.SafeGetCharAt(sc.currentPos + b, '\0');

											if (ch != ' ' && ch != '\t') {
												sName[j++] = ch;
											}
											if (ch == ';' || ch == '=' || ch == '.' || ch == '(' || ch == '\0') {
												break;
											}
										}
										/*
										if (j > 0) {
											sName[--j] = '\0';
											if (strcmp(s, "function") == 0) {
												currentCFFunction.setName(sName);
												currentCFFunction.arguments.setPositionFirst(sc.currentPos);
												currentCFFunction.pos = sc.currentPos;
												// foldStart is the level before the fold begins, so when we check the other way we need
												currentCFFunction.scripted = true;

												argumentsNew.setPositionFirst(sc.currentPos);
												cfUserFunctionsNew.Set(currentCFFunction.pos, currentCFFunction);
											}
											else {  
												CFBaseType newLocal;
												newLocal.pos = sc.currentPos;
												newLocal.setName(sName);
												
												//*** THIS COMMENTED OUT PIECE (localsNew.Set to be precise) PROVOKED HANGING. 
												// Cannot see any difference though. Investigation required.
												localsNew.Set(sc.currentPos, newLocal);
												// need to instantly merge locals as they will be used.
												currentCFFunction.locals.Merge(localsNew, sc.currentPos);
												currentCFFunction.dirtyLocals = true;
												
											}
										}*/
									}
									
									
									if (dostyling) {
										sc.ForwardSetState(statebefore);
									}
									handledkeyword = true;
									break;
								}
								else 	if (thisblock->hasOperator(s)) {
												int statebefore = sc.state;
												if (dostyling) {
													sc.SetState(sID::_OPERATOR);
												}
												if (a > 0) {
													sc.Forward(a - 1);
												}

												if (dostyling) {
													sc.ForwardSetState(statebefore);
												}
												handledkeyword = true;
												break;
								}
								else if (thisblock->hasKeyword(s)) {
													int statebefore = sc.state;
													if (dostyling) {
														sc.SetState(thisblock->getKeywordState());
													}
													if (a > 0) {
														sc.Forward(a - 1);
													}
													if (dostyling) {
														sc.ForwardSetState(statebefore);
													}
													handledkeyword = true;
													break;
								}
								else if (currentCFFunction.pos > 0 && (inCFScript || inCFSet) && currentCFFunction.hasLocalVar(s)) {
												int statebefore = sc.state;
												if (dostyling) {
													sc.SetState(sID::LOCAL_VARIABLE);
												}
												if (a > 0) {
													sc.Forward(a - 1);
												}
												if (dostyling) {
													sc.ForwardSetState(statebefore);
												}
												handledkeyword = true;
												break;
								}
							}
						}
						if ((inCFSet) &&
							blocks[static_cast<size_t>(BlockId::CFScript)]->validateforkeyword(sc)) {

							if (strcmp(s, "var") == 0) {
											int statebefore = sc.state;
											if (dostyling) {
												sc.SetState(sID::CFS_RESERVED);
											}
											if (a > 0) {
												sc.Forward(a - 1);
											}

											if ((strcmp(s, "var") == 0 && currentCFFunction.pos > 0)) {
									/* Read Ahead to get name */
									bool inName = false;
									int j = 0;
									char sName[100];
									for (int b = 2; b < max; b++) {
										int ch = styler.SafeGetCharAt(sc.currentPos + b, '\0');

										if (ch != ' ' && ch != '\t') {
											sName[j++] = ch;
										}
										if (ch == ';' || ch == '=' || ch == '.' || ch == '(' || ch == '\0') {
											break;
										}
									}

									if (j > 0) {
										sName[--j] = '\0';
										CFBaseType newLocal;
										newLocal.pos = sc.currentPos;
										newLocal.setName(sName);
										localsNew.Set(sc.currentPos, newLocal);
										// need to instantly merge locals as they will be used.
										currentCFFunction.locals.Merge(localsNew, sc.currentPos);
										currentCFFunction.dirtyLocals = true;

									}
								}
								if (dostyling) {
									sc.ForwardSetState(statebefore);
								}
								handledkeyword = true;
								break;
							}
							else if (blocks[static_cast<size_t>(BlockId::CFScript)]->hasOperator(s)) {
										int statebefore = sc.state;
										if (dostyling) {
											sc.SetState(sID::_OPERATOR);
										}
										if (a > 0) {
											sc.Forward(a - 1);
										}
										handledkeyword = true;
										if (dostyling) {
											sc.ForwardSetState(statebefore);
										}
										break;
							}
							else if (blocks[static_cast<size_t>(BlockId::CFScript)]->hasKeyword(s)) {
										int statebefore = sc.state;
										if (dostyling) {
											sc.SetState(blocks[static_cast<size_t>(BlockId::CFScript)]->getKeywordState());
										}
										if (a > 0) {
											sc.Forward(a - 1);
										}
										handledkeyword = true;
										if (dostyling) {
											sc.ForwardSetState(statebefore);
										}
										break;
							}
							else if (currentCFFunction.pos > 0 && (inCFScript || inCFSet) && currentCFFunction.hasLocalVar(s)) {
											int statebefore = sc.state;
											if (dostyling) {
												sc.SetState(sID::LOCAL_VARIABLE);
											}
											if (a > 0) {
												sc.Forward(a - 1);
											}
											if (dostyling) {
												sc.ForwardSetState(statebefore);
											}
											handledkeyword = true;
											break;
							}
						}
						if (handledkeyword) {
							break;
						}
						else {
							sc.Forward(a);
							break;
						}
					}
				}
			}
		}

		if (sc.Match('<') && !inCFSet && sc.state != sID::CF_VALUE && sc.state != sID::_COMMENT && (sc.state != sID::_COMMENTBLOCK || inJSBlock)) {
				char s[100];
				char paddedText[102];

				int i = 0;
				paddedText[i] = ' ';

				if (status.tagOpening && status.currentHTMLTag[0] != '\0') {
					status.preCFTagIsHTMLTagOpening = true;
				}

				status.tagOpening = true;
				status.tagClosing = false;
				status.currentCFTag.fill(0);

				if (!status.preCFTagIsHTMLTagOpening) {
					status.currentHTMLTag.fill(0);
				}

				int max = 100;
			if ((startPos - sc.currentPos) + length < 100) {
				max = (startPos - sc.currentPos) + length;
			}

			for (int a = 0; a < max; a++) {
				int ch = sc.GetRelative(a + 1);
				if (setTagContinue.Contains(ch)) {
								s[i++] = SafeMakeLowerCase(ch);
					paddedText[i] = s[i - 1];
				}
				else {
					if (a == 0 && ch == '/') {
						status.tagClosing = true;
						status.tagOpening = false;
						continue;
					}
					//we're at a block

					s[i++] = '\0';
					paddedText[i] = ' ';
					paddedText[i + 1] = s[i - 1];
					bool scriptcheck = (!inCFScript || (strcmp(s, "cfscript") == 0 && status.tagClosing));
							bool jsscriptcheck = (!inJSBlock || (strcmp(s, "script") == 0 && status.tagClosing));

							// Use s (null-terminated) for tag lookup, not paddedText (which has trailing space)
							if (scriptcheck && (styler.StyleAt(sc.currentPos) == sID::CF_TAG || cfs->coldfusionNS->isTag(s))) {
						if (!status.tagClosing) {
							cfTagsNew.Set(sc.currentPos + strnlen_s(s, sizeof(s)) + 1, s);
						}
						strcpy_s(status.currentCFTag.data(), status.currentCFTag.size(), s);

						if (strcmp(s, "cffunction") == 0 && dostyling) {
							CFUserFunction newFunc(sc.currentPos);
							if (status.tagClosing && currentCFFunction.pos > 0) {
								newFunc.pos = 0;
								const bool argumentsChanged = currentCFFunction.arguments.Merge(argumentsNew, sc.currentPos);
								const bool localsChanged = currentCFFunction.locals.Merge(localsNew, sc.currentPos);
								if (localsChanged) {
									currentCFFunction.dirtyLocals = true;
								}
								if (argumentsChanged) {
									currentCFFunction.dirtyArguments = true;
								}
								cfUserFunctionsNew.Set(currentCFFunction.pos, currentCFFunction);
								const bool cfUserFunctionsChanged = cfUserFunctions.Merge(cfUserFunctionsNew, sc.currentPos);
								if (argumentsChanged || localsChanged || cfUserFunctionsChanged) {
																	}
							}
							cfUserFunctionsNew.Set(sc.currentPos, newFunc);
							currentCFFunction = newFunc;
							argumentsNew = PublicSparseState<CFBaseType>();
							argumentsNew.setPositionFirst(sc.currentPos);

							localsNew = PublicSparseState<CFBaseType>();
							localsNew.setPositionFirst(sc.currentPos);

						}

						if (dostyling) {
							status.stateHistory[++status.lastState] = sc.state;
							sc.SetState(sID::CF_TAG);
						}
						if ((strcmp(s, "cfset") == 0 || strcmp(s, "cfelseif") == 0 || strcmp(s, "cfreturn") == 0 || (strcmp(s, "cfif") == 0 && !status.tagClosing))) {
							inCFSet = true;
							inCFSetsNew.Set(sc.currentPos + strlen(s), true);
						}
					}
					else if (jsscriptcheck && scriptcheck && cfs->htmlNS->isTag(s) && !inCFQuery) {
						if (!status.tagClosing) {
							
							htmlTagsNew.Set(sc.currentPos + strnlen_s(s, sizeof(s)), s);
													}
						strcpy_s(status.currentHTMLTag.data(), status.currentHTMLTag.size(), s);
						if (dostyling) {
							if (!inJSBlock) {
								status.stateHistory[++status.lastState] = sc.state;
							}
							sc.SetState(sID::_TAG);
						}
					}

					sc.Forward(strnlen_s(s, sizeof(s)) + 1);
					if (!status.tagClosing) {
						if (inCFSet) {
							if (dostyling) {
								sc.SetState(sID::_DEFAULT);
							}
						}
					}

					break;
				}
			}
		}

		if (sc.state == sID::_TAG && !sc.Match('>') && dostyling && status.tagOpening && status.currentHTMLTag[0] != '\0' && sc.Match(' ') && !sc.Match(" #")) {
			char s[100];
			int i = 0;
			int max = 100;
			if ((startPos - sc.currentPos) + length < 100) {
				max = (startPos - sc.currentPos) + length;
			}
			for (int a = 0; a < max; a++) {
				int ch = sc.GetRelative(a + 1);
				if (setTagContinue.Contains(ch)) {
								s[i++] = SafeMakeLowerCase(ch);
				}
				else {
					//we're at a block

					s[i++] = '\0';

					if (cfs->htmlNS->tagHasAttribute(status.currentHTMLTag.data(), s)) {
						sc.SetState(sID::_ATTRIBUTE);
						sc.Forward(strnlen_s(s, 100));
						sc.ForwardSetState(sID::_TAG);

					}
					else {
						sc.SetState(sID::_ATTRIBUTEUNKNOWN);
						sc.Forward(strnlen_s(s, 100));
						sc.ForwardSetState(sID::_TAG);
					}
					break;
				}
			}
		}
		if (sc.state == sID::CF_TAG && !sc.Match('>') && dostyling && status.tagOpening && status.currentCFTag[0] != '\0' && (sc.Match(' ') || sc.Match('\t'))) {
			char s[100];
			int i = 0;
			int max = 100;
			if ((startPos - sc.currentPos) + length < 100) {
				max = (startPos - sc.currentPos) + length;
			}
			for (int a = 0; a < max; a++) {
				int ch = sc.GetRelative(a + 1);
				if (setTagContinue.Contains(ch)) {
								s[i++] = SafeMakeLowerCase(ch);
				}
				else {
					//we're at a block

					s[i++] = '\0';

					if (cfs->coldfusionNS->tagHasAttribute(status.currentCFTag.data(), s)) {

						if ((strcmp(status.currentCFTag.data(), "cffunction") == 0 || strcmp(status.currentCFTag.data(), "cfargument") == 0) && strcmp(s, "name") == 0) {
							/* Read Ahead to get name */
							bool inName = false;
							int j = 0;
							char sName[100];
							for (int b = a + 1; b < a + max; b++) {
								int ch = styler.SafeGetCharAt(sc.currentPos + b, '\0');

								if ((!inName && j > 0) || ch == '\0') {
									break;
								}

								if (ch == '#') {
									j = 0;
									break;
								}
								if (inName) {
									sName[j++] = ch;
								}
								if (ch == '"') {
									inName = !inName;
								}
							}
							if (j > 0) {
								sName[--j] = '\0';

								if (strcmp(status.currentCFTag.data(), "cffunction") == 0) {
									currentCFFunction.setName(sName);
									currentCFFunction.pos = sc.currentPos;
									currentCFFunction.arguments.setPositionFirst(sc.currentPos);
									currentCFFunction.scripted = false;
									argumentsNew.setPositionFirst(sc.currentPos);
									cfUserFunctionsNew.Set(currentCFFunction.pos, currentCFFunction);
								}
								else {
									CFBaseType newArgument;
									newArgument.pos = sc.currentPos;
									newArgument.setName(sName);
									argumentsNew.Set(sc.currentPos, newArgument);
																	}
							}
						}

						sc.SetState(sID::CF_ATTRIBUTE);
						sc.Forward(strnlen_s(s, 100));
						sc.ForwardSetState(sID::CF_TAG);

					}
					else {
						sc.SetState(sID::CF_ATTRIBUTEBAD);
						sc.Forward(strnlen_s(s, 100));
						sc.ForwardSetState(sID::CF_TAG);
					}
					break;
				}
			}
					}

		if (sc.Match('>') && (sc.state == sID::CF_TAG || sc.state == sID::_DEFAULT || sc.state == sID::_TAG)) {
			//if (/*&&*/ !status.inCFVal && !status.inSingleString  && !( status.inDoubleString && !status.inDoubleStringBeforeCFSet  /* && status.currentCFTag == '\0'*/ ) ) {
			if (inCFSet) {

				inCFSet = false;
				inCFSetsNew.Set(sc.currentPos, false);
				if (dostyling) {
					sc.SetState(sID::CF_TAG);
				}
			}

			int state = 0;
			if (dostyling) {
				state = sc.state;
			}
			else {
				state = styler.StyleAt(sc.currentPos);
			}

			if (state == sID::CF_TAG || (status.tagClosing && state == sID::_DEFAULT && strcmp(status.currentCFTag.data(), "cfscript") == 0)) {

					std::string currentTag = coldFusionTags.ValueAt(sc.currentPos);
					
					auto j = strnlen_s(status.currentCFTag.data(), status.currentCFTag.size());
						status.currentCFTag[j] = ' ';
						status.currentCFTag[j + 1] = '\0';
						if (CF_SINGLE_TAGS.find(std::string_view(status.currentCFTag.data())) == CF_SINGLE_TAGS.end()) {
									if (status.tagOpening) {
										if (!dostyling) {
											auto curlen = strnlen(status.openTagsBuffer.data(), status.openTagsBuffer.size());
											// Bounds check: prevent buffer overflow
											if (status.currentOpenTag < Constants::MAX_OPEN_TAGS_POSITIONS && curlen < status.openTagsBuffer.size()) {
												status.openTagsPositions[status.currentOpenTag] = curlen;
												strcpy_s(&status.openTagsBuffer[curlen], status.openTagsBuffer.size() - curlen, status.currentCFTag.data());
												status.currentOpenTag++;
											}
										}
									}
					if (status.tagClosing) {
						if (!dostyling) {
							if (status.currentOpenTag > 0) {
								status.currentOpenTag--;
								status.openTagsBuffer[status.openTagsPositions[status.currentOpenTag]] = '\0';
							}
						}
					}
				}
				status.currentCFTag[j] = '\0';
				if (dostyling) {
							if ((strcmp(status.currentCFTag.data(), "cfquery") == 0)) {
						if (status.tagOpening) {
							inCFQuery = true;
							cfQueryBlocksNew.Set(sc.currentPos, true);
																					sc.ForwardSetState(sID::_DEFAULT);
						}
						else if (status.tagClosing && inCFQuery) {
							inCFQuery = false;
							cfQueryBlocksNew.Set(sc.currentPos, false);
																												sc.ForwardSetState(status.stateHistory[status.lastState--]);
						}
					}
					else if ((strcmp(status.currentCFTag.data(), "cfoutput") == 0)) {
						if (status.tagOpening) {
							cfOutputDepth++;
																					cfOutputDepthsNew.Set(sc.currentPos, cfOutputDepth);
						}
						else if (status.tagClosing && cfOutputDepth > 0) {
							cfOutputDepth--;
							cfOutputDepthsNew.Set(sc.currentPos, cfOutputDepth);

						}
						sc.ForwardSetState(status.stateHistory[status.lastState--]);
					}
					else if ((strcmp(status.currentCFTag.data(), "cfscript") == 0)) {
						if (status.tagOpening) {
							inCFScript = true;
							scriptBlocksNew.Set(sc.currentPos, true);
							sc.ForwardSetState(sID::_DEFAULT);
						}
						else if (status.tagClosing && inCFScript) {
							inCFScript = false;
							scriptBlocksNew.Set(sc.currentPos + 1, false);
							sc.ForwardSetState(status.stateHistory[status.lastState--]);
						}
					}
					else {
						sc.ForwardSetState(status.stateHistory[status.lastState--]);
					}
				}
				if (status.tagClosing) {
					status.tagOpening = status.preCFTagIsHTMLTagOpening;
					status.currentCFTag[0] = '\0';
					status.tagClosing = false;
				}
				else {
					cfTagsNew.Set(sc.currentPos + 1, "");
					if (dostyling) {
						const bool rawStringsChanged = coldFusionTags.Merge(cfTagsNew, sc.currentPos + 1);
					}
				}
			}
			else if (state == sID::_TAG) {
				std::string currentTag = htmlTags.ValueAt(sc.currentPos);
				Lexilla::SparseState<std::string> htmlTagsNew(sc.currentPos);
				if (HTML_SINGLE_TAGS.find(std::string_view(status.currentHTMLTag.data())) == HTML_SINGLE_TAGS.end()) {
								if (status.tagOpening) {
									if (!dostyling) {
										auto curlen = strnlen(status.openTagsBuffer.data(), status.openTagsBuffer.size());
										// Bounds check: prevent buffer overflow
										if (status.currentOpenTag < Constants::MAX_OPEN_TAGS_POSITIONS && curlen < status.openTagsBuffer.size()) {
											status.openTagsPositions[status.currentOpenTag] = curlen;
											strcpy_s(&status.openTagsBuffer[curlen], status.openTagsBuffer.size() - curlen, status.currentHTMLTag.data());
											status.currentOpenTag++;
										}
									}
								}
					if (status.tagClosing && !status.tagOpening) {
						if (!dostyling) {
							status.currentOpenTag--;
							if (status.currentOpenTag > 0) {
								status.openTagsBuffer[status.openTagsPositions[status.currentOpenTag]] = '\0';
							}
						}
					}
				}
				if (dostyling) {
					if ((strcmp(status.currentHTMLTag.data(), "script") == 0)) {
						if (status.tagOpening) {
							inJSBlock = true;
							jsBlocksNew.Set(sc.currentPos, true);
														//blocks[static_cast<size_t>(BlockId::JS)]->updatelinestate( linestate );
							sc.ForwardSetState(sID::_DEFAULT);
						}
						else if (status.tagClosing && inJSBlock) {

							inJSBlock = false;
							jsBlocksNew.Set(sc.currentPos, false);

							sc.ForwardSetState(status.stateHistory[status.lastState--]);
						}
					}
					else 	if ((strcmp(status.currentHTMLTag.data(), "style") == 0)) {
						if (status.tagOpening) {
							inCSSBlock = true;
							cssBlocksNew.Set(sc.currentPos, true);
							sc.ForwardSetState(sID::_DEFAULT);
						}
						else if (status.tagClosing && blocks[static_cast<size_t>(BlockId::CSS)]->inBlock) {
							inCSSBlock = false;
							cssBlocksNew.Set(sc.currentPos, false);
							sc.ForwardSetState(status.stateHistory[status.lastState--]);
						}
					}
					else {
						sc.ForwardSetState(status.stateHistory[status.lastState--]);
					}
				}
				if (status.tagOpening && !status.tagClosing) {
					htmlTagsNew.Set(sc.currentPos + 1, "");
					//const bool rawStringsChanged = htmlTags.Merge(rawSTNew, sc.currentPos+1);
				}
			}
		}

		// Lexer hasn't done anything in this loop move the cursor forward so
		// we don't get stuck in an infinite loop.
		if (loopstartpos == sc.currentPos) {
			sc.Forward();
		}
	}
	if (dostyling) {
		bool cfTagsChanged = false;
		if (cfTagsNew.size() > 0) {
			cfTagsChanged = coldFusionTags.Merge(cfTagsNew, sc.currentPos);
		}
		const bool htmlTagsChanged = htmlTags.Merge(htmlTagsNew, sc.currentPos);
		const bool scriptBlocksChanged = scriptBlocks.Merge(scriptBlocksNew, sc.currentPos);
		const bool cfQueryBlocksChanged = cfQueryBlocks.Merge(cfQueryBlocksNew, sc.currentPos);
		const bool jsBlocksChanged = jsBlocks.Merge(jsBlocksNew, sc.currentPos);
		const bool cssBlocksChanged = cssBlocks.Merge(cssBlocksNew, sc.currentPos);

		const bool cfCommentDepthsChanged = cfCommentDepths.Merge(cfCommentDepthsNew, sc.currentPos);
		const bool cfOutputDepthsChanged = cfOutputDepths.Merge(cfOutputDepthsNew, sc.currentPos);
		const bool cfinCFSetsChanged = inCFSets.Merge(inCFSetsNew, sc.currentPos);

		bool cfArgumentsChanged = false;
		bool cfLocalsChanged = false;
		bool bracketDepthsChanged = false;
		if (currentCFFunction.pos > 0) {
			cfArgumentsChanged = currentCFFunction.arguments.Merge(argumentsNew, sc.currentPos);
			if (cfArgumentsChanged) {
				currentCFFunction.dirtyArguments = true;
			}
			cfLocalsChanged = currentCFFunction.locals.Merge(localsNew, sc.currentPos);
			if (cfLocalsChanged) {
				currentCFFunction.dirtyLocals = true;
			}
			if (currentCFFunction.scripted) {
				bracketDepthsChanged = currentCFFunction.bracketDepths.Merge(bracketDepthsNew, sc.currentPos);
			}

			cfUserFunctionsNew.Set(currentCFFunction.pos, currentCFFunction);
		}
		const bool cfUserFunctionsChanged = cfUserFunctions.Merge(cfUserFunctionsNew, sc.currentPos);

		if (cfTagsChanged || htmlTagsChanged || scriptBlocksChanged || cfQueryBlocksChanged || jsBlocksChanged || cssBlocksChanged || cfCommentDepthsChanged || cfOutputDepthsChanged || cfLocalsChanged) {
			styler.ChangeLexerState(startPos, startPos + length);
		}
		sc.Complete();
	}
	else {

	}
	return status;
}


int SCI_METHOD LexerColdFusion::NamedStyles() {
    return 24; // Highest style ID + 1 (0-23, matching XML styleIDs with gaps)
}

const char* SCI_METHOD LexerColdFusion::NameOfStyle(int style) {
    // Must match nppColdFusion.xml WordsStyle name attributes exactly
    // Indexed by styleID (0-23), gaps return empty string
    static const char* styleNames[] = {
        "DEFAULT",           // 0
        "TAG",               // 1
        "CFTAG",             // 2
        "ATTRIBUTE",         // 3
        "ATTRIBUTEUNKNOWN",  // 4
        "NUMBER",            // 5
        "DOUBLESTRING",      // 6
        "SINGLESTRING",      // 7
        "OPERATOR",          // 8
        "COMMENT",           // 9
        "COMMENTBLOCK",      // 10
        "",                  // 11 (gap)
        "CFCOMMENT",         // 12
        "CFVALUE",           // 13
        "CFFUNCTION",        // 14
        "CFATTRIBUTE",       // 15
        "CFATTRIBUTEBAD",    // 16
        "LOCALVARS",         // 17
        "",                  // 18 (gap)
        "CFSRESERVED",       // 19
        "",                  // 20 (gap)
        "SQLKEYWORDS",       // 21
        "JSKEYWORDS",        // 22
        "CSSKEYWORDS",       // 23
    };
    if (style >= 0 && style < 24) return styleNames[style];
    return "";
}

const char* SCI_METHOD LexerColdFusion::DescriptionOfStyle(int style) {
    static const char* styleDescs[] = {
        "Default text",           // 0 DEFAULT
        "HTML tag",               // 1 TAG
        "CFML tag",               // 2 CFTAG
        "Attribute name",         // 3 ATTRIBUTE
        "Unknown attribute",      // 4 ATTRIBUTEUNKNOWN
        "Number",                 // 5 NUMBER
        "Double-quoted string",   // 6 DOUBLESTRING
        "Single-quoted string",   // 7 SINGLESTRING
        "Operator",               // 8 OPERATOR
        "Comment",                // 9 COMMENT
        "Block comment",          // 10 COMMENTBLOCK
        "",                       // 11 (gap)
        "CFML comment",           // 12 CFCOMMENT
        "CFML value",             // 13 CFVALUE
        "CFML function",          // 14 CFFUNCTION
        "CFML attribute",         // 15 CFATTRIBUTE
        "Bad CFML attribute",     // 16 CFATTRIBUTEBAD
        "Local variables",        // 17 LOCALVARS
        "",                       // 18 (gap)
        "CFML reserved",          // 19 CFSRESERVED
        "",                       // 20 (gap)
        "SQL keywords",           // 21 SQLKEYWORDS
        "JavaScript keywords",    // 22 JSKEYWORDS
        "CSS keywords",           // 23 CSSKEYWORDS
    };
    if (style >= 0 && style < 24) return styleDescs[style];
    return "";
}

const char* SCI_METHOD LexerColdFusion::TagsOfStyle(int style) {
    return "";
}

Scintilla::ILexer5* SCI_METHOD LexerColdFusion::CreateLexer(const char* name)
{
	return (strcmp(name, LexerName()) == 0) ? LexerColdFusion::LexerFactory() : nullptr;
}

const char* SCI_METHOD LexerColdFusion::PropertyGet(const char* key) { return "";} ///

CFUserFunction::CFUserFunction(unsigned int ipos) {
		pos = ipos;
}

CFUserFunction::CFUserFunction() {
	pos = 0;
	scripted = false;
	name = "";
}

CFUserFunction::~CFUserFunction() {}

LRESULT nppMessageProc(UINT /*Message*/, WPARAM /*wParam*/, LPARAM /*lParam*/) {
	return 1;
}
///override version 4 in example
int SCI_METHOD LexerColdFusion::Version() const {
	return Scintilla::lvRelease4; // can try lvRelease5
}
