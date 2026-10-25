#!/usr/bin/env python3
"""
generate_autocomplete.py — Генерация C++ заголовка с данными для автодополнения из YAML источников

Usage:
    python scripts/generate_autocomplete.py

Output:
    src/AutoCompleteData.h — static constexpr структуры для автодополнения
"""

import yaml
import os
import sys
from pathlib import Path

# Paths
REPO_ROOT = Path(__file__).parent.parent
DATA_DIR = REPO_ROOT / "data"
SRC_DIR = REPO_ROOT / "src"
OUTPUT_PATH = SRC_DIR / "AutoCompleteData.h"

# ============================================================
# NAMESPACE MAPPING (matches generate_db.py)
# ============================================================

NAMESPACE_MAPPING = {
    "ColdFusion 9": [
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
    "Javascript": [
        "var", "let", "const", "function", "return", "if", "else", "for",
        "while", "do", "switch", "case", "default", "break", "continue",
        "try", "catch", "finally", "throw", "new", "this", "typeof",
        "instanceof", "in", "delete", "void", "class", "extends", "super",
        "import", "export", "from", "as", "async", "await", "yield",
        "null", "undefined", "true", "false", "console", "log", "error",
        "window", "document", "element", "event", "promise", "then", "catch"
    ],
    "CSS": [
        "color", "background", "border", "margin", "padding", "width",
        "height", "display", "position", "top", "left", "right", "bottom",
        "float", "clear", "font", "text-align", "overflow", "visibility",
        "z-index", "opacity", "transform", "transition", "animation",
        "flex", "grid", "justify-content", "align-items", "gap"
    ],
}

KEYWORDSET_MAPPING = {
    1: "SQL Keywords",
    2: "JS Keywords",
    3: "CSS Keywords",
    4: "CF Functions (Temporary)",
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
# HELPERS
# ============================================================

def load_yaml(filename):
    path = DATA_DIR / filename
    if not path.exists():
        print("Warning: {} not found".format(path))
        return {}
    with open(path, 'r') as f:
        return yaml.safe_load(f) or {}

def escape_cpp_string(s):
    """Escape string for C++ string literal."""
    return s.replace('\\', '\\\\').replace('"', '\\"').replace('\n', '\\n').replace('\r', '\\r').replace('\t', '\\t')

def cpp_identifier(s):
    """Convert string to valid C++ identifier."""
    return s.replace('-', '_').replace(' ', '_').replace('.', '_').replace('!', '').replace('@', '').replace('#', '').replace('$', '').replace('%', '').replace('^', '').replace('&', '').replace('*', '').replace('(', '').replace(')', '').replace('+', '').replace('=', '').replace('[', '').replace(']', '').replace('{', '').replace('}', '').replace('|', '').replace('\\', '').replace(':', '').replace(';', '').replace('"', '').replace("'", '').replace('<', '').replace('>', '').replace(',', '').replace('?', '').replace('/', '')

# ============================================================
# MAIN GENERATION
# ============================================================

def generate_header():
    tags_data = load_yaml("tags.yaml")
    keywords_data = load_yaml("keywords.yaml")
    types_data = load_yaml("types.yaml")
    namespaces_data = load_yaml("namespaces.yaml")

    lines = []
    append = lines.append

    append("// Auto-generated from YAML sources by generate_autocomplete.py")
    append("// DO NOT EDIT MANUALLY")
    append("")
    append("#ifndef NPP_AUTOCMPLETE_DATA_H")
    append("#define NPP_AUTOCMPLETE_DATA_H")
    append("")
    append("#include <array>")
    append("#include <string_view>")
    append("#include <unordered_map>")
    append("#include <algorithm>")
    append("")
    append("namespace nppColdFusionNS {")
    append("namespace AutoCompleteData {")
    append("")

    # ---- Namespaces ----
    append("// ============================================================")
    append("// Namespaces")
    append("// ============================================================")
    append("")
    append("enum class NamespaceId : uint8_t {")
    for i, ns_name in enumerate(NAMESPACE_MAPPING.keys()):
        enum_name = cpp_identifier(ns_name).upper()
        append("    " + enum_name + " = " + str(i + 1) + ",")
    append("    COUNT")
    append("};")
    append("")

    # ---- Tag Data ----
    append("// ============================================================")
    append("// Tag attributes (per tag)")
    append("// ============================================================")
    append("")

    # TagAttribute struct
    append("struct TagAttribute {")
    append("    const char* name;")
    append("    bool required;")
    append("};")
    append("")

    # TagInfo struct
    append("struct TagInfo {")
    append("    const char* name;")
    append("    bool autoclosing;")
    append("    bool closing_required;")
    append("    const TagAttribute* attributes;")
    append("    size_t attr_count;")
    append("};")
    append("")

    # Generate per-tag attribute arrays
    append("// Per-tag attribute arrays")
    for tag_name, tag_data in sorted(tags_data.items()):
        attrs = tag_data.get('attributes', [])
        if attrs:
            safe_name = cpp_identifier(tag_name)
            append("constexpr TagAttribute " + safe_name + "_attrs[] = {")
            for attr in attrs:
                attr_name = attr.get('name', '')
                required = attr.get('required', False)
                escaped_name = escape_cpp_string(attr_name)
                append("    {\"" + escaped_name + "\", " + str(required).lower() + "},")
            append("};")
            append("")

    # Generate TagInfo array (all tags)
    append("constexpr TagInfo all_tags[] = {")
    for tag_name, tag_data in sorted(tags_data.items()):
        safe_name = cpp_identifier(tag_name)
        autoclosing = tag_data.get('autoclosing', False)
        closing_required = tag_data.get('closing_required', False)
        attrs = tag_data.get('attributes', [])
        escaped_tag = escape_cpp_string(tag_name)
        if attrs:
            append("    {\"" + escaped_tag + "\", " + str(autoclosing).lower() + ", " + str(closing_required).lower() + ", " + safe_name + "_attrs, " + str(len(attrs)) + "},")
        else:
            append("    {\"" + escaped_tag + "\", " + str(autoclosing).lower() + ", " + str(closing_required).lower() + ", nullptr, 0},")
    append("};")
    append("")

    # ---- Namespace -> Tag indices ----
    append("// Namespace -> tag index mapping (indices into all_tags)")
    append("struct NamespaceTags {")
    append("    const uint16_t* indices;")
    append("    size_t count;")
    append("};")
    append("")

    for ns_name, tag_list in NAMESPACE_MAPPING.items():
        safe_ns = cpp_identifier(ns_name)
        tag_indices = []
        for i, (tname, _) in enumerate(sorted(tags_data.items())):
            if tname in tag_list:
                tag_indices.append(str(i))
        append("constexpr uint16_t " + safe_ns + "_tag_indices[] = { " + ', '.join(tag_indices) + " };")
    append("")

    append("constexpr NamespaceTags namespace_tags[] = {")
    for ns_name in NAMESPACE_MAPPING.keys():
        safe_ns = cpp_identifier(ns_name)
        tag_list = NAMESPACE_MAPPING[ns_name]
        count = sum(1 for t in tag_list if t in tags_data)
        append("    { " + safe_ns + "_tag_indices, " + str(count) + " },")
    append("};")
    append("")

    # ---- Keywords ----
    append("// ============================================================")
    append("// Keywords")
    append("// ============================================================")
    append("")

    append("struct KeywordSet {")
    append("    const char* name;")
    append("    const char* const* keywords;")
    append("    size_t count;")
    append("};")
    append("")

    for set_name, kw_list in keywords_data.items():
        safe_name = cpp_identifier(set_name)
        append("constexpr const char* " + safe_name + "_keywords[] = {")
        for kw in sorted(kw_list):
            append("    \"" + escape_cpp_string(kw) + "\",")
        append("};")
        append("")

    append("constexpr KeywordSet keyword_sets[] = {")
    for set_id in sorted(KEYWORDSET_MAPPING.keys()):
        set_name = KEYWORDSET_MAPPING[set_id]
        safe_name = cpp_identifier(set_name)
        kw_list = keywords_data.get(set_name, [])
        append("    {\"" + escape_cpp_string(set_name) + "\", " + safe_name + "_keywords, " + str(len(kw_list)) + "},")
    append("};")
    append("")

    # Namespace -> KeywordSet mapping
    append("struct NamespaceKeywordSets {")
    append("    const uint8_t* set_ids;")
    append("    size_t count;")
    append("};")
    append("")

    for ns_name, set_ids in NAMESPACE_KEYWORDSET_MAP.items():
        safe_ns = cpp_identifier(ns_name)
        append("constexpr uint8_t " + safe_ns + "_kwset_ids[] = { " + ', '.join(str(s) for s in set_ids) + " };")
    append("")

    append("constexpr NamespaceKeywordSets namespace_keyword_sets[] = {")
    for ns_name in NAMESPACE_MAPPING.keys():
        safe_ns = cpp_identifier(ns_name)
        set_ids = NAMESPACE_KEYWORDSET_MAP.get(ns_name, [])
        append("    { " + safe_ns + "_kwset_ids, " + str(len(set_ids)) + " },")
    append("};")
    append("")

    # ---- Lookup functions ----
    append("// ============================================================")
    append("// Lookup functions")
    append("// ============================================================")
    append("")

    append("inline const TagInfo* findTag(const char* name) {")
    append("    // Binary search on all_tags (sorted by name)")
    append("    size_t lo = 0, hi = sizeof(all_tags) / sizeof(TagInfo);")
    append("    while (lo < hi) {")
    append("        size_t mid = (lo + hi) / 2;")
    append("        int cmp = strcmp(name, all_tags[mid].name);")
    append("        if (cmp == 0) return &all_tags[mid];")
    append("        if (cmp < 0) hi = mid;")
    append("        else lo = mid + 1;")
    append("    }")
    append("    return nullptr;")
    append("}")
    append("")

    append("inline bool isKeywordInSet(const char* keyword, size_t set_index) {")
    append("    if (set_index >= sizeof(keyword_sets) / sizeof(KeywordSet)) return false;")
    append("    const auto& ks = keyword_sets[set_index];")
    append("    // Binary search")
    append("    size_t lo = 0, hi = ks.count;")
    append("    while (lo < hi) {")
    append("        size_t mid = (lo + hi) / 2;")
    append("        int cmp = strcmp(keyword, ks.keywords[mid]);")
    append("        if (cmp == 0) return true;")
    append("        if (cmp < 0) hi = mid;")
    append("        else lo = mid + 1;")
    append("    }")
    append("    return false;")
    append("}")
    append("")

    append("inline bool isKeywordInNamespace(const char* keyword, NamespaceId ns) {")
    append("    uint8_t ns_idx = static_cast<uint8_t>(ns);")
    append("    if (ns_idx == 0 || ns_idx > sizeof(namespace_keyword_sets) / sizeof(NamespaceKeywordSets)) return false;")
    append("    const auto& nks = namespace_keyword_sets[ns_idx - 1];")
    append("    for (size_t i = 0; i < nks.count; ++i) {")
    append("        uint8_t set_id = nks.set_ids[i];")
    append("        if (set_id > 0 && set_id <= sizeof(keyword_sets) / sizeof(KeywordSet)) {")
    append("            if (isKeywordInSet(keyword, set_id - 1)) return true;")
    append("        }")
    append("    }")
    append("    return false;")
    append("}")
    append("")

    append("inline const TagInfo* findTagInNamespace(const char* name, NamespaceId ns) {")
    append("    uint8_t ns_idx = static_cast<uint8_t>(ns);")
    append("    if (ns_idx == 0 || ns_idx > sizeof(namespace_tags) / sizeof(NamespaceTags)) return nullptr;")
    append("    const auto& nt = namespace_tags[ns_idx - 1];")
    append("    for (size_t i = 0; i < nt.count; ++i) {")
    append("        uint16_t tag_idx = nt.indices[i];")
    append("        if (tag_idx < sizeof(all_tags) / sizeof(TagInfo)) {")
    append("            const TagInfo* tag = &all_tags[tag_idx];")
    append("            if (strcmp(name, tag->name) == 0) return tag;")
    append("        }")
    append("    }")
    append("    return nullptr;")
    append("}")
    append("")

    append("inline const TagAttribute* findTagAttributes(const char* tag_name, NamespaceId ns, size_t& out_count) {")
    append("    const TagInfo* tag = findTagInNamespace(tag_name, ns);")
    append("    if (tag) {")
    append("        out_count = tag->attr_count;")
    append("        return tag->attributes;")
    append("    }")
    append("    out_count = 0;")
    append("    return nullptr;")
    append("}")
    append("")

    append("} // namespace AutoCompleteData")
    append("} // namespace nppColdFusionNS")
    append("")
    append("#endif // NPP_AUTOCMPLETE_DATA_H")

    return "\n".join(lines)

def main():
    print("Generating " + str(OUTPUT_PATH) + "...")
    content = generate_header()
    with open(OUTPUT_PATH, 'w', encoding='utf-8') as f:
        f.write(content)
    print("Done. Generated " + str(len(content)) + " chars.")

if __name__ == "__main__":
    main()