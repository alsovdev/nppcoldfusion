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


#ifndef NPP_CF_STYLES
#define NPP_CF_STYLES

namespace nppColdFusionNS
{

namespace Styles
{

/*
 *	List all of your styleIDs as found in your style xml file.
 *
 */

const int _DEFAULT = 0;
const int _TAG = 1;
const int CF_TAG = 2;
const int _TAGUNKNOWN = 22;
const int _ATTRIBUTE = 3;
const int _ATTRIBUTEUNKNOWN = 4;
const int _NUMBER = 5;
const int _DOUBLESTRING = 6;
const int _SINGLESTRING = 7;
const int _OPERATOR = 8;
const int _COMMENT = 9;
const int _COMMENTBLOCK = 10;
const int _TAGEND = 11;
const int CF_COMMENT = 12;
//const int _XMLSTART = 12;
const int CF_VALUE = 13;
const int CF_FUNCTION = 14;
const int CF_KEYWORD = 15;
const int CF_ATTRIBUTE = 16;
const int CF_ATTRIBUTEBAD = 17;
const int LOCAL_VARIABLE = 18;
const int _QUESTION = 19;
const int CFS_RESERVED = 20;
const int _XCCOMMENT = 21;
const int SQL_KEYWORD = 22;
const int JS_KEYWORD = 23;
const int CSS_KEYWORD = 24;
const int CSS_PROPERTY = 25;

const int J_START = 40;
const int J_DEFAULT = 41;
const int J_COMMENT = 42;
const int J_COMMENTLINE = 43;
const int J_COMMENTDOC = 44;
const int J_NUMBER = 45;
const int J_WORD = 46;
const int J_KEYWORD = 47;
const int J_DOUBLESTRING = 48;
const int J_SINGLESTRING = 49;
const int J_SYMBOLS = 50;
const int J_STRINGEOL = 51;
const int J_REGEX = 52;
const int JA_START = 55;
const int JA_COMMENT = 57;
const int JA_COMMENTLINE = 58;
const int JA_COMMENTDOC = 59;
const int JA_NUMBER = 60;
const int JA_WORD = 61;
const int JA_KEYWORD = 62;
const int JA_DOUBLESTRING = 63;
const int JA_SINGLESTRING = 64;
const int JA_SYMBOLS = 65;
const int JA_STRINGEOL = 66;
const int JA_REGEX = 67;
//const int CF_TAG = 22;
const int CF_TAGUNKNOWN = 130;
//const int CF_ATTRIBUTE = 131;
//const int CF_ATTRIBUTEUNKNOWN = 132;
const int CF_NUMBER = 133;
const int CF_DOUBLESTRING = 72;
const int CF_SINGLESTRING = 135;
const int CF_OTHER = 136;
const int CF_ENTITY = 138;
const int CF_TAGEND = 139;
const int CF_XMLSTART = 140;
const int CF_XMLEND = 141;
const int CF_SCRIPT = 142;
const int CF_OUTPUT = 143;
const int CF_QUERY = 24;
const int CF_CDATA = 145;
const int CF_QUESTION = 146;

const int CF_XCCOMMENT = 148;


};  // End namespace Style

};
#endif