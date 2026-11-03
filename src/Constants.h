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

#ifndef NPP_COLDFUSION_CONSTANTS_H
#define NPP_COLDFUSION_CONSTANTS_H

namespace nppColdFusionNS {
namespace Constants {

// Buffer sizes
constexpr size_t MAX_TAG_LENGTH = 100;
constexpr size_t MAX_WORD_LENGTH = 100;
constexpr size_t LEXER_NAME_BUFFER_SIZE = 64;
constexpr size_t OPEN_TAGS_BUFFER_SIZE = 512;
constexpr size_t MAX_STATE_HISTORY = 32;
constexpr size_t MAX_OPEN_TAGS_POSITIONS = 25;
constexpr size_t TIP_DELIMITERS_SIZE = 32;
constexpr size_t DLL_FILENAME_SIZE = 100;
constexpr size_t INI_FILENAME_SIZE = 100;

// Parameter array sizes (for cffunction::parameters)
constexpr size_t MAX_FUNCTION_PARAMETERS = 10;

} // namespace Constants
} // namespace nppColdFusionNS

#endif // NPP_COLDFUSION_CONSTANTS_H