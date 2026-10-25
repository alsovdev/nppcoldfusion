#!/usr/bin/env python3
"""
generate_db.py — Генерация nppColdFusion.db3 и nppColdFusion.xml из YAML источников

Usage:
    python scripts/generate_db.py
"""

import sqlite3
import yaml
import os
import sys
from pathlib import Path

# Paths
REPO_ROOT = Path(__file__).parent.parent
DATA_DIR = REPO_ROOT / "data"
SRC_DIR = REPO_ROOT / "src"
DB_PATH = SRC_DIR / "nppColdFusion.db3"
XML_PATH = SRC_DIR / "nppColdFusion.xml"

# ============================================================
# SCHEMA DEFINITIONS
# ============================================================

SCHEMA_SQL = """
-- Tags table
CREATE TABLE IF NOT EXISTS tags (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(32) UNIQUE NOT NULL,
    isautoclosing BOOLEAN DEFAULT 0,
    isclosingtagrequired BOOLEAN DEFAULT 0
);

-- Attributes table
CREATE TABLE IF NOT EXISTS attributes (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(32) NOT NULL,
    typeid INTEGER DEFAULT 0,
    FOREIGN KEY (typeid) REFERENCES types(id)
);

-- Tag-Attribute mapping
CREATE TABLE IF NOT EXISTS tagattributes (
    tagid INTEGER NOT NULL,
    attributeid INTEGER NOT NULL,
    "order" INTEGER DEFAULT 0,
    required BOOLEAN DEFAULT 0,
    PRIMARY KEY (tagid, attributeid),
    FOREIGN KEY (tagid) REFERENCES tags(id),
    FOREIGN KEY (attributeid) REFERENCES attributes(id)
);

-- Namespaces
CREATE TABLE IF NOT EXISTS namespaces (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(32) UNIQUE NOT NULL,
    enabled BOOLEAN DEFAULT 1
);

-- Namespace-Tag mapping
CREATE TABLE IF NOT EXISTS namespacetags (
    namespaceid INTEGER NOT NULL,
    tagid INTEGER NOT NULL,
    PRIMARY KEY (namespaceid, tagid),
    FOREIGN KEY (namespaceid) REFERENCES namespaces(id),
    FOREIGN KEY (tagid) REFERENCES tags(id)
);

-- Types
CREATE TABLE IF NOT EXISTS types (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(32) UNIQUE NOT NULL,
    basetype VARCHAR(32) DEFAULT ''
);

-- Keyword sets
CREATE TABLE IF NOT EXISTS keywordsets (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name CHAR(1) UNIQUE NOT NULL
);

-- Keywords
CREATE TABLE IF NOT EXISTS keywords (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(50) UNIQUE NOT NULL
);

-- KeywordSet-Keyword mapping
CREATE TABLE IF NOT EXISTS keywordsetkeywords (
    keywordsetid INTEGER NOT NULL,
    keywordid INTEGER NOT NULL,
    PRIMARY KEY (keywordsetid, keywordid),
    FOREIGN KEY (keywordsetid) REFERENCES keywordsets(id),
    FOREIGN KEY (keywordid) REFERENCES keywords(id)
);

-- Namespace-KeywordSet mapping
CREATE TABLE IF NOT EXISTS namespacekeywordsets (
    namespaceid INTEGER NOT NULL,
    keywordsetid INTEGER NOT NULL,
    PRIMARY KEY (namespaceid, keywordsetid),
    FOREIGN KEY (namespaceid) REFERENCES namespaces(id),
    FOREIGN KEY (keywordsetid) REFERENCES keywordsets(id)
);

-- Functions
CREATE TABLE IF NOT EXISTS functions (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(64) UNIQUE NOT NULL,
    returntypeid INTEGER DEFAULT 0,
    FOREIGN KEY (returntypeid) REFERENCES types(id)
);

-- Parameters
CREATE TABLE IF NOT EXISTS parameters (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name VARCHAR(32) UNIQUE NOT NULL,
    typeid INTEGER DEFAULT 0,
    FOREIGN KEY (typeid) REFERENCES types(id)
);

-- Function-Parameter mapping
CREATE TABLE IF NOT EXISTS functionparameters (
    functionid INTEGER NOT NULL,
    parameterid INTEGER NOT NULL,
    required BOOLEAN DEFAULT 0,
    PRIMARY KEY (functionid, parameterid),
    FOREIGN KEY (functionid) REFERENCES functions(id),
    FOREIGN KEY (parameterid) REFERENCES parameters(id)
);

-- Options
CREATE TABLE IF NOT EXISTS options (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    value VARCHAR(32) UNIQUE NOT NULL
);

-- Type-Option mapping
CREATE TABLE IF NOT EXISTS typeoptions (
    typeid INTEGER NOT NULL,
    optionid INTEGER NOT NULL,
    PRIMARY KEY (typeid, optionid),
    FOREIGN KEY (typeid) REFERENCES types(id),
    FOREIGN KEY (optionid) REFERENCES options(id)
);

-- sqlite_sequence for autoincrement
-- SQLite creates this automatically for AUTOINCREMENT tables
-- CREATE TABLE IF NOT EXISTS sqlite_sequence (name, seq);
"""

