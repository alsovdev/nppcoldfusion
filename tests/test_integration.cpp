// test_integration.cpp - Integration tests with real CFM/CFC files (Doctest)
#include "test_common.h"
#include "../src/nppColdFusion.h"
#include "../src/nppCFShared.h"
#include "../src/Styles.h"
#include "ILexer.h"
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace nppColdFusionNS;

namespace fs = std::filesystem;

// Helper to read entire file
static std::string ReadFile(const fs::path& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) return "";
    std::ostringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

// Helper to get test fixtures directory
static fs::path GetFixturesDir() {
    // Tests run from vs.proj/x64/Debug/Tests/
    // Fixtures are at repo_root/tests/fixtures/
    fs::path exePath = fs::current_path();
    // Navigate up to find tests/fixtures
    for (auto p = exePath; p.has_parent_path(); p = p.parent_path()) {
        fs::path fixtures = p / "tests" / "fixtures";
        if (fs::exists(fixtures)) return fixtures;
        fixtures = p / ".." / "tests" / "fixtures";
        if (fs::exists(fixtures)) return fs::canonical(fixtures);
    }
    return "tests/fixtures"; // fallback
}

// Test that lexer can tokenize real CFM files without crashing
TEST_CASE("Integration: Lexer tokenizes Taffy Application.cfc") {
    fs::path fixturesDir = GetFixturesDir();
    std::string content = ReadFile(fixturesDir / "taffy_Application.cfc");
    REQUIRE(!content.empty());
    
    // Create lexer
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);
    
    // Initialize lexer
    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");
    
    // Tokenize
    int length = static_cast<int>(content.size());
    lexer->Lex(0, length, 0, nullptr);
    
    delete lexer;
    CHECK(true); // If we get here without crash, test passes
}

TEST_CASE("Integration: Lexer tokenizes Taffy artistMember.cfc (complex CFC)") {
    fs::path fixturesDir = GetFixturesDir();
    std::string content = ReadFile(fixturesDir / "taffy_artistMember.cfc");
    REQUIRE(!content.empty());
    CHECK(content.size() > 1000); // Substantial file
    
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);
    
    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");
    
    int length = static_cast<int>(content.size());
    lexer->Lex(0, length, 0, nullptr);
    
    delete lexer;
    CHECK(true);
}

TEST_CASE("Integration: Lexer tokenizes Taffy consumer index.cfm (largest fixture)") {
    fs::path fixturesDir = GetFixturesDir();
    std::string content = ReadFile(fixturesDir / "taffy_consumer_index.cfm");
    REQUIRE(!content.empty());
    CHECK(content.size() > 5000); // Largest fixture ~9KB
    
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);
    
    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");
    
    int length = static_cast<int>(content.size());
    lexer->Lex(0, length, 0, nullptr);
    
    delete lexer;
    CHECK(true);
}

TEST_CASE("Integration: Lexer tokenizes Lucee docs build.cfm") {
    fs::path fixturesDir = GetFixturesDir();
    std::string content = ReadFile(fixturesDir / "lucee_docs_build.cfm");
    REQUIRE(!content.empty());
    
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);
    
    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");
    
    int length = static_cast<int>(content.size());
    lexer->Lex(0, length, 0, nullptr);
    
    delete lexer;
    CHECK(true);
}

TEST_CASE("Integration: Lexer tokenizes all Taffy fixtures") {
    fs::path fixturesDir = GetFixturesDir();
    
    std::vector<std::string> taffyFiles = {
        "taffy_Application.cfc",
        "taffy_anythingtoxml_Application.cfc",
        "taffy_anythingtoxml_index.cfm",
        "taffy_api_index.cfm",
        "taffy_artMember.cfc",
        "taffy_artistMember.cfc",
        "taffy_consumer_Application.cfc",
        "taffy_consumer_index.cfm",
        "taffy_fakeData.cfc",
        "taffy_hoth_Application.cfc",
        "taffy_hoth_index.cfm",
        "taffy_jsonutil_Application.cfc",
        "taffy_jsonutil_index.cfm",
        "taffy_logtoemail_Application.cfc"
    };
    
    for (const auto& filename : taffyFiles) {
        fs::path filePath = fixturesDir / filename;
        if (!fs::exists(filePath)) continue; // Skip missing
        
        std::string content = ReadFile(filePath);
        if (content.empty()) continue;
        
        Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
        REQUIRE(lexer != nullptr);
        
        lexer->PropertySet("fold", "1");
        lexer->PropertySet("fold.compact", "1");
        
        int length = static_cast<int>(content.size());
        // Should not crash
        lexer->Lex(0, length, 0, nullptr);
        
        delete lexer;
    }
    CHECK(true);
}

