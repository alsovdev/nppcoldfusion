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
 *  Must match nppColdFusion.xml LexerStyles
 *  Using enum class to ensure unique values and type safety.
 */

enum class StyleId : int
{
    // Base styles (MUST match nppColdFusion.xml styleID exactly)
    DEFAULT           = 0,
    TAG               = 1,
    CF_TAG            = 2,
    ATTRIBUTE         = 3,
    ATTRIBUTEUNKNOWN  = 4,
    NUMBER            = 5,
    DOUBLESTRING      = 6,
    SINGLESTRING      = 7,
    OPERATOR          = 8,
    COMMENT           = 9,
    COMMENTBLOCK      = 10,
    // 11 = gap (not in XML)
    CF_COMMENT        = 12,
    CF_VALUE          = 13,
    CF_FUNCTION       = 14,
    CF_ATTRIBUTE      = 15,   // XML: CFATTRIBUTE
    CF_ATTRIBUTEBAD   = 16,   // XML: CFATTRIBUTEBAD
    LOCALVARS         = 17,   // XML: LOCALVARS
    // 18 = gap (not in XML)
    CFS_RESERVED      = 19,   // XML: CFSRESERVED
    // 20 = gap (not in XML)
    SQL_KEYWORD       = 21,   // XML: SQLKEYWORDS
    JS_KEYWORD        = 22,   // XML: JSKEYWORDS
    CSS_KEYWORD       = 23,   // XML: CSSKEYWORDS
    // 24 = gap (not in XML)

    // Internal styles (not in XML, use extended range to avoid conflicts)
    TAGEND            = 100,
    QUESTION          = 101,
    XCCOMMENT         = 102,
    LOCAL_VARIABLE    = 103,  // Internal: was 18, now LOCALVARS=17 in XML
    CSS_PROPERTY      = 104,  // Internal: was 25
    CF_KEYWORD        = 105,  // Internal: CFScript keywords (not in XML)
    CF_TAGUNKNOWN     = 130,
    CF_NUMBER         = 133,
    CF_DOUBLESTRING   = 134,
    CF_SINGLESTRING   = 135,
    CF_OTHER          = 136,
    CF_ENTITY         = 138,
    CF_TAGEND         = 139,
    CF_XMLSTART       = 140,
    CF_XMLEND         = 141,
    CF_SCRIPT         = 142,
    CF_OUTPUT         = 143,
    CF_QUERY          = 150,
    CF_CDATA          = 145,
    CF_QUESTION       = 146,
    CF_XCCOMMENT      = 148,

    // JavaScript styles (Scintilla default JS lexer styles)
    J_START           = 40,
    J_DEFAULT         = 41,
    J_COMMENT         = 42,
    J_COMMENTLINE     = 43,
    J_COMMENTDOC      = 44,
    J_NUMBER          = 45,
    J_WORD            = 46,
    J_KEYWORD         = 47,
    J_DOUBLESTRING    = 48,
    J_SINGLESTRING    = 49,
    J_SYMBOLS         = 50,
    J_STRINGEOL       = 51,
    J_REGEX           = 52,

    // Java styles (Scintilla default Java lexer styles)
    JA_START          = 55,
    JA_COMMENT        = 57,
    JA_COMMENTLINE    = 58,
    JA_COMMENTDOC     = 59,
    JA_NUMBER         = 60,
    JA_WORD           = 61,
    JA_KEYWORD        = 62,
    JA_DOUBLESTRING   = 63,
    JA_SINGLESTRING   = 64,
    JA_SYMBOLS        = 65,
    JA_STRINGEOL      = 66,
    JA_REGEX          = 67,
};

// Backward compatibility constants (deprecated - use StyleId enum)
// These match the XML styleIDs exactly
const int _DEFAULT           = static_cast<int>(StyleId::DEFAULT);
const int _TAG               = static_cast<int>(StyleId::TAG);
const int CF_TAG             = static_cast<int>(StyleId::CF_TAG);
const int _TAGUNKNOWN        = static_cast<int>(StyleId::CF_TAGUNKNOWN);
const int _ATTRIBUTE         = static_cast<int>(StyleId::ATTRIBUTE);
const int _ATTRIBUTEUNKNOWN  = static_cast<int>(StyleId::ATTRIBUTEUNKNOWN);
const int _NUMBER            = static_cast<int>(StyleId::NUMBER);
const int _DOUBLESTRING      = static_cast<int>(StyleId::DOUBLESTRING);
const int _SINGLESTRING      = static_cast<int>(StyleId::SINGLESTRING);
const int _OPERATOR          = static_cast<int>(StyleId::OPERATOR);
const int _COMMENT           = static_cast<int>(StyleId::COMMENT);
const int _COMMENTBLOCK      = static_cast<int>(StyleId::COMMENTBLOCK);
const int _TAGEND            = static_cast<int>(StyleId::TAGEND);
const int CF_COMMENT         = static_cast<int>(StyleId::CF_COMMENT);
const int CF_VALUE           = static_cast<int>(StyleId::CF_VALUE);
const int CF_FUNCTION        = static_cast<int>(StyleId::CF_FUNCTION);
const int CF_ATTRIBUTE       = static_cast<int>(StyleId::CF_ATTRIBUTE);
const int CF_ATTRIBUTEBAD    = static_cast<int>(StyleId::CF_ATTRIBUTEBAD);
const int LOCALVARS          = static_cast<int>(StyleId::LOCALVARS);
const int LOCAL_VARIABLE     = static_cast<int>(StyleId::LOCAL_VARIABLE);
const int _QUESTION          = static_cast<int>(StyleId::QUESTION);
const int CFS_RESERVED       = static_cast<int>(StyleId::CFS_RESERVED);
const int _XCCOMMENT         = static_cast<int>(StyleId::XCCOMMENT);
const int SQL_KEYWORD        = static_cast<int>(StyleId::SQL_KEYWORD);
const int JS_KEYWORD         = static_cast<int>(StyleId::JS_KEYWORD);
const int CSS_KEYWORD        = static_cast<int>(StyleId::CSS_KEYWORD);
const int CSS_PROPERTY       = static_cast<int>(StyleId::CSS_PROPERTY);
const int CF_KEYWORD         = static_cast<int>(StyleId::CF_KEYWORD);