# ============================================================
# NAMESPACE MAPPING
# ============================================================

NAMESPACE_MAPPING = {
    # ColdFusion namespace (id=1)
    "ColdFusion 9": [
        # All cf* tags
        "cfabort", "cfajaximport", "cfajaxproxy", "cfapplet", "cfapplication",
        "cfargument", "cfassociate", "cfbreak", "cfcache", "cfcalendar",
        "cfcase", "cfcatch", "cfchart", "cfchartdata", "cfchartseries",
        "cfcol", "cfcollection", "cfcomponent", "cfcontent", "cfcontinue",
        "cfcookie", "cfdbinfo", "cfdefaultcase", "cfdirectory", "cfdiv",
        "cfdocument", "cfdocumentitem", "cfdocumentsection", "cfdump",
        "cfelse", "cfelseif", "cferror", "cfexchangecalendar", "cfexchangeconnection",
        "cfexchangecontact", "cfexchangefilter", "cfexchangemail", "cfexchangetask",
        "cfexecute", "cfexit", "cffeed", "cffile", "cffileupload", "cffinally",
        "cfflush", "cfform", "cfformgroup", "cfformitem", "cfftp", "cffunction",
        "cfgrid", "cfgridcolumn", "cfgridrow", "cfgridupdate", "cfheader",
        "cfhtmlhead", "cfhttp", "cfhttpparam", "cfif", "cfimage", "cfimap",
        "cfimport", "cfinclude", "cfindex", "cfinput", "cfinsert", "cfinterface",
        "cfinvoke", "cfinvokeargument", "cfldap", "cflayout", "cflayoutarea",
        "cflocation", "cflock", "cflog", "cflogin", "cfloginuser", "cflogout",
        "cfloop", "cfmail", "cfmailparam", "cfmailpart", "cfmap", "cfmapitem",
        "cfmediaplayer", "cfmenu", "cfmenuitem", "cfmessagebox", "cfmodule",
        "cfntauthenticate", "cfobject", "cfobjectcache", "cfoutput", "cfparam",
        "cfpdf", "cfpdfform", "cfpdfformparam", "cfpdfparam", "cfpdfsubform",
        "cfpod", "cfpop", "cfpresentation", "cfpresentationslide", "cfpresenter",
        "cfprint", "cfprocessingdirective", "cfprocparam", "cfprocresult",
        "cfprogressbar", "cfproperty", "cfquery", "cfqueryparam", "cfregistry",
        "cfreport", "cfreportparam", "cfrethrow", "cfreturn", "cfsavecontent",
        "cfschedule", "cfscript", "cfsearch", "cfselect", "cfset", "cfsetting",
        "cfsharepoint", "cfsilent", "cfslider", "cfspreadsheet", "cfsprydataset",
        "cfstoredproc", "cfswitch", "cftable", "cftextarea", "cftextinput",
        "cfthread", "cfthrow", "cftimer", "cftooltip", "cftrace", "cftransaction",
        "cftree", "cftreeitem", "cftry", "cfupdate", "cfwddx", "cfwindow",
        "cfxml", "cfzip", "cfzipparam", "cfwebsocket", "cfclient", "cfpdfform",
    ],
    # HTML namespace (id=2)
    "HTML": [
        "!DOCTYPE", "a", "abbr", "acronym", "address", "applet", "area",
        "article", "aside", "audio", "b", "base", "basefont", "bdo", "bgsound",
        "big", "blink", "blockquote", "body", "br", "button", "canvas", "caption",
        "center", "cite", "code", "col", "colgroup", "command", "comment",
        "datalist", "dd", "del", "details", "dfn", "dir", "div", "dl", "dt",
        "em", "embed", "fieldset", "figcaption", "figure", "font", "footer",
        "form", "frame", "frameset", "h1", "h2", "h3", "h4", "h5", "h6",
        "head", "header", "hgroup", "hr", "html", "i", "iframe", "ilayer",
        "img", "input", "ins", "isindex", "kbd", "keygen", "label", "layer",
        "legend", "li", "link", "map", "mark", "marquee", "math", "menu",
        "meta", "meter", "nav", "nobr", "noembed", "noframes", "noscript",
        "object", "ol", "optgroup", "option", "output", "p", "param", "pre",
        "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "section",
        "select", "small", "source", "span", "strike", "strong", "style",
        "sub", "summary", "sup", "svg", "table", "tbody", "td", "textarea",
        "tfoot", "th", "thead", "time", "title", "tr", "tt", "u", "ul",
        "var", "video", "wbr", "xml", "xmp"
    ],
    # SQL namespace (id=3)
    "SQL": [
        "SELECT", "FROM", "WHERE", "INSERT", "UPDATE", "DELETE", "JOIN",
        "INNER", "LEFT", "RIGHT", "OUTER", "ON", "AS", "GROUP", "BY",
        "ORDER", "HAVING", "LIMIT", "OFFSET", "UNION", "DISTINCT", "NULL",
        "NOT", "AND", "OR", "IN", "LIKE", "BETWEEN", "IS", "EXISTS",
        "CASE", "WHEN", "THEN", "ELSE", "END", "CREATE", "TABLE", "INDEX",
        "VIEW", "DROP", "ALTER", "ADD", "COLUMN", "PRIMARY", "KEY",
        "FOREIGN", "REFERENCES", "CONSTRAINT", "DEFAULT", "AUTO_INCREMENT",
        "COUNT", "SUM", "AVG", "MIN", "MAX", "NOW", "CURRENT_DATE",
        "CURRENT_TIME", "CURRENT_TIMESTAMP"
    ],
    # Javascript namespace (id=4)
    "Javascript": [
        "var", "let", "const", "function", "return", "if", "else", "for",
        "while", "do", "switch", "case", "default", "break", "continue",
        "try", "catch", "finally", "throw", "new", "this", "typeof",
        "instanceof", "in", "delete", "void", "class", "extends", "super",
        "import", "export", "from", "as", "async", "await", "yield",
        "null", "undefined", "true", "false", "console", "log", "error",
        "window", "document", "element", "event", "promise", "then", "catch"
    ],
    # CSS namespace (id=5)
    "CSS": [
        "color", "background", "border", "margin", "padding", "width",
        "height", "display", "position", "top", "left", "right", "bottom",
        "float", "clear", "font", "text-align", "overflow", "visibility",
        "z-index", "opacity", "transform", "transition", "animation",
        "flex", "grid", "justify-content", "align-items", "gap"
    ],
}


