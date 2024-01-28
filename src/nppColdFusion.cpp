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


#include "nppColdFusion.h"
#include "DllEntry.h" ///*** 
namespace sID = nppColdFusion::Styles;		//  All of the style state codes.
namespace lex = nppColdFusion;				//  This lexer's namespace.

using namespace nppColdFusion;
const Lexilla::CharacterSet setTagContinue(Lexilla::CharacterSet::setAlphaNum, ".-_:!#[", 0x80, true);

static char* nppColdFusion::LexerName() {
	return const_cast<char*>(LEXER_NAME.c_str());
}

LexerColdFusion::LexerColdFusion() {
	cfs = nppCFShared::Instance();
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
	return (ch < 0x80) && (isalnum(ch) || ch == '.' || ch == '_');
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
							s[wordlength] = Lexilla::MakeLowerCase(ch); ///
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
		if (hasDeterminedType || inScriptComment || inScriptLineComment || closingcomment) {
			Colourise_Doc(startPos, length, initStyle, astyler);
			astyler.Flush();

		}
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
					nppCFShared& ref = *nppCFShared::Instance();
					if (chPrev != '/' && strstr("meta link img area br hr input cfabort cfajaximport cfajaxproxy cfapplet cfapplication cfargument cfassociate cfbreak cfcache cfcalendar cfchartdata cfchartseries cfcol cfcollection cfcontent cfcontinue cfcookie cfdbinfo cfdirectory cfdiv cfdump cferror cfexchangecalendar cfexchangeconnection cfexchangecontact cfexchangefilter cfexchangemail cfexchangetask cfexit cffeed cffile cfflush cfftp cfgridcolumn cfgridrow cfgridupdate cfheader cfhtmlhead cfhttp cfhttpparam cfimage cfimport cfinclude cfindex cfinput cfinsert cfinvoke cfinvokeargument cfldap cflocation cflog cfloginuser cflogout cfmailparam cfmodule cfntauthenticate cfobject cfobjectcache cfparam cfpdf cfpdfformparam cfpdfparam cfpop cfpresenter cfprint cfprocessingdirective cfprocparam cfprocresult cfproperty cfqueryparam cfregistry cfreport cfreportparam cfrethrow cfreturn cfschedule cfsearch cfset cfsetting cfsilent cfslider cfsprydataset cfstoredproc cftextinput cfthrow cftrace cftreeitem cfupdate cfwddx cfzip cfzipparam ", tagCF) == NULL && !cfs->coldfusionNS->isCustomTag(tagCF)) {
						if (tagCFClosing) {
							levelNext--;
						}
						else {
							if (strstr("cfelse cfelseif ", tagCF) != NULL) {
								levelNext--;
							}
							if (strstr("cfif cfelse cfelseif ", tagCF) != NULL) {
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
					if (chPrev != '/' && strstr("meta link img area br hr input ", tagHTML) == NULL) {
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
		loweredwl = CharLowerA(loweredwl);
		cfs->originallists[n] = new char[wllength];
		cfs->loweredlists[n] = new char[wllength];
		strcpy_s(cfs->loweredlists[n], wllength, loweredwl);
		strcpy_s(cfs->originallists[n], wllength, wl);
		delete[]loweredwl;
		return 0;
	}

	return -1;

}



//  <---  Colourise --->
Status LexerColdFusion::Colourise_Doc(Sci_PositionU startPos, Sci_Position length, int initStyle, Lexilla::LexAccessor& styler, bool dostyling)
{
	Status status = Status();

	status.openTagsBuffer[0] = '\0';

	boost::shared_ptr<BlockType> cfqueryblock(new CFQueryBlock);
	boost::shared_ptr<BlockType> cssblock(new CSSBlock);
	boost::shared_ptr<BlockType> jsblock(new JSBlock);
	boost::shared_ptr<BlockType> cfscriptblock(new CFScriptBlock);

	static const int cfquery = 0;
	static const int cfscript = 1;
	static const int js = 2;
	static const int css = 3;

	std::vector<boost::shared_ptr<BlockType>> blocks;

	blocks.push_back(cfqueryblock);
	blocks.push_back(cfscriptblock);
	blocks.push_back(jsblock);
	blocks.push_back(cssblock);

	int currentLine = styler.GetLine(startPos);
	int linestate = 0;

	linestate = styler.GetLineState(currentLine - 1);

	/*incfset.value	= getstoredbitvalue( linestate, incfset );
	status.inCFSet			= incfset.value;
	*/
	CSciMessager sciMsgr(cfs->m_nppMsgr.getCurrentScintillaWnd());
	unsigned int currenteditpos = sciMsgr.getCurrentPos();
	bool outsideeditingrange = false;
	if ((startPos < currenteditpos - min(currenteditpos, 100) || startPos > currenteditpos + 100)) {
		outsideeditingrange = true;
	}
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
		if (!outsideeditingrange) {
			if ((loopstartpos < currenteditpos - min(currenteditpos, 100) || loopstartpos > currenteditpos + 100)) {
				outsideeditingrange = true;
			}
		}
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
					for (std::vector<boost::shared_ptr<BlockType>>::iterator thisblock = blocks.begin(); thisblock != blocks.end(); ++thisblock) {
						(*thisblock)->updatelinestate(linestate);

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
										//word = new char[100];
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
										//word = new char[100];
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
							///const bool bracketsChanged = currentCFFunction.bracketDepths.Merge(bracketDepthsNew, sc.currentPos);
							if (localsChanged) {
								currentCFFunction.dirtyLocals = true;
							}
							if (argumentsChanged) {
								currentCFFunction.dirtyArguments = true;
							}
							cfUserFunctionsNew.Set(currentCFFunction.pos, currentCFFunction);
							const bool cfUserFunctionsChanged = cfUserFunctions.Merge(cfUserFunctionsNew, sc.currentPos);
							if (argumentsChanged || localsChanged || cfUserFunctionsChanged) {
								//	styler.ChangeLexerState(startPos, sc.currentPos);
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
			else if (isdigit(static_cast <unsigned char> (sc.ch)) && sc.state == sID::_DEFAULT) { //*** not exactly great
				int max = 100;
				if ((startPos - sc.currentPos) + length < 100) {
					max = (startPos - sc.currentPos) + length;
				}
				int len = 0;
				for (int a = 0; a < max; a++) {
					char s = sc.GetRelative(a);
					if (!isdigit(static_cast<unsigned char> (s)) && s != '.') { //***
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
						s[a] = Lexilla::MakeLowerCase(sc.GetRelative(a));
					}
					else {
						s[a] = '\0';
						bool handledkeyword = false;
						// temp override
						blocks[cfscript]->inBlock = inCFScript;
						blocks[cfquery]->inBlock = inCFQuery;
						blocks[js]->inBlock = inJSBlock;
						blocks[css]->inBlock = inCSSBlock;
						for (std::vector<boost::shared_ptr<BlockType>>::iterator thisblock = blocks.begin(); thisblock != blocks.end(); ++thisblock) {
							if ((*thisblock)->inBlock &&
								(*thisblock)->validateforkeyword(sc, inCFSet)) {
								if ((*thisblock)->hasReservedWord(s)) {
									int statebefore = sc.state;
									if (dostyling) {
										sc.SetState(sID::CFS_RESERVED);
									}

									sc.Forward(a - 1);
									
									if ((strcmp(s, "var") == 0 && currentCFFunction.pos > 0) || strcmp(s, "function") == 0) {
										//break; //*************************************
										/* Read Ahead to get name */
										///bool inName = false;
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
								else 	if ((*thisblock)->hasOperator(s)) {
									int statebefore = sc.state;
									if (dostyling) {
										sc.SetState(sID::_OPERATOR);
									}
									sc.Forward(a - 1);

									if (dostyling) {
										sc.ForwardSetState(statebefore);
									}
									handledkeyword = true;
									break;
								}
								else if (((outsideeditingrange && styler.StyleAt(sc.currentPos) == (*thisblock)->getKeywordState()) ||
									(*thisblock)->hasKeyword(s))) {
									int statebefore = sc.state;
									if (dostyling) {
										sc.SetState((*thisblock)->getKeywordState());
									}
									sc.Forward(a - 1);
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
									sc.Forward(a - 1);
									if (dostyling) {
										sc.ForwardSetState(statebefore);
									}
									handledkeyword = true;
									break;
								}
							}
						}
						if ((inCFSet) &&
							blocks[cfscript]->validateforkeyword(sc)) {

							if (strcmp(s, "var") == 0) {
								int statebefore = sc.state;
								if (dostyling) {
									sc.SetState(sID::CFS_RESERVED);
								}

								sc.Forward(a - 1);

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
							else if (blocks[cfscript]->hasOperator(s)) {
								int statebefore = sc.state;
								if (dostyling) {
									sc.SetState(sID::_OPERATOR);
								}
								handledkeyword = true;
								sc.Forward(a - 1);
								if (dostyling) {
									sc.ForwardSetState(statebefore);
								}
								break;
							}
							else if (((outsideeditingrange && styler.StyleAt(sc.currentPos) == blocks[cfscript]->getKeywordState()) ||
								(blocks[cfscript]->hasKeyword(s)))) {
								int statebefore = sc.state;
								if (dostyling) {
									sc.SetState(blocks[cfscript]->getKeywordState());
								}
								handledkeyword = true;
								sc.Forward(a - 1);
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
								sc.Forward(a - 1);
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
				status.preCFTagisHTMLTagOpening = true;
			}

			status.tagOpening = true;
			status.tagClosing = false;
			ZeroMemory(status.currentCFTag, sizeof(status.currentCFTag));

			if (!status.preCFTagisHTMLTagOpening) {
				ZeroMemory(status.currentHTMLTag, sizeof(status.currentHTMLTag));
			}

			int max = 100;
			if ((startPos - sc.currentPos) + length < 100) {
				max = (startPos - sc.currentPos) + length;
			}

			for (int a = 0; a < max; a++) {
				int ch = sc.GetRelative(a + 1);
				if (setTagContinue.Contains(ch)) {
					s[i++] = Lexilla::MakeLowerCase(ch);
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

					if (scriptcheck && ((outsideeditingrange && styler.StyleAt(sc.currentPos) == sID::CF_TAG) || cfs->coldfusionNS->isTag(paddedText))) {
						if (!status.tagClosing) {
							cfTagsNew.Set(sc.currentPos + strnlen_s(s, sizeof(s)) + 1, s);
						}
						strcpy_s(status.currentCFTag, sizeof(s), s);

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
									//	styler.ChangeLexerState(startPos, sc.currentPos);
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
					else if (jsscriptcheck && scriptcheck && cfs->htmlNS->isTag(paddedText) && !inCFQuery) {
						if (!status.tagClosing) {
							//SparseState<std::string> rawSTNew(sc.currentPos);

							htmlTagsNew.Set(sc.currentPos + strnlen_s(s, sizeof(s)), s);
							//const bool rawStringsChanged = htmlTags.Merge(rawSTNew, sc.currentPos + strnlen_s( s, sizeof( s ) ));
						}
						strcpy_s(status.currentHTMLTag, sizeof(s), s);
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

		if (sc.state == sID::_TAG && !sc.Match('>') && dostyling && status.tagOpening && status.currentHTMLTag != 0 && sc.Match(' ') && !sc.Match(" #")) {
			char s[100];
			int i = 0;
			int max = 100;
			if ((startPos - sc.currentPos) + length < 100) {
				max = (startPos - sc.currentPos) + length;
			}
			for (int a = 0; a < max; a++) {
				int ch = sc.GetRelative(a + 1);
				if (setTagContinue.Contains(ch)) {
					s[i++] = Lexilla::MakeLowerCase(ch);
				}
				else {
					//we're at a block

					s[i++] = '\0';

					if (cfs->htmlNS->tagHasAttribute(status.currentHTMLTag, s)) {
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
		if (sc.state == sID::CF_TAG && !sc.Match('>') && dostyling && status.tagOpening && status.currentCFTag != 0 && (sc.Match(' ') || sc.Match('\t'))) {
			char s[100];
			int i = 0;
			int max = 100;
			if ((startPos - sc.currentPos) + length < 100) {
				max = (startPos - sc.currentPos) + length;
			}
			for (int a = 0; a < max; a++) {
				int ch = sc.GetRelative(a + 1);
				if (setTagContinue.Contains(ch)) {
					s[i++] = Lexilla::MakeLowerCase(ch);
				}
				else {
					//we're at a block

					s[i++] = '\0';

					if (cfs->coldfusionNS->tagHasAttribute(status.currentCFTag, s)) {

						if ((strcmp(status.currentCFTag, "cffunction") == 0 || strcmp(status.currentCFTag, "cfargument") == 0) && strcmp(s, "name") == 0) {
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

								if (strcmp(status.currentCFTag, "cffunction") == 0) {
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
									//SparseState<CFBaseType>::stateVector argumentStates = currentCFFunction.arguments.getStates();
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
			//int i = 0;
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

			if (state == sID::CF_TAG || (status.tagClosing && state == sID::_DEFAULT && strcmp(status.currentCFTag, "cfscript") == 0)) {

				std::string currentTag = coldFusionTags.ValueAt(sc.currentPos);
				//SparseState<std::string> rawSTNew(sc.currentPos);

				auto j = strnlen_s(status.currentCFTag, sizeof(status.currentCFTag));
				status.currentCFTag[j] = ' ';
				status.currentCFTag[j + 1] = '\0';
				if (strstr("cfabort cfajaximport cfajaxproxy cfapplet cfapplication cfargument cfassociate cfbreak cfcache cfcalendar cfchartdata cfchartseries cfcol cfcollection cfcontent cfcontinue cfcookie cfdbinfo cfdirectory cfdiv cfdump cfelse cfelseif cferror cfexchangecalendar cfexchangeconnection cfexchangecontact cfexchangefilter cfexchangemail cfexchangetask cfexit cffeed cffile cfflush cfftp cfgridcolumn cfgridrow cfgridupdate cfheader cfhtmlhead cfhttp cfhttpparam cfimage cfimport cfinclude cfindex cfinput cfinsert cfinvoke cfinvokeargument cfldap cflocation cflog cfloginuser cflogout cfmailparam cfmodule cfntauthenticate cfobject cfobjectcache cfparam cfpdf cfpdfformparam cfpdfparam cfpop cfpresenter cfprint cfprocessingdirective cfprocparam cfprocresult cfproperty cfqueryparam cfregistry cfreport cfreportparam cfrethrow cfreturn cfschedule cfsearch cfset cfsetting cfsilent cfslider cfsprydataset cfstoredproc cftextinput cfthrow cftrace cftreeitem cfupdate cfwddx cfzip cfzipparam ", status.currentCFTag) == NULL) {
					if (status.tagOpening) {
						if (!dostyling) {
							auto curlen = strnlen(status.openTagsBuffer, sizeof(status.openTagsBuffer));
							status.openTagsPositions[status.currentopenTag] = curlen;
							strcpy_s(&status.openTagsBuffer[curlen], sizeof(status.openTagsBuffer) - curlen, status.currentCFTag);
							status.currentopenTag++;
						}
					}
					if (status.tagClosing) {
						if (!dostyling) {
							if (status.currentopenTag > 0) {
								status.currentopenTag--;
								status.openTagsBuffer[status.openTagsPositions[status.currentopenTag]] = '\0';
							}
						}
					}
				}
				status.currentCFTag[j] = '\0';
				if (dostyling) {
					if ((strcmp(status.currentCFTag, "cfquery") == 0)) {
						if (status.tagOpening) {
							inCFQuery = true;
							cfQueryBlocksNew.Set(sc.currentPos, true);
							//linestate = styler.GetLineState( currentLine );
							//blocks[cfquery]->updatelinestate( linestate );
							sc.ForwardSetState(sID::_DEFAULT);
						}
						else if (status.tagClosing && inCFQuery) {
							inCFQuery = false;
							cfQueryBlocksNew.Set(sc.currentPos, false);
							//blocks[cfquery]->inBlock = 0;
							//linestate = styler.GetLineState( currentLine );
							//blocks[cfquery]->updatelinestate( linestate );
							sc.ForwardSetState(status.stateHistory[status.lastState--]);
						}
					}
					else if ((strcmp(status.currentCFTag, "cfoutput") == 0)) {
						if (status.tagOpening) {
							cfOutputDepth++;
							//linestate = styler.GetLineState( currentLine );
							//linestate = changestoredbitvalue( linestate, cfoutputdepth );
							cfOutputDepthsNew.Set(sc.currentPos, cfOutputDepth);
						}
						else if (status.tagClosing && cfOutputDepth > 0) {
							cfOutputDepth--;
							cfOutputDepthsNew.Set(sc.currentPos, cfOutputDepth);

						}
						sc.ForwardSetState(status.stateHistory[status.lastState--]);
					}
					else if ((strcmp(status.currentCFTag, "cfscript") == 0)) {
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
					status.tagOpening = status.preCFTagisHTMLTagOpening;
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
				if (strstr("meta link img area br hr input ", status.currentHTMLTag) == NULL) {
					if (status.tagOpening) {
						if (!dostyling) {
							auto curlen = strnlen(status.openTagsBuffer, sizeof(status.openTagsBuffer));
							status.openTagsPositions[status.currentopenTag] = curlen;
							strcpy_s(&status.openTagsBuffer[curlen], sizeof(status.openTagsBuffer) - curlen, status.currentHTMLTag);
							status.currentopenTag++;
						}
					}
					if (status.tagClosing && !status.tagOpening) {
						if (!dostyling) {
							status.currentopenTag--;
							if (status.currentopenTag > 0) {
								status.openTagsBuffer[status.openTagsPositions[status.currentopenTag]] = '\0';
							}
						}
					}
				}
				if (dostyling) {
					if ((strcmp(status.currentHTMLTag, "script") == 0)) {
						if (status.tagOpening) {
							inJSBlock = true;
							jsBlocksNew.Set(sc.currentPos, true);
							//linestate = styler.GetLineState( currentLine );
							//blocks[js]->updatelinestate( linestate );
							sc.ForwardSetState(sID::_DEFAULT);
						}
						else if (status.tagClosing && inJSBlock) {

							inJSBlock = false;
							jsBlocksNew.Set(sc.currentPos, false);

							sc.ForwardSetState(status.stateHistory[status.lastState--]);
						}
					}
					else 	if ((strcmp(status.currentHTMLTag, "style") == 0)) {
						if (status.tagOpening) {
							inCSSBlock = true;
							cssBlocksNew.Set(sc.currentPos, true);
							sc.ForwardSetState(sID::_DEFAULT);
						}
						else if (status.tagClosing && blocks[css]->inBlock) {
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

/*
Scintilla::ILexer5* SCI_METHOD LexerColdFusion::CreateLexer(const char* name)
{
	return (strcmp(name, LexerName()) == 0) ? LexerColdFusion::LexerFactory() : nullptr;
//	return nullptr; /////////***
}
*/
Scintilla::ILexer5* SCI_METHOD LexerColdFusion::CreateLexer(const char* name)
{
	return (strcmp(name, LexerName()) == 0) ? LexerColdFusion::LexerFactory() : nullptr;
}

const char* SCI_METHOD LexerColdFusion::PropertyGet(const char* key) { return "";} ///

CFUserFunction::CFUserFunction(unsigned int ipos) {
	//arguments.states.empty();
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
///override version 4 in exemple
int SCI_METHOD LexerColdFusion::Version() const {
	return Scintilla::lvRelease4;
}
