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

#include "CFMLPlugin.h"
///#include <boost/thread/thread.hpp> /// *** trying use sleep, but failed to build
//#include <Windows.h> //for Sleep only, this does work


using namespace nppColdFusionNS;
extern CFMLPlugin cfmlplugin;

bool     g_dbOpen;

WNDPROC CFMLPlugin::nppOriginalWndProc = NULL;

AutoCompleteStructure::AutoCompleteStructure() {}
AutoCompleteStructure::~AutoCompleteStructure() {}
AutoCompleteBit::AutoCompleteBit() {}
AutoCompleteBit::~AutoCompleteBit() {}


CFMLPlugin::CFMLPlugin()
{
	lastAC = new AutoCompleteBit();
	lastAC->pos = 0;
	lastAC->text = "";


}

CFMLPlugin::~CFMLPlugin()
{
}


FuncItem* CFMLPlugin::nppGetFuncsArray(int* pnbFuncItems)
{
	//nppCFShared &cfs = *nppCFShared::Instance();

	*pnbFuncItems = nppCFMenu::N_NBFUNCITEMS;
	return nppCFMenu::arrFuncItems;
}
bool CFMLPlugin::isNppWndUnicode = true;


LRESULT CFMLPlugin::nppCallWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return (isNppWndUnicode ?
		::CallWindowProcW(nppOriginalWndProc, hWnd, uMsg, wParam, lParam) :
		::CallWindowProcA(nppOriginalWndProc, hWnd, uMsg, wParam, lParam));
}


LRESULT CALLBACK CFMLPlugin::nppNewWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/* TODO: Might have to do something with this to help with Macros! */

	/*if ( uMsg == WM_COMMAND )
	{
		const WORD id = LOWORD(wParam);
		switch ( id )
		{
			case IDM_MACRO_STARTRECORDINGMACRO:
				thePlugin.OnNppMacro(MACRO_START);
				break;

			case IDM_MACRO_STOPRECORDINGMACRO:
				thePlugin.OnNppMacro(MACRO_STOP);
				break;

			case IDC_EDIT_TOGGLEMACRORECORDING:
				thePlugin.OnNppMacro(MACRO_TOGGLE);
				break;

			case IDM_MACRO_PLAYBACKRECORDEDMACRO:
				{
					thePlugin.OnNppMacro(MACRO_START);
					LRESULT lResult = nppCallWndProc(hWnd, uMsg, wParam, lParam);
					thePlugin.OnNppMacro(MACRO_STOP);
					return lResult;
				}
				break;

			default:
				if ( (id >= ID_MACRO) && (id < ID_MACRO_LIMIT) )
				{
					thePlugin.OnNppMacro(MACRO_START);
					LRESULT lResult = nppCallWndProc(hWnd, uMsg, wParam, lParam);
					thePlugin.OnNppMacro(MACRO_STOP);
					return lResult;
				}
				break;
		}
	}
	else if ( uMsg == WM_MACRODLGRUNMACRO )
	{
		thePlugin.OnNppMacro(MACRO_START);
		LRESULT lResult = nppCallWndProc(hWnd, uMsg, wParam, lParam);
		thePlugin.OnNppMacro(MACRO_STOP);
		return lResult;
	}
	*/
	return nppCallWndProc(hWnd, uMsg, wParam, lParam);
}

/**/
const TCHAR* CFMLPlugin::nppGetName()
{
	//return nppColdFusionNS::PLUGIN_NAME.c_str(); //produces error LNK2001: unresolved external symbol "public: static wchar_t const * const CFMLPlugin::PLUGIN_NAME" (?PLUGIN_NAME@CFMLPlugin@@2PEB_WEB)
	//return 0; //no errors
	return TEXT("nppColdFusion"); //incorrect ***
}


void CFMLPlugin::nppBeNotified(SCNotification* notifyCode)
{
	int keystate = 0;
	if (notifyCode->nmhdr.hwndFrom == m_nppMsgr.getNppWnd()) {
		// >>> notifications from Notepad++
		switch (notifyCode->nmhdr.code) {
		case NPPN_BUFFERACTIVATED:
			OnNppBufferActivated();
			break;

		case NPPN_FILEOPENED:
			//OnNppFileOpened();
			break;

		case NPPN_FILESAVED:
			OnNppFileSaved();
			break;

		case NPPN_READY:
			OnNppReady();
			break;
		case NPPN_LANGCHANGED:
			OnNppLangChanged(notifyCode->nmhdr.idFrom);
			break;
		case NPPN_SHUTDOWN:
			OnNppShutdown();
			break;

		default:
			break;
		}
		// <<< notifications from Notepad++
	}
	else {
		nppCFShared& cfs = *nppCFShared::Instance();

		// >>> notifications from Scintilla
		switch (notifyCode->nmhdr.code) {
		case SCN_UPDATEUI:
			break;
		case SCN_CHARADDED:
			OnSciCharAdded(notifyCode->ch);
			break;
		case SCN_AUTOCCANCELLED:
			ResetShiftTab();
			break;
		case SCN_AUTOCSELECTION:
			ResetShiftTab();

			keystate = ::GetKeyState(VK_SHIFT);

			if (keystate < 0 || cfs.alwaysCompleteReqAttributes) {
				// Shift is held
				OnSciAutoCSelection(notifyCode->lParam, notifyCode->text);
			}

			break;
		default:
			break;
		}
		// <<< notifications from Scintilla
	}

}