# ============================================================
# KEYWORD SET MAPPING
# ============================================================

KEYWORDSET_MAPPING = {
    1: "SQL Keywords",      # namespace 3 -> SQL
    2: "JS Keywords",       # namespace 4 -> Javascript
    3: "CSS Keywords",      # namespace 5 -> CSS
    4: "CF Functions (Temporary)",  # namespace 1 -> ColdFusion
    5: "CF Reserved Words (2018/2021)",
    6: "Array Member Functions",
    7: "Struct Member Functions",
    8: "String Member Functions",
    9: "Query Member Functions",
}

NAMESPACE_KEYWORDSET_MAP = {
    "ColdFusion 9": [4, 5, 6, 7, 8, 9],
    "HTML": [],
    "SQL": [1],
    "Javascript": [2],
    "CSS": [3],
}


# ============================================================
# MAIN GENERATION FUNCTIONS
# ============================================================

def load_yaml(filename):
    """Load YAML file from data directory."""
    path = DATA_DIR / filename
    if not path.exists():
        print(f"Warning: {path} not found")
        return {}
    with open(path, 'r') as f:
        return yaml.safe_load(f) or {}


def init_database():
    """Create fresh database with schema."""
    if DB_PATH.exists():
        DB_PATH.unlink()
    
    conn = sqlite3.connect(DB_PATH)
    conn.executescript(SCHEMA_SQL)
    conn.commit()
    return conn


