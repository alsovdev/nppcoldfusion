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


#include "DllEntry.h"
using namespace nppColdFusion;
CFMLPlugin cfmlPlugin;

BOOL APIENTRY DllMain( HINSTANCE hModule, DWORD reasonForCall, LPVOID /*lpReserved*/ )
{
	switch ( reasonForCall ) {
	case DLL_PROCESS_ATTACH:


		cfmlPlugin.OnDllProcessAttach( hModule );


		break;
	case DLL_PROCESS_DETACH:
		cfmlPlugin.OnDllProcessDetach();
		break;
	}
	return TRUE;
}

#define EXT_LEXER_DECL __declspec( dllexport ) __stdcall




extern "C" {

#ifdef UNICODE
	__declspec( dllexport ) BOOL isUnicode()
	{
		return TRUE;
	}
#endif

	__declspec( dllexport ) const TCHAR * getName()
	{
		//generic_string s = PLUGIN_NAME;
		//const TCHAR* s = TEXT("nppColdFusion");
		return PLUGIN_NAME.c_str();
		//return s; ///***
	}
	__declspec( dllexport ) void setInfo( NppData notpadPlusData )
	{
		cfmlPlugin.nppSetInfo( notpadPlusData );
	}

	__declspec( dllexport ) FuncItem * getFuncsArray( int *nbF )
	{

		return cfmlPlugin.nppGetFuncsArray( nbF );

	}

	__declspec( dllexport ) void beNotified( SCNotification * notifyCode )
	{
		cfmlPlugin.nppBeNotified( notifyCode );

	}
	__declspec( dllexport ) LRESULT messageProc( UINT Message, WPARAM wParam, LPARAM lParam )
	{
		return cfmlPlugin.nppMessageProc( Message, wParam, lParam );
	}


} // End extern "C"

extern "C" int EXT_LEXER_DECL GetLexerCount()
{
	return 1;
}


extern "C" void EXT_LEXER_DECL GetLexerName( unsigned int /*index*/, char *name, int buflength )
{
	*name = 0;
	if ( buflength > 0 ) {
		strncpy_s( name, buflength, LEXER_NAME.c_str(), _TRUNCATE );
		//strncpy_s( name, buflength, "nppColdFusion", _TRUNCATE);
		name[buflength - 1] = L'\0';
	}
}

extern "C" void EXT_LEXER_DECL GetLexerStatusText( unsigned int /*Index*/, TCHAR *desc, int buflength )
{
	if ( buflength > 0 ) {
		generic_strncpy_s( desc, buflength, LEXER_STATUS_TEXT.c_str(), _TRUNCATE );
	}
}


//extern "C" Lexilla::LexerFactoryFunction EXT_LEXER_DECL GetLexerFactory( unsigned int index )
extern "C" __declspec(dllexport) inline Lexilla::LexerFactoryFunction SCI_METHOD GetLexerFactory(unsigned int index)
{
	if ( index == 0 ) {
		return LexerColdFusion::LexerFactory;
	} else {
		return 0;
	}
}

///extern "C" DLLAPI inline ILexer5 * WINAPI CreateLexer(const char* name)
extern "C" __declspec(dllexport) inline Scintilla::ILexer5 * WINAPI CreateLexer(const char* name)
{
	return nppColdFusion::LexerColdFusion::CreateLexer(name);
}