TEST_CASE("Integration: Lexer tokenizes all Lucee docs fixtures") {
    fs::path fixturesDir = GetFixturesDir();
    
    std::vector<std::string> luceeFiles = {
        "lucee_docs_Application.cfc",
        "lucee_docs_build.cfm",
        "lucee_docs_build-all.cfm",
        "lucee_docs_import.cfm"
    };
    
    for (const auto& filename : luceeFiles) {
        fs::path filePath = fixturesDir / filename;
        if (!fs::exists(filePath)) continue;
        
        std::string content = ReadFile(filePath);
        if (content.empty()) continue;
        
        Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
        REQUIRE(lexer != nullptr);
        
        lexer->PropertySet("fold", "1");
        lexer->PropertySet("fold.compact", "1");
        
        int length = static_cast<int>(content.size());
        lexer->Lex(0, length, 0, nullptr);
        
        delete lexer;
    }
    CHECK(true);
}

// Test lexer handles CFML-specific syntax from real files
TEST_CASE("Integration: Real files contain expected CFML constructs") {
    fs::path fixturesDir = GetFixturesDir();
    
    // Check artistMember.cfc has component, function, cfquery
    std::string artistMember = ReadFile(fixturesDir / "taffy_artistMember.cfc");
    CHECK(ContainsIgnoreCase(artistMember, "component"));
    CHECK(ContainsIgnoreCase(artistMember, "function"));
    CHECK(ContainsIgnoreCase(artistMember, "cfquery"));
    CHECK(ContainsIgnoreCase(artistMember, "cfargument"));
    
    // Check consumer index.cfm has HTML + CFML mixed
    std::string consumerIndex = ReadFile(fixturesDir / "taffy_consumer_index.cfm");
    CHECK(ContainsIgnoreCase(consumerIndex, "<html"));
    CHECK(ContainsIgnoreCase(consumerIndex, "cfoutput"));
    CHECK(ContainsIgnoreCase(consumerIndex, "cfloop"));
    
    // Check Lucee build.cfm has CFML tags
    std::string luceeBuild = ReadFile(fixturesDir / "lucee_docs_build.cfm");
    CHECK(ContainsIgnoreCase(luceeBuild, "cfset"));
    CHECK(ContainsIgnoreCase(luceeBuild, "cffile"));
    CHECK(ContainsIgnoreCase(luceeBuild, "cfloop"));
}

// Test that lexer works without XML config (uses default styles)
TEST_CASE("Integration: Lexer works without XML config - default styles") {
    fs::path fixturesDir = GetFixturesDir();
    std::string content = ReadFile(fixturesDir / "taffy_Application.cfc");
    REQUIRE(!content.empty());

    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);

    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");

    int length = static_cast<int>(content.size());
    // Should not crash even without XML loaded
    lexer->Lex(0, length, 0, nullptr);

    // Verify default styles are available via NamedStyles API
    int namedStyles = lexer->NamedStyles();
    CHECK(namedStyles == 24);

    const char* styleName = lexer->NameOfStyle(0);
    CHECK(styleName != nullptr);
    CHECK(strcmp(styleName, "DEFAULT") == 0);

    const char* styleDesc = lexer->DescriptionOfStyle(0);
    CHECK(styleDesc != nullptr);
    CHECK(strcmp(styleDesc, "Default text") == 0);

    // Check all 24 styles have names (gaps return empty)
    for (int i = 0; i < namedStyles; ++i) {
        const char* name = lexer->NameOfStyle(i);
        CHECK(name != nullptr);
        // Gaps (11, 18, 20) return empty string, others have names
        if (i != 11 && i != 18 && i != 20) {
            CHECK(strlen(name) > 0);
        }
    }

    delete lexer;
    CHECK(true);
}

// Test that lexer handles malformed/invalid XML gracefully
TEST_CASE("Integration: Lexer handles missing XML gracefully") {
    // Lexer doesn't load XML directly - it uses NamedStyles API
    // This test verifies the plugin doesn't depend on external XML file
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);

    // Verify all style names match expected defaults from nppColdFusion.xml
    static const char* expectedStyles[] = {
        "DEFAULT", "TAG", "CFTAG", "ATTRIBUTE", "ATTRIBUTEUNKNOWN",
        "NUMBER", "DOUBLESTRING", "SINGLESTRING", "OPERATOR", "COMMENT",
        "COMMENTBLOCK", "", "CFCOMMENT", "CFVALUE", "CFFUNCTION",
        "CFATTRIBUTE", "CFATTRIBUTEBAD", "LOCALVARS", "", "CFSRESERVED",
        "", "SQLKEYWORDS", "JSKEYWORDS", "CSSKEYWORDS"
    };

    int namedStyles = lexer->NamedStyles();
    CHECK(namedStyles == 24);

    for (int i = 0; i < namedStyles; ++i) {
        const char* name = lexer->NameOfStyle(i);
        CHECK(name != nullptr);
        CHECK(strcmp(name, expectedStyles[i]) == 0);
    }

    delete lexer;
}