def insert_types(conn, types_data):
    """Insert type definitions."""
    cursor = conn.cursor()
    type_id_map = {}
    
    for type_name, type_info in types_data.items():
        cursor.execute(
            "INSERT OR IGNORE INTO types (name, basetype) VALUES (?, ?)",
            (type_name, type_info.get('basetype', ''))
        )
        cursor.execute("SELECT id FROM types WHERE name = ?", (type_name,))
        row = cursor.fetchone()
        if row:
            type_id_map[type_name] = row[0]
    
    conn.commit()
    return type_id_map


def insert_options(conn, tags_data, type_id_map):
    """Extract enum options from tag attributes and insert into options/typeoptions."""
    cursor = conn.cursor()
    option_id_map = {}
    type_option_map = {}
    
    # Collect all enum types from tag attributes
    enum_types = set()
    for tag_data in tags_data.values():
        for attr in tag_data.get('attributes', []):
            type_name = attr.get('type', '')
            if type_name and type_name not in type_id_map and '-' in type_name:
                # Likely an enum type (e.g., cfdocument-format)
                enum_types.add(type_name)
    
    # Insert enum types and their options
    for enum_type in sorted(enum_types):
        # Insert type if not exists
        cursor.execute("INSERT OR IGNORE INTO types (name, basetype) VALUES (?, 'enum')", (enum_type,))
        cursor.execute("SELECT id FROM types WHERE name = ?", (enum_type,))
        row = cursor.fetchone()
        if row:
            type_id_map[enum_type] = row[0]
            type_id = row[0]
            
            # Generate options from enum type name (e.g., cfdocument-format -> pdf, flash, etc.)
            # For now, insert placeholder options
            base_name = enum_type.split('-')[-1] if '-' in enum_type else enum_type
            options = [f"{base_name}_option1", f"{base_name}_option2"]
            
            for opt in options:
                cursor.execute("INSERT OR IGNORE INTO options (value) VALUES (?)", (opt,))
                cursor.execute("SELECT id FROM options WHERE value = ?", (opt,))
                opt_row = cursor.fetchone()
                if opt_row:
                    cursor.execute(
                        "INSERT OR IGNORE INTO typeoptions (typeid, optionid) VALUES (?, ?)",
                        (type_id, opt_row[0])
                    )
    
    conn.commit()