void CFMLPlugin::OnNppLangChanged(int idFrom)
{

}

void CFMLPlugin::OnNppFileSaved()
{
	//UpdateFileType();
}
void CFMLPlugin::OnNppReady()
{
	//ReadOptions();
	//CXBracketsMenu::UpdateMenuState();
	//UpdateFileType();

	if (isNppWndUnicode) {
		nppOriginalWndProc = (WNDPROC)SetWindowLongPtrW(
			m_nppMsgr.getNppWnd(), GWLP_WNDPROC, (LONG_PTR)nppNewWndProc);
	}
	else {
		nppOriginalWndProc = (WNDPROC)SetWindowLongPtrA(
			m_nppMsgr.getNppWnd(), GWLP_WNDPROC, (LONG_PTR)nppNewWndProc);
	}

	nppCFShared& cfs = *nppCFShared::Instance();
	int a = cfs.m_nppMsgr.SendNppMsg(NPPM_MSGTOPLUGIN, (WPARAM)_T("FingerText.dll"), (LPARAM)true);
	if (a) {
		cfs.isFingerTextInstalled = true;
	}
	else {
		cfs.isFingerTextInstalled = false;
	}
	nppCFMenu::updateMenu();
	cfs.nppReady = true;
}



void CFMLPlugin::OnNppShutdown()
{
	nppCFShared& cfs = *nppCFShared::Instance();
	if (nppOriginalWndProc) {
		if (isNppWndUnicode) {
			::SetWindowLongPtrW(m_nppMsgr.getNppWnd(),
				GWLP_WNDPROC, (LONG_PTR)nppOriginalWndProc);
		}
		else {
			::SetWindowLongPtrA(m_nppMsgr.getNppWnd(),
				GWLP_WNDPROC, (LONG_PTR)nppOriginalWndProc);
		}
	}
	// cfs.cleanupDB();  // REMOVED - no SQLite

	//SaveOptions();
}
/*
 Might Need to use this for script based CFCs.
*/
//int CFMLPlugin::getFileType(bool& isSupported)
//{

/* TCHAR szExt[500];
 int   nType = 0;

 isSupported = false;
 szExt[0] = 0;
 m_nppMsgr.getCurrentFileExtPart(499, szExt);
int b = 0;
int a = m_nppMsgr.SendNppMsg(NPPM_GETCURRENTLANGTYPE, (WPARAM) 0, (LPARAM) &b);
int c = m_nppMsgr.SendNppMsg(NPPM_GETCURRENTBUFFERID);

 if ( szExt[0] )
 {
	 TCHAR* pszExt = szExt;

	 if ( *pszExt == _T('.') )
	 {
		 ++pszExt;
		 if ( !(*pszExt) )
			 return nType;
	 }

	 ::CharLower(pszExt);

	 if ( lstrcmp(pszExt, _T("cfm")) == 0 ||
		  lstrcmp(pszExt, _T("cfc")) == 0)
	 {
		 nType = 1;
	 }

	 isSupported = (nType==1);
 }

 return nType;
*/
//}



void CFMLPlugin::OnNppBufferActivated()
{
	//UpdateFileType();
}


void CFMLPlugin::UpdateFileType() // <-- call it when the plugin becomes active!!!
{
	//if ( !g_opt.m_bBracketsAutoComplete )
	//     return;

	//m_nAutoRightBracketPos = -1;
	//m_nFileType = getFileType(m_bSupportedFileType);
}


