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

#ifndef NPP_COLDFUSION_DLL_H
#define NPP_COLDFUSION_DLL_H

#include "CFMLPlugin.h"

namespace nppColdFusionNS
{
	
	// Plugin file name possibly obtained directly from plugin dll name
	
	// Plugin display name for menu
	static const generic_string PLUGIN_NAME = TEXT( "&ColdFusion Lexer" );
	//static const generic_string PLUGIN_NAME = TEXT("nppColdFusion"); 

	//exactly the same as Language.name and LexerType.name specified in nppColdFusion.xml
	static const std::string LEXER_NAME = "ColdFusion"; 

	static const generic_string LEXER_STATUS_TEXT = TEXT("(NPP STATUS TEXT): ColdFusion source file ");
}
#endif