def insert_tags(conn, tags_data, type_id_map):
    """Insert tags and their attributes."""
    cursor = conn.cursor()
    tag_id_map = {}
    
    for tag_name, tag_data in tags_data.items():
        cursor.execute(
            "INSERT OR IGNORE INTO tags (name, isautoclosing, isclosingtagrequired) VALUES (?, ?, ?)",
            (tag_name, tag_data.get('autoclosing', False), tag_data.get('closing_required', False))
        )
        cursor.execute("SELECT id FROM tags WHERE name = ?", (tag_name,))
        row = cursor.fetchone()
        if row:
            tag_id = row[0]
            tag_id_map[tag_name] = tag_id
            
            # Insert attributes
            for idx, attr in enumerate(tag_data.get('attributes', [])):
                attr_name = attr.get('name', '')
                attr_type = attr.get('type', 'String')
                attr_required = attr.get('required', False)
                
                # Get or create attribute
                cursor.execute("INSERT OR IGNORE INTO attributes (name, typeid) VALUES (?, ?)",
                              (attr_name, type_id_map.get(attr_type, 0)))
                cursor.execute("SELECT id FROM attributes WHERE name = ?", (attr_name,))
                attr_row = cursor.fetchone()
                if attr_row:
                    attr_id = attr_row[0]
                    # Update typeid if we have it
                    if attr_type in type_id_map:
                        cursor.execute("UPDATE attributes SET typeid = ? WHERE id = ?",
                                      (type_id_map[attr_type], attr_id))
                    
                    # Link tag-attribute
                    cursor.execute(
                        "INSERT OR IGNORE INTO tagattributes (tagid, attributeid, \"order\", required) VALUES (?, ?, ?, ?)",
                        (tag_id, attr_id, idx, attr_required)
                    )
    
    conn.commit()
    return tag_id_map


def insert_namespaces(conn):
    """Insert namespaces and their tags."""
    cursor = conn.cursor()
    ns_id_map = {}
    
    for ns_name, tags_list in NAMESPACE_MAPPING.items():
        cursor.execute(
            "INSERT OR IGNORE INTO namespaces (name, enabled) VALUES (?, 1)",
            (ns_name,)
        )
        cursor.execute("SELECT id FROM namespaces WHERE name = ?", (ns_name,))
        row = cursor.fetchone()
        if row:
            ns_id = row[0]
            ns_id_map[ns_name] = ns_id
            
            # Link tags to namespace
            cursor.execute("SELECT id, name FROM tags")
            all_tags = {name: tid for tid, name in cursor.fetchall()}
            
            for tag_name in tags_list:
                if tag_name in all_tags:
                    cursor.execute(
                        "INSERT OR IGNORE INTO namespacetags (namespaceid, tagid) VALUES (?, ?)",
                        (ns_id, all_tags[tag_name])
                    )
    
    conn.commit()
    return ns_id_map


def insert_keywords(conn, keywords_data):
    """Insert keywords and keyword sets."""
    cursor = conn.cursor()
    kwset_id_map = {}
    kw_id_map = {}
    
    # Insert keyword sets
    for set_id, set_name in KEYWORDSET_MAPPING.items():
        cursor.execute("INSERT OR IGNORE INTO keywordsets (id, name) VALUES (?, ?)",
                      (set_id, set_name))
        kwset_id_map[set_name] = set_id
    
    # Insert keywords and map to sets
    for set_name, kw_list in keywords_data.items():
        if set_name not in kwset_id_map:
            # Assign new ID
            new_id = max(kwset_id_map.values()) + 1
            cursor.execute("INSERT OR IGNORE INTO keywordsets (id, name) VALUES (?, ?)",
                          (new_id, set_name))
            kwset_id_map[set_name] = new_id
        
        set_id = kwset_id_map[set_name]
        
        for kw in kw_list:
            cursor.execute("INSERT OR IGNORE INTO keywords (name) VALUES (?)", (kw,))
            cursor.execute("SELECT id FROM keywords WHERE name = ?", (kw,))
            row = cursor.fetchone()
            if row:
                kw_id = row[0]
                kw_id_map[kw] = kw_id
                cursor.execute(
                    "INSERT OR IGNORE INTO keywordsetkeywords (keywordsetid, keywordid) VALUES (?, ?)",
                    (set_id, kw_id)
                )
    
    conn.commit()
    return kwset_id_map, kw_id_map