void CFMLPlugin::OnSciCharAdded(int ch)
{
	/*if (!m_bSupportedFileType)
		return;
	*/
	if (ch == 13 || ch == 10) {
		return;
	}
	// We need to check to see if the lexer is currently "aware" of this buffer - that is -
	// if the lexer has not been run, then in theory the buffer id we store should not be the
	// same, this essentially means any files that use the lexer can have the auto complete
	nppCFShared& cfs = *nppCFShared::Instance();
	int currentbuffid = cfs.m_nppMsgr.getCurrentBufferID();
	LexerColdFusion* lexer = cfs.getLexerForDoc(currentbuffid);
	// If N++'s current buffer id doesn't match the lexer one then don't go any further.
	if (!lexer) {
		return;
	}


	CSciMessager sciMsgr(m_nppMsgr.getCurrentScintillaWnd());

	bool activeac = sciMsgr.isAutoCActive();


	if (activeac != 0 && ch != ' ') {
		// a popup is active no need for further processing
		if (ch == '>') {
			sciMsgr.SendSciMsg(SCI_AUTOCCANCEL);
		}
		return;
	}

	char space = ' ';
	// lets see if we can find one
	int currentpos = sciMsgr.getCurrentPos();
	int line = sciMsgr.getLineFromPos(currentpos);
	int pos = sciMsgr.getCaretInLine();
	int state = sciMsgr.getLineState(line - 1);
	int wordstart = sciMsgr.SendSciMsg(SCI_WORDSTARTPOSITION, (WPARAM)currentpos, (LPARAM)true);

	bool inCFScript = lexer->scriptBlocks.ValueAt(currentpos);
	bool inCFQuery = lexer->cfQueryBlocks.ValueAt(currentpos);
	bool inJSBlock = lexer->jsBlocks.ValueAt(currentpos);
	bool inCSSBlock = lexer->cssBlocks.ValueAt(currentpos);
	bool inCFSet = lexer->inCFSets.ValueAt(currentpos);

	int isctipactive = sciMsgr.SendSciMsg(SCI_CALLTIPACTIVE);
	int style = sciMsgr.getStyleAt(currentpos);
	// Lets update our status bits to this point
	Lexilla::LexAccessor astyler(cfs.currentdoc);
	Status status = lexer->Colourise_Doc(currentpos - pos, pos, sciMsgr.getStyleAt(currentpos - pos), astyler, false);

	char wordstartchar = sciMsgr.getCharAt(wordstart - 1);
	CFUserFunction func = lexer->cfUserFunctions.ValueAt(currentpos);

	if (!inCFSet && (status.tagOpening == true || style == Styles::_TAG || style == Styles::CF_TAG || style == Styles::CF_ATTRIBUTEBAD || (style == Styles::_DOUBLESTRING && status.currentCFTag[0] != 0))) {


		int charssince = currentpos - wordstart;



		char prevch = sciMsgr.getCharAt(wordstart - 2);
		if (wordstartchar == '"' && prevch == '=') {

			int searchstartpos = wordstart - 2;
			int searchpos = sciMsgr.SendSciMsg(SCI_WORDSTARTPOSITION, (WPARAM)wordstart - 2, (LPARAM)true);

			int j = 0;
			char previousword[512];
			for (int i = searchpos; i < searchstartpos; i++) {
				previousword[j++] = (char) ::CharLowerA((LPSTR)sciMsgr.getCharAt(i));
			}
			previousword[j++] = '\0';

			if (status.tagOpening == true && (status.currentCFTag[0] != 0 || status.currentHTMLTag[0] != 0)) {
						char tagName[100];
						strncpy_s(tagName, status.currentCFTag, 100);

						const char* expanded;
						if (status.currentHTMLTag[0] != 0) {
							strncpy_s(tagName, status.currentHTMLTag, 100);
							expanded = cfs.htmlNS->listAttributeValues(tagName, previousword);
						}
						else {
							expanded = cfs.coldfusionNS->listAttributeValues(tagName, previousword);
						}
						if (cfs.completeCFsqltype && charssince == 0 && strcmp(previousword, "cfsqltype") == 0) {
							sciMsgr.SendSciMsg(SCI_ADDTEXT, (WPARAM)7, (LPARAM)"cf_sql_");
							charssince = 7;
						}
						if (expanded != 0 && strlen(expanded) > 1) {
							sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
							sciMsgr.autoCSetIgnoreCase(true);
							sciMsgr.autoCSetSeparator(space);
							sciMsgr.autoCShow(charssince, (const char*)expanded);
						}
						// delete[] expanded;  // expanded is now const char*, don't delete
					}
					return;

		}
		else if (wordstartchar == ' ' && prevch != '>') {

			char wordtooffer[100];
			char tagName[100];

			wordtooffer[0] = '\0';

			int stylebefore = sciMsgr.getStyleAt(currentpos - 2);
			int styleat = sciMsgr.getStyleAt(currentpos);
			char nextch = sciMsgr.getCharAt(wordstart);
			std::string currentCFTag = lexer->coldFusionTags.ValueAt(currentpos);

			std::string currentHTMLTag = lexer->htmlTags.ValueAt(currentpos);

			if (currentCFTag != "") {
				strncpy_s(tagName, currentCFTag.c_str(), 100);
			}
			else if (currentHTMLTag != "") {
				strncpy_s(tagName, currentHTMLTag.c_str(), 100);
			}
			if ((status.tagOpening == true || currentCFTag != "" || currentHTMLTag != "") &&
						!(prevch == '"' && nextch == '"') &&
						(currentCFTag != "" || currentHTMLTag != "") &&
						(stylebefore == Styles::_TAG || stylebefore == Styles::CF_TAG) ||
						(styleat == Styles::CF_ATTRIBUTEBAD || styleat == Styles::_ATTRIBUTEUNKNOWN) && (stylebefore == styleat || stylebefore == Styles::_DOUBLESTRING) ||
						(styleat == Styles::CF_ATTRIBUTE || styleat == Styles::_ATTRIBUTE)) {
					const char* expanded;
					if (currentCFTag == "" && currentHTMLTag != "") {
								//strncpy_s( tagName,status.currentHTMLTag, 100 );
								sciMsgr.SendSciMsg(SCI_REGISTERIMAGE, (WPARAM)1, (LPARAM)tags_blue);
								sciMsgr.SendSciMsg(SCI_AUTOCSETTYPESEPARATOR, (WPARAM)0x3f, (LPARAM)"");
								expanded = cfs.htmlNS->listTagAttributes(tagName, true);
								//Sleep(100);
							}
							else {
								//LRESULT res = sciMsgr.SendSciMsg(SCI_CLEARREGISTEREDIMAGES, (WPARAM)0, (LPARAM)"");
								sciMsgr.SendSciMsg(SCI_REGISTERIMAGE, (WPARAM)1, (LPARAM)tags_red);
								sciMsgr.SendSciMsg(SCI_AUTOCSETTYPESEPARATOR, (WPARAM)0x3f, (LPARAM)"");
								expanded = cfs.coldfusionNS->listTagAttributes(tagName, true);
								//Sleep(10);
							}
					if (expanded != 0 && strlen(expanded) > 1) {
						// by trial and error: SCI_AUTOCSETTYPESEPARATOR fixes /? in lists with images, in NPP 8.5+
						sciMsgr.SendSciMsg(SCI_AUTOCSETTYPESEPARATOR, (WPARAM)0x3f, (LPARAM)"");
						sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
						sciMsgr.autoCSetIgnoreCase(true);
						sciMsgr.autoCSetSeparator(space);
						sciMsgr.autoCShow(charssince, (const char*)expanded);
					}
					// delete[] expanded;  // expanded is now const char*, don't delete
					return;
			}
		}
	}
	//#endif
	if (inCFScript || inCFSet) {

		// call tips
		if (isctipactive == 1 && ch == ')' && style == Styles::_DEFAULT) {

		}
		if (ch == '(') {

			int searchstartpos = currentpos - 1;
			int searchpos = sciMsgr.SendSciMsg(SCI_WORDSTARTPOSITION, (WPARAM)currentpos - 1, (LPARAM)true);

			int j = 0;
			char previousword[512];
			for (int i = searchpos; i < searchstartpos; i++) {
				previousword[j++] = (char) ::CharLowerA((LPSTR)sciMsgr.getCharAt(i));
			}
			previousword[j++] = '\0';
			cffunction thisone = getfunction(previousword);
			const char* calltipstart;

			if (strcmp(thisone.name, "notafunction") != 0) {
				calltipstart = getTypeAsString(thisone.returntype);
				char calltiptext[1024];
				strcpy_s(calltiptext, calltipstart);

				strcat_s(calltiptext, thisone.name);
				for (int thisparam = 0; thisparam <= 10; thisparam++) {
					if (strcmp(thisone.parameters[thisparam].name, "notaparameter") == 0) {
						if (thisparam > 0) {
							strcat_s(calltiptext, ")");
						}
						break;
					}
					if (thisparam > 0) {
						strcat_s(calltiptext, ", ");
					}
					else {
						strcat_s(calltiptext, "(");
					}
					if (!thisone.parameterrequired[thisparam]) {
						strcat_s(calltiptext, "[");
					}
					strcat_s(calltiptext, getTypeAsString(thisone.parameters[thisparam].type));
					strcat_s(calltiptext, thisone.parameters[thisparam].name);
					if (!thisone.parameterrequired[thisparam]) {
						strcat_s(calltiptext, "]");
					}
				}
				sciMsgr.SendSciMsg(SCI_CALLTIPSHOW, (WPARAM)currentpos, (LPARAM)calltiptext);
				return;
			}
		}
	}



	if (style == Styles::_DEFAULT || style == Styles::CF_VALUE) {

		if (inCFQuery && style != Styles::CF_VALUE) {
			if (currentpos > wordstart + 2) {
				int charssince = currentpos - wordstart;

				if (charssince > 1 && charssince < 15) {
								char sqkw_copy[2048];
								strncpy_s(sqkw_copy, cfs.sqlNS->listAllKeywords(), sizeof(sqkw_copy));
								::CharUpperA(sqkw_copy);
								sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
								sciMsgr.autoCSetIgnoreCase(true);
								sciMsgr.autoCSetSeparator(space);
								sciMsgr.autoCShow(charssince, sqkw_copy);
							}
			}
		}

		if (inCFScript || inCFSet || style == Styles::CF_VALUE) {
			if (wordstartchar == '.' && func.pos > 0) {
				int charssince = currentpos - wordstart;
				int searchstartpos = wordstart - 1;
				int searchpos = sciMsgr.SendSciMsg(SCI_WORDSTARTPOSITION, (WPARAM)wordstart - 1, (LPARAM)true);

				int j = 0;
				char previousword[512];
				for (int i = searchpos; i < searchstartpos; i++) {
					previousword[j++] = (char) ::CharLowerA((LPSTR)sciMsgr.getCharAt(i));
				}
				previousword[j++] = '\0';

				if (strcmp(previousword, "arguments") == 0) {
					std::string arguments = func.getArgumentssSorted("?1");
					sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
					sciMsgr.autoCSetIgnoreCase(true);
					sciMsgr.autoCSetSeparator(space);
					sciMsgr.SendSciMsg(SCI_REGISTERIMAGE, (WPARAM)1, (LPARAM)tag_green);
					
					sciMsgr.autoCShow(charssince, (const char*)arguments.c_str());
				}
				else if (strcmp(previousword, "local") == 0) {
					std::string locals = func.getLocalsSorted("?1");
					sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
					sciMsgr.autoCSetIgnoreCase(true);
					sciMsgr.autoCSetSeparator(space);
					sciMsgr.SendSciMsg(SCI_REGISTERIMAGE, (WPARAM)1, (LPARAM)shield);
					sciMsgr.SendSciMsg(SCI_AUTOCSETTYPESEPARATOR, (WPARAM)0x3f, (LPARAM)""); // 0x3f="?" 
					sciMsgr.autoCShow(charssince, (const char*)locals.c_str());
				}

			}
			if (currentpos > wordstart + 2) {
				int charssince = currentpos - wordstart;

				if (charssince > 1 && charssince < 15) {
					const char* cff = cfs.coldfusionNS->listAllKeywords(false, true);
					const char* cffl = cfs.coldfusionNS->listAllKeywords(true);
					const char* loweredword;
					char thisword[20];
					int a = 0;
					int b = 0;
					thisword[0] = ' ';
					for (a = wordstart; a <= currentpos; a++) {
						b = (a - wordstart) + 1;
						thisword[b] = sciMsgr.getCharAt(a);
						if (b > 17) {
							break;
						}
					}
					thisword[b] = '\0';
					loweredword = ::CharLowerA(thisword);
					//cfs.wordlists[2]->InListAbbreviated(thisword
					const char* test = strstr(cffl, loweredword);
					if (test != 0) {
						sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
						sciMsgr.SendSciMsg(SCI_REGISTERIMAGE, (WPARAM)1, (LPARAM)cf_func);
						sciMsgr.SendSciMsg(SCI_AUTOCSETTYPESEPARATOR, (WPARAM)0x3f, (LPARAM)""); // 0x3f="?" 
						sciMsgr.autoCSetIgnoreCase(true);
						sciMsgr.autoCSetSeparator(space);
						sciMsgr.autoCShow(charssince, (const char*)cff);
						/*char firstch = sciMsgr.getCharAt(lastAC->pos);
						char secndch = sciMsgr.getCharAt(lastAC->pos + 1);
						*/
					}
				}
			}
		}
		else if (inJSBlock && style != Styles::CF_VALUE) {
			if (currentpos > wordstart + 2) {
				int charssince = currentpos - wordstart;

				if (charssince > 1 && charssince < 15) {
					const char* sqkw = cfs.javascriptNS->listAllKeywords();
					sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
					sciMsgr.autoCSetIgnoreCase(true);
					sciMsgr.autoCSetSeparator(space);
					sciMsgr.autoCShow(charssince, (const char*)sqkw);
				}
			}
		}


		if (ch == '<' /*&& !cfscriptblock->inBlock*/ && style != Styles::CF_VALUE) {
			lastAC->pos = currentpos;
			lastAC->text = "<";
			return;
		}


		if (strcmp(lastAC->text, "<") == 0 && inCFScript && ch != '/') {
			// cfscript needs to stop trying to process tags if we're not closing cfscript.
			lastAC->pos = 0;
			lastAC->text = "";
			return;
		}

		if (strcmp(lastAC->text, "<") == 0 /*&& !cfscriptblock->inBlock*/ && style != Styles::CF_VALUE) {
			switch (ch) {
			case '>':
			case ' ':
				lastAC->pos = 0;
				lastAC->text = "";
				sciMsgr.SendSciMsg(SCI_AUTOCCANCEL);
				return;
				break;
			}


			int charssince = currentpos - lastAC->pos;

			if (charssince >= 1 && charssince < 15) {
				char firstch = sciMsgr.getCharAt(lastAC->pos);
				char secndch = sciMsgr.getCharAt(lastAC->pos + 1);

				if (firstch == '/') {
					bool foundtag = false;
					char wordtooffer[100];
					wordtooffer[0] = '\0';
					Status statustag = lexer->Colourise_Doc(currentpos - pos, pos, sciMsgr.getStyleAt(currentpos - pos), astyler, false);

					if (statustag.currentopenTag > 0) {
						strcpy_s(wordtooffer, 100, &statustag.openTagsBuffer[statustag.openTagsPositions[status.currentopenTag - 1]]);
						if (wordtooffer[strnlen(wordtooffer, 100) - 1] == ' ') {
							wordtooffer[strnlen(wordtooffer, 100) - 1] = '\0';
						}
					}
					else {

						int foldparentline = sciMsgr.SendSciMsg(SCI_GETFOLDPARENT, (WPARAM)line);
						int lineafterfold = foldparentline + 1;
						int posforfold = sciMsgr.SendSciMsg(SCI_POSITIONFROMLINE, (WPARAM)lineafterfold) - 1;
						int posstop = sciMsgr.SendSciMsg(SCI_POSITIONFROMLINE, (WPARAM)lineafterfold - 1);
						if (posstop < 0) {
							posstop = 0;
						}
						int tagendpos = 0;

						for (int a = posforfold; a > posstop; a--) {
							char search = sciMsgr.getCharAt(a);
							if (search == '>') {
								foundtag = true;
								tagendpos = a;
								break;
							}
						}

						if (foundtag == true) {
							Status statustag = lexer->Colourise_Doc(posstop, (tagendpos + 1) - posstop, sciMsgr.getStyleAt(posstop), astyler, false);

							if (statustag.currentopenTag > 0) {
								if (status.currentopenTag < 0) {
									statustag.currentopenTag += status.currentopenTag;
									statustag.openTagsBuffer[statustag.openTagsPositions[statustag.currentopenTag]] = '\0';
								}
								if (statustag.currentopenTag > 0) {
									strcpy_s(wordtooffer, 100, &statustag.openTagsBuffer[statustag.openTagsPositions[statustag.currentopenTag - 1]]);
									if (wordtooffer[strnlen(wordtooffer, 100) - 1] == ' ') {
										wordtooffer[strnlen(wordtooffer, 100) - 1] = '\0';
									}
								}
							}
							/*
							int stophere = true;

							if (strnlen_s(statustag.currentCFTag, sizeof(statustag.currentCFTag)) > 0) {
								 strcpy_s(wordtooffer, statustag.currentCFTag);
							}
							if (strnlen_s(statustag.currentHTMLTag, sizeof(statustag.currentHTMLTag)) > 0) {
								strcpy_s(wordtooffer, statustag.currentHTMLTag);
							}*/
						}
					}
					auto wordlength = strnlen_s(wordtooffer, 100);
					if (wordlength > 0) {
						wordtooffer[wordlength] = '>';
						wordtooffer[wordlength + 1] = '\0';
						sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
						sciMsgr.autoCSetIgnoreCase(true);
						sciMsgr.autoCSetSeparator(space);
						//sciMsgr.SendSciMsg(SCI_AUTOCSTOPS, (WPARAM) '\0' , (LPARAM) '>');
						sciMsgr.autoCShow(charssince - 1, (const char*)wordtooffer);

					}

				}
				else if (charssince > 1 && !inCFScript) {
					if (firstch == 'c' && secndch == 'f') {
						//WordList &cfkeywords = *cfs.wordlists[1];
						const char* cfkw = cfs.coldfusionNS->listAllTags(true);
						//sciMsgr.SendSciMsg(SCI_AUTOCSETMAXHEIGHT, (WPARAM) 10);
						int keytakeover = SCK_TAB + (SCMOD_SHIFT << 16);
						sciMsgr.SendSciMsg(SCI_CLEARCMDKEY, (WPARAM)keytakeover);
						sciMsgr.SendSciMsg(SCI_REGISTERIMAGE, (WPARAM)1, (LPARAM)tags_red);
						sciMsgr.SendSciMsg(SCI_AUTOCSETTYPESEPARATOR, (WPARAM)0x3f, (LPARAM)""); // 0x3f="?" 
						sciMsgr.SendSciMsg(SCI_ASSIGNCMDKEY, (WPARAM)keytakeover, SCI_AUTOCCOMPLETE);
						sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
						sciMsgr.autoCSetIgnoreCase(true);
						sciMsgr.autoCSetSeparator(space);
						sciMsgr.autoCShow(charssince, cfkw);
						//https://stackoverflow.com/questions/2001286/const-char-s-in-c
						//delete[] cfkw;

					}
					else if (!inJSBlock && !inCFQuery) {
						//WordList &htmlkeywords = *cfs.wordlists[0];
						const char* htkw = cfs.htmlNS->listAllTags(true);
						//sciMsgr.SendSciMsg(SCI_AUTOCSETMAXHEIGHT, (WPARAM) 10);
						//sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM) 0, (LPARAM) ' ');
						sciMsgr.SendSciMsg(SCI_REGISTERIMAGE, (WPARAM)1, (LPARAM)tags_blue);
						sciMsgr.SendSciMsg(SCI_AUTOCSETTYPESEPARATOR, (WPARAM)0x3f, (LPARAM)""); // 0x3f="?" 
						sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM)0, (LPARAM)"");
						sciMsgr.autoCSetIgnoreCase(true);
						sciMsgr.autoCSetSeparator(space);
						sciMsgr.autoCShow(charssince, htkw);
						//delete[] htkw;
					}
				}
			}
			/*if (prevCH2 == '<' && !cfscriptblock->inBlock)
			{
				if (prevCH == 'c' && ch == 'f')
				{
					WordList &cfkeywords = *cfs.wordlists[1];
					const char * cfkw = cfs.originallists[1];
					//sciMsgr.SendSciMsg(SCI_AUTOCSETMAXHEIGHT, (WPARAM) 10);
					//sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM) 0, (LPARAM) ' ');
					//sciMsgr.autoCSetIgnoreCase(true);
					sciMsgr.autoCSetSeparator('\0');
					sciMsgr.autoCShow(2, cfkw);

				}
				else
				{
					WordList &htmlkeywords = *cfs.wordlists[0];
					const char * htkw = cfs.originallists[0];
					//sciMsgr.SendSciMsg(SCI_AUTOCSETMAXHEIGHT, (WPARAM) 10);
					//sciMsgr.SendSciMsg(SCI_AUTOCSETFILLUPS, (WPARAM) 0, (LPARAM) ' ');
					//sciMsgr.autoCSetIgnoreCase(true);
					sciMsgr.autoCSetSeparator('\0');
					sciMsgr.autoCShow(2, htkw);
				}
			}*/
		}


	}
	/*
	WordList &cfkeywords = *cfs.wordlists[1];
	const char * cfkw = cfs.originallists[1];

	int line = sciMsgr.SendSciMsg(SCI_LINEFROMPOSITION, sciMsgr.SendSciMsg(SCI_GETCURRENTPOS));
	int pos = sciMsgr.getCaretInLine();
	int state = sciMsgr.SendSciMsg(SCI_GETLINESTATE, (WPARAM) line);
	CFScriptBlock* cfscriptblock = new CFScriptBlock();
	cfscriptblock->updatefromlinestate(state);

	int b = pos;
	sciMsgr.autoCSetSeparator('\0');
	sciMsgr.autoCShow(0, cfkw);
	*/
}
void CFMLPlugin::ResetShiftTab()
{
	CSciMessager sciMsgr(m_nppMsgr.getCurrentScintillaWnd());
	int keytakeover = SCK_TAB + (SCMOD_SHIFT << 16);
	sciMsgr.SendSciMsg(SCI_CLEARCMDKEY, (WPARAM)keytakeover);
	sciMsgr.SendSciMsg(SCI_ASSIGNCMDKEY, (WPARAM)keytakeover, SCI_BACKTAB);

}
void CFMLPlugin::OnSciAutoCSelection(int pos, const char* text)
{


	nppCFShared& cfs = *nppCFShared::Instance();
	CSciMessager sciMsgr(m_nppMsgr.getCurrentScintillaWnd());
	const char* expanded;

	expanded = cfs.coldfusionNS->listTagAttributes(text, true, cfs.isFingerTextInstalled && cfs.integrateWithFingerText, false);

	if (expanded != 0 && strlen(expanded) > 1) {
		char* texttoinsert = new char[strlen(expanded) + strlen(text) + 2];
		texttoinsert[0] = '\0';
		int curpos = sciMsgr.getCurrentPos();
		strcat_s(texttoinsert, strlen(expanded) + strlen(text) + 2, text + (curpos - pos));
		strcat_s(texttoinsert, strlen(expanded) + strlen(text) + 2, " ");
		//expanded[strlen(expanded)] = '\0';
		strcat_s(texttoinsert, strlen(expanded) + strlen(text) + 2, expanded);
		//

		sciMsgr.SendSciMsg(SCI_AUTOCCANCEL);
		sciMsgr.setSelectionStart(pos);
		sciMsgr.setSelectionEnd(curpos);

		sciMsgr.SendSciMsg(SCI_ADDTEXT, strlen(texttoinsert), (LPARAM)texttoinsert);
		sciMsgr.goToPos(curpos);
		if (cfs.isFingerTextInstalled && cfs.integrateWithFingerText) {
			// We need to cancel the shift key so fingertext will activate
			keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0);
			keybd_event(VK_TAB, 0, 0, 0);
		}
		else {
			//sciMsgr.goToPos();
			int endpos = sciMsgr.SendSciMsg(SCI_WORDENDPOSITION, pos + strlen(text) + 2);
			sciMsgr.goToPos(endpos + 2);
		}

	}
	delete[] expanded;

	/* TODO: maybe add proper indenting when closing tags etc */
	/* NOTE: the below was a test for chaining autocompletes, which failed :( */



	/*
	if (strcmp(text,"cfinclude") == 0)
	{

		// template="
		const char * text2 = "cfinclude template=\"\">";
		//const char * text2 = "cfinclude ";
		//WcharMbcsConvertor *wmc = WcharMbcsConvertor::getInstance();
		//unsigned int cp = sciMsgr.SendSciMsg(SCI_GETCODEPAGE);
		//const char *text2AppendA =wmc->wchar2char(text2, cp);
		//execute(SCI_ADDTEXT, strlen(text2AppendA), (LPARAM)text2AppendA);

		//int line = sciMsgr.SendSciMsg(SCI_LINEFROMPOSITION, sciMsgr.SendSciMsg(SCI_GETCURRENTPOS));
		//int pos3 = sciMsgr.getCaretInLine();

		//int pos2 = pos+9;
		//sciMsgr.SendSciMsg(SCI_SETCURRENTPOS, (WPARAM) pos2);
		//sciMsgr.SendSciMsg(SCI_INSERTTEXT, (WPARAM) 10, (LPARAM) "          ");
		int pos2 = sciMsgr.getCurrentPos();
		int trimamount = pos2 - pos;
		const char * actualtext = text2 + trimamount;
		//sciMsgr.SendSciMsg(SCI_ADDTEXT, (WPARAM) 1, (LPARAM) ">");
		//sciMsgr.SendSciMsg(SCI_SETCURRENTPOS, (WPARAM) pos);
		sciMsgr.SendSciMsg(SCI_AUTOCCANCEL);
		sciMsgr.SendSciMsg(SCI_ADDTEXT, (WPARAM) (strlen(actualtext)), (LPARAM) actualtext);
		//sciMsgr.autoCShow(0, "include=\"\"");
		int curpos = sciMsgr.getCurrentPos();
		sciMsgr.SendSciMsg(SCI_GOTOPOS, (WPARAM) (curpos-2) );


	}*/

}