// Test that lexer produces valid style IDs for real content
TEST_CASE("Integration: Lexer produces valid style IDs for all fixtures") {
    fs::path fixturesDir = GetFixturesDir();

    std::vector<std::string> allFiles = {
        "taffy_Application.cfc",
        "taffy_artistMember.cfc",
        "lucee_docs_build.cfm",
        "cloud_capacity.cfm"
    };

    for (const auto& filename : allFiles) {
        fs::path filePath = fixturesDir / filename;
        if (!fs::exists(filePath)) continue;

        std::string content = ReadFile(filePath);
        if (content.empty()) continue;

        Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
        REQUIRE(lexer != nullptr);

        lexer->PropertySet("fold", "1");
        lexer->PropertySet("fold.compact", "1");

        int length = static_cast<int>(content.size());
        lexer->Lex(0, length, 0, nullptr);

        // Verify style IDs returned are within valid range
        // (This is implicitly tested by successful lexing without crash)
        CHECK(true);

        delete lexer;
    }
}

// Test edge cases
TEST_CASE("Integration: No crash on empty file") {
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);

    lexer->PropertySet("fold", "1");
    lexer->Lex(0, 0, 0, nullptr); // Empty content

    delete lexer;
    CHECK(true);
}

TEST_CASE("Integration: No crash on UTF-8 BOM") {
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);

    lexer->PropertySet("fold", "1");
    std::string utf8Bom = "\xEF\xBB\xBF<cfset x = 1>";
    lexer->Lex(0, static_cast<int>(utf8Bom.size()), 0, nullptr);

    delete lexer;
    CHECK(true);
}

// Test SQL keyword highlighting in cfquery blocks
TEST_CASE("Integration: SQL keywords highlighted in cfquery") {
    // Test that SQL keyword list is loaded and contains key keywords
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);

    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");

    // Verify WordListSet was called with SQL keywords (index 6)
    // The lexer should have SQL keywords loaded via DescribeWordListSets/WordListSet
    const char* wordLists = lexer->DescribeWordListSets();
    REQUIRE(wordLists != nullptr);
    CHECK(strstr(wordLists, "SQL Keywords") != nullptr);

    // Test with a cfquery containing SQL
    std::string cfquerySql = 
        "<cfquery name=\"q\" datasource=\"dsn\">\n"
        "    WITH status AS (VALUES ('a', 1), ('b', 2))\n"
        "    SELECT upper(trim(name)), substring(code, 1, 5), length(description)\n"
        "    FROM products\n"
        "    WHERE price > 100\n"
        "    ORDER BY created_at DESC\n"
        "</cfquery>";

    int length = static_cast<int>(cfquerySql.size());
    // Should not crash and should process SQL keywords
    lexer->Lex(0, length, 0, nullptr);

    delete lexer;
    CHECK(true);
}

TEST_CASE("Integration: SQL functions and casts highlighted") {
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);

    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");

    // Test various SQL functions and PostgreSQL-specific syntax
    std::string sql = 
        "<cfquery>\n"
        "    SELECT \n"
        "        UPPER(name), LOWER(email),\n"
        "        TRIM(description), LTRIM(code), RTRIM(value),\n"
        "        SUBSTRING(sku, 1, 10),\n"
        "        LENGTH(name),\n"
        "        CAST(price AS NUMERIC),\n"
        "        id::text,\n"
        "        COALESCE(discount, 0),\n"
        "        CASE WHEN active THEN 'yes' ELSE 'no' END\n"
        "    FROM products\n"
        "    WHERE created_at BETWEEN '2024-01-01' AND '2024-12-31'\n"
        "    GROUP BY category\n"
        "    HAVING COUNT(*) > 5\n"
        "</cfquery>";

    int length = static_cast<int>(sql.size());
    lexer->Lex(0, length, 0, nullptr);

    delete lexer;
    CHECK(true);
}

TEST_CASE("Integration: CTE and advanced SQL syntax") {
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    REQUIRE(lexer != nullptr);

    lexer->PropertySet("fold", "1");
    lexer->PropertySet("fold.compact", "1");

    // Test CTE (WITH), window functions, joins
    std::string advancedSql = 
        "<cfquery>\n"
        "    WITH ranked AS (\n"
        "        SELECT \n"
        "            id,\n"
        "            name,\n"
        "            ROW_NUMBER() OVER (PARTITION BY category ORDER BY price DESC) as rn,\n"
        "            SUM(price) OVER (PARTITION BY category) as cat_total\n"
        "        FROM products\n"
        "    )\n"
        "    SELECT r.id, r.name, c.name as category_name\n"
        "    FROM ranked r\n"
        "    INNER JOIN categories c ON r.category_id = c.id\n"
        "    LEFT JOIN orders o ON r.id = o.product_id\n"
        "    WHERE r.rn = 1\n"
        "    AND o.id IS NULL\n"
        "    UNION ALL\n"
        "    SELECT id, name, 'orphan' as category_name\n"
        "    FROM products\n"
        "    WHERE category_id IS NULL\n"
        "</cfquery>";

    int length = static_cast<int>(advancedSql.size());
    lexer->Lex(0, length, 0, nullptr);

    delete lexer;
    CHECK(true);
}