def insert_namespace_keywordsets(conn, kwset_id_map):
    """Link namespaces to keyword sets."""
    cursor = conn.cursor()
    
    cursor.execute("SELECT id, name FROM namespaces")
    namespaces = {name: nsid for nsid, name in cursor.fetchall()}
    
    for ns_name, kwset_ids in NAMESPACE_KEYWORDSET_MAP.items():
        if ns_name in namespaces:
            ns_id = namespaces[ns_name]
            for kwset_id in kwset_ids:
                cursor.execute(
                    "INSERT OR IGNORE INTO namespacekeywordsets (namespaceid, keywordsetid) VALUES (?, ?)",
                    (ns_id, kwset_id)
                )
    
    conn.commit()


def insert_functions(conn, functions_data, type_id_map):
    """Insert functions and their parameters."""
    cursor = conn.cursor()
    func_id_map = {}
    param_id_map = {}
    
    for func_name, func_data in functions_data.items():
        return_type = func_data.get('return_type', 'any')
        return_type_id = type_id_map.get(return_type, 0)
        
        cursor.execute(
            "INSERT OR IGNORE INTO functions (name, returntypeid) VALUES (?, ?)",
            (func_name, return_type_id)
        )
        cursor.execute("SELECT id FROM functions WHERE name = ?", (func_name,))
        row = cursor.fetchone()
        if row:
            func_id = row[0]
            func_id_map[func_name] = func_id
            
            for param in func_data.get('parameters', []):
                param_name = param.get('name', '')
                param_type = param.get('type', 'any')
                param_required = param.get('required', False)
                param_type_id = type_id_map.get(param_type, 0)
                
                cursor.execute(
                    "INSERT OR IGNORE INTO parameters (name, typeid) VALUES (?, ?)",
                    (param_name, param_type_id)
                )
                cursor.execute("SELECT id FROM parameters WHERE name = ?", (param_name,))
                p_row = cursor.fetchone()
                if p_row:
                    param_id = p_row[0]
                    param_id_map[param_name] = param_id
                    cursor.execute(
                        "INSERT OR IGNORE INTO functionparameters (functionid, parameterid, required) VALUES (?, ?, ?)",
                        (func_id, param_id, param_required)
                    )
    
    conn.commit()
    return func_id_map