const int J_START            = static_cast<int>(StyleId::J_START);
const int J_DEFAULT          = static_cast<int>(StyleId::J_DEFAULT);
const int J_COMMENT          = static_cast<int>(StyleId::J_COMMENT);
const int J_COMMENTLINE      = static_cast<int>(StyleId::J_COMMENTLINE);
const int J_COMMENTDOC       = static_cast<int>(StyleId::J_COMMENTDOC);
const int J_NUMBER           = static_cast<int>(StyleId::J_NUMBER);
const int J_WORD             = static_cast<int>(StyleId::J_WORD);
const int J_KEYWORD          = static_cast<int>(StyleId::J_KEYWORD);
const int J_DOUBLESTRING     = static_cast<int>(StyleId::J_DOUBLESTRING);
const int J_SINGLESTRING     = static_cast<int>(StyleId::J_SINGLESTRING);
const int J_SYMBOLS          = static_cast<int>(StyleId::J_SYMBOLS);
const int J_STRINGEOL        = static_cast<int>(StyleId::J_STRINGEOL);
const int J_REGEX            = static_cast<int>(StyleId::J_REGEX);

const int JA_START           = static_cast<int>(StyleId::JA_START);
const int JA_COMMENT         = static_cast<int>(StyleId::JA_COMMENT);
const int JA_COMMENTLINE     = static_cast<int>(StyleId::JA_COMMENTLINE);
const int JA_COMMENTDOC      = static_cast<int>(StyleId::JA_COMMENTDOC);
const int JA_NUMBER          = static_cast<int>(StyleId::JA_NUMBER);
const int JA_WORD            = static_cast<int>(StyleId::JA_WORD);
const int JA_KEYWORD         = static_cast<int>(StyleId::JA_KEYWORD);
const int JA_DOUBLESTRING    = static_cast<int>(StyleId::JA_DOUBLESTRING);
const int JA_SINGLESTRING    = static_cast<int>(StyleId::JA_SINGLESTRING);
const int JA_SYMBOLS         = static_cast<int>(StyleId::JA_SYMBOLS);
const int JA_STRINGEOL       = static_cast<int>(StyleId::JA_STRINGEOL);
const int JA_REGEX           = static_cast<int>(StyleId::JA_REGEX);

const int CF_TAGUNKNOWN      = static_cast<int>(StyleId::CF_TAGUNKNOWN);
const int CF_NUMBER          = static_cast<int>(StyleId::CF_NUMBER);
const int CF_DOUBLESTRING    = static_cast<int>(StyleId::CF_DOUBLESTRING);
const int CF_SINGLESTRING    = static_cast<int>(StyleId::CF_SINGLESTRING);
const int CF_OTHER           = static_cast<int>(StyleId::CF_OTHER);
const int CF_ENTITY          = static_cast<int>(StyleId::CF_ENTITY);
const int CF_TAGEND          = static_cast<int>(StyleId::CF_TAGEND);
const int CF_XMLSTART        = static_cast<int>(StyleId::CF_XMLSTART);
const int CF_XMLEND          = static_cast<int>(StyleId::CF_XMLEND);
const int CF_SCRIPT          = static_cast<int>(StyleId::CF_SCRIPT);
const int CF_OUTPUT          = static_cast<int>(StyleId::CF_OUTPUT);
const int CF_QUERY           = static_cast<int>(StyleId::CF_QUERY);
const int CF_CDATA           = static_cast<int>(StyleId::CF_CDATA);
const int CF_QUESTION        = static_cast<int>(StyleId::CF_QUESTION);
const int CF_XCCOMMENT       = static_cast<int>(StyleId::CF_XCCOMMENT);

} // namespace Styles

} // namespace nppColdFusionNS
#endif