void CFMLPlugin::OnNppSetInfo(const NppData& notpadPlusData)
{
	nppCFShared& cfs = *nppCFShared::Instance();
	cfs.m_nppMsgr.setNppData(notpadPlusData);
	//m_PluginMenu.setNppData(notpadPlusData);
	isNppWndUnicode = ::IsWindowUnicode(notpadPlusData._nppHandle) ? true : false;
	cfs.m_nppMsgr.getPluginsConfigDir(MAX_PATH, cfs.plugindir);
	// char* dbfile;  // REMOVED - no SQLite

	// int multibyteLength = WideCharToMultiByte(CP_UTF8, 0, cfs.plugindir, -1, NULL, 0, 0, 0);
	// dbfile = new char[multibyteLength + 50];
	// //_tcsncat(dbfile, cfs.plugindir, MAX_PATH);

	// WideCharToMultiByte(CP_UTF8, 0, cfs.plugindir, -1, dbfile, multibyteLength, 0, 0);
	// strncat_s(dbfile, multibyteLength + 50, "\\nppColdFusion.db3", 20);
	// cfs.setDB(dbfile);  // REMOVED - no SQLite

}
void CFMLPlugin::wrapCFComment()
{
	const char* starttext = "<!--- ";
	const char* endtext = " --->";

	wrapIn(starttext, endtext);
}

void CFMLPlugin::wrapCFOutput()
{
	const char* starttext = "<cfoutput>";
	const char* endtext = "</cfoutput>";

	wrapIn(starttext, endtext);
}

void CFMLPlugin::wrapCFDump()
{
	const char* starttext = "<cfdump var=\"#";
	const char* endtext = "#\">";

	wrapIn(starttext, endtext);
}
void CFMLPlugin::aboutDlg()
{
	nppCFShared& cfs = *nppCFShared::Instance();

	::MessageBox(cfs.m_nppMsgr.getNppWnd(),
		TEXT("nppColdFusion by Ben Bluemel\n")
		TEXT("updated by Msyu from v0.8.1\n")
		TEXT("http://bitbucket.org/bbluemel/nppcoldfusion/ - \n")
		TEXT("(not available anymore)\n\n"),
		nppColdFusionNS::PLUGIN_VERSION,
		MB_OK);
}
void CFMLPlugin::wrapIn(const char* before, const char* after)
{
	nppCFShared& cfs = *nppCFShared::Instance();

	CSciMessager sciMsgr(cfs.m_nppMsgr.getCurrentScintillaWnd());

	int startpos = sciMsgr.getSelectionStart();
	int endpos = sciMsgr.getSelectionEnd();
	auto startlen = strnlen_s(before, 100);
	auto endlen = strnlen_s(after, 100);
	sciMsgr.SendSciMsg(SCI_BEGINUNDOACTION);
	sciMsgr.goToPos(endpos);
	sciMsgr.SendSciMsg(SCI_ADDTEXT, endlen, (LPARAM)after);
	sciMsgr.goToPos(startpos);
	sciMsgr.SendSciMsg(SCI_ADDTEXT, startlen, (LPARAM)before);
	if (startpos == endpos) {
		sciMsgr.goToPos(startpos + startlen);
	}
	else {
		sciMsgr.goToPos(endpos + startlen + endlen);
	}

	sciMsgr.SendSciMsg(SCI_ENDUNDOACTION);


}