def generate_xml(tags_data, keywords_data):
    """Generate nppColdFusion.xml from tags data."""
    lines = []
    lines.append('<?xml version="1.0" encoding="Windows-1252" ?>')
    lines.append('<NotepadPlus>')
    lines.append('    <Languages>')
    lines.append('        <Language name="ColdFusion" ext="cfm cfc cfml" commentStart="<!--" commentEnd="-->">')
    lines.append('            <Keywords name="0"></Keywords>')
    lines.append('            <Keywords name="1"></Keywords>')
    lines.append('            <Keywords name="2"></Keywords>')
    lines.append('            <Keywords name="3"></Keywords>')
    lines.append('            <Keywords name="4">active after before first first-child first-letter first-line focus hover lang left link right visited</Keywords>')
    lines.append('            <Keywords name="5"></Keywords>')
    lines.append('            <Keywords name="6"></Keywords>')
    lines.append('            <Keywords name="7"></Keywords>')
    lines.append('        </Language>')
    lines.append('    </Languages>')
    lines.append('    <LexerStyles>')
    lines.append('        <LexerType name="ColdFusion" desc="ColdFusion" excluded="no">')
    
    # Standard styles (from original XML)
    styles = [
        (0, "DEFAULT", "000000", "FFFFFF", "", "1", "", 0),
        (1, "TAG", "0000FF", "FFFFFF", "", "0", "", 0),
        (2, "CFTAG", "804000", "FFFFFF", "", "0", "", 1),
        (3, "ATTRIBUTE", "0080C0", "FFFFFF", "", "0", "", None),
        (4, "ATTRIBUTEUNKNOWN", "FF0000", "FFFFFF", "", "0", "", None),
        (5, "NUMBER", "FF8000", "FFFFFF", "", "0", "", None),
        (6, "DOUBLESTRING", "8000FF", "FFFFFF", "", "1", "", None),
        (7, "SINGLESTRING", "8000FF", "FFFFFF", "", "1", "", None),
        (8, "OPERATOR", "000080", "FFFFFF", "", "1", "", None),
        (9, "COMMENT", "008000", "FFFFFF", "", "0", "", None),
        (10, "COMMENTBLOCK", "008000", "FFFFFF", "", "0", "", None),
        (12, "CFCOMMENT", "408080", "FFFFFF", "", "2", "", None),
        (13, "CFVALUE", "FF8000", "FFFFFF", "", "0", "", None),
        (14, "CFFUNCTION", "808000", "FFFFFF", "", "0", "", 2),
        (15, "CFATTRIBUTE", "800080", "FFFFFF", "", "0", "", None),
        (16, "CFATTRIBUTEBAD", "FF0000", "FFFFFF", "", "0", "", None),
        (17, "LOCALVARS", "000000", "F2F2F2", "", "1", "", None),
        (19, "CFSRESERVED", "804000", "FFFFFF", "", "0", "", None),
        (21, "SQLKEYWORDS", "0000FF", "FFFFFF", "", "0", "", 6),
        (22, "JSKEYWORDS", "871F78", "FFFFFF", "", "0", "", 5),
        (23, "CSSKEYWORDS", "871F78", "FFFFFF", "", "0", "", 7),
    ]
    
    for style_id, name, fg, bg, font_name, font_style, font_size, keyword_class in styles:
        kc_attr = f' keywordClass="{keyword_class}"' if keyword_class is not None else ''
        lines.append(f'            <WordsStyle name="{name}" styleID="{style_id}" fgColor="{fg}" bgColor="{bg}" fontName="{font_name}" fontStyle="{font_style}" fontSize="{font_size}"{kc_attr} />')
    
    lines.append('        </LexerType>')
    lines.append('    </LexerStyles>')
    lines.append('</NotepadPlus>')
    
    with open(XML_PATH, 'w', encoding='windows-1252') as f:
        f.write('\n'.join(lines))
    
    print(f'Generated {XML_PATH}')


def main():
    print("Loading YAML data sources...")
    tags_data = load_yaml("tags.yaml")
    functions_data = load_yaml("functions.yaml")
    keywords_data = load_yaml("keywords.yaml")
    types_data = load_yaml("types.yaml")
    namespaces_data = load_yaml("namespaces.yaml")
    
    print(f"Tags: {len(tags_data)}")
    print(f"Functions: {len(functions_data)}")
    print(f"Keyword sets: {len(keywords_data)}")
    print(f"Types: {len(types_data)}")
    print(f"Namespaces: {len(namespaces_data)}")
    
    print("\nInitializing database...")
    conn = init_database()
    
    print("Inserting types...")
    type_id_map = insert_types(conn, types_data)
    print(f"Types inserted: {len(type_id_map)}")
    
    print("Inserting tags and attributes...")
    tag_id_map = insert_tags(conn, tags_data, type_id_map)
    print(f"Tags inserted: {len(tag_id_map)}")
    
    print("Inserting options/enums...")
    insert_options(conn, tags_data, type_id_map)
    
    print("Inserting namespaces...")
    ns_id_map = insert_namespaces(conn)
    print(f"Namespaces: {len(ns_id_map)}")
    
    print("Inserting keywords...")
    kwset_id_map, kw_id_map = insert_keywords(conn, keywords_data)
    print(f"Keyword sets: {len(kwset_id_map)}, Keywords: {len(kw_id_map)}")
    
    print("Linking namespaces to keyword sets...")
    insert_namespace_keywordsets(conn, kwset_id_map)
    
    print("Inserting functions...")
    func_id_map = insert_functions(conn, functions_data, type_id_map)
    print(f"Functions inserted: {len(func_id_map)}")
    
    conn.close()
    
    print("\nGenerating XML...")
    generate_xml(tags_data, keywords_data)
    
    print("\n✅ Generation complete!")
    print(f"Database: {DB_PATH}")
    print(f"XML: {XML_PATH}")


if __name__ == "__main__":
    main()