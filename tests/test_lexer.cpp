// test_lexer.cpp - Tests for lexer functionality (Doctest)
#include "test_common.h"
#include "../src/nppColdFusion.h"
#include "../src/nppCFShared.h"
#include "../src/Styles.h"
#include "ILexer.h"  // For Scintilla::ILexer5 (via AdditionalIncludeDirectories)

using namespace nppColdFusionNS;

// Test LexerName returns valid UTF-8 (T5)
TEST_CASE("LexerName returns valid UTF-8") {
    const char* name = LexerName();
    REQUIRE(name != nullptr);
    CHECK(strcmp(name, "coldfusion") == 0);
    
    // Verify it's valid UTF-8 (ASCII subset)
    for (const char* p = name; *p; ++p) {
        CHECK(static_cast<unsigned char>(*p) >= 0x20);
        CHECK(static_cast<unsigned char>(*p) <= 0x7E);
    }
}

// Test LexerName is cached (not re-converted each call) - P3
TEST_CASE("LexerName is cached") {
    const char* name1 = LexerName();
    const char* name2 = LexerName();
    
    // Should return the same pointer (static storage)
    CHECK(name1 == name2);
    CHECK(strcmp(name1, "coldfusion") == 0);
}

// Test lexer factory creation
TEST_CASE("LexerColdFusion factory creation") {
    // Test the static factory method
    Scintilla::ILexer5* lexer = LexerColdFusion::LexerFactory();
    CHECK(lexer != nullptr);
    delete lexer; // Clean up
}

// Test LexerColdFusion CreateLexer
TEST_CASE("LexerColdFusion CreateLexer") {
    Scintilla::ILexer5* lexer = LexerColdFusion::CreateLexer("ColdFusion");
    CHECK(lexer != nullptr);
    delete lexer;
}

// Test Status struct bounds (T7)
TEST_CASE("Status struct bounds constants") {
    using namespace Constants;
    
    // Verify constants exist and match expected values
    CHECK(MAX_STATE_HISTORY == 32);
    CHECK(MAX_OPEN_TAGS == 25);
    CHECK(MAX_TAG_LENGTH == 100);
    CHECK(OPEN_TAGS_BUFFER_SIZE == 512);
    CHECK(MAX_OPEN_TAGS_POSITIONS == 25);
}

// Test BlockTypeId enum values
TEST_CASE("BlockTypeId enum values") {
    using BlockId = BlockTypeId;
    
    CHECK(static_cast<int>(BlockId::CFQuery) == 0);
    CHECK(static_cast<int>(BlockId::CFScript) == 1);
    CHECK(static_cast<int>(BlockId::JS) == 2);
    CHECK(static_cast<int>(BlockId::CSS) == 3);
}

// Test Styles constants are accessible
TEST_CASE("Styles constants accessible") {
    using namespace Styles;
    
    // Just verify some constants compile and have expected values
    CHECK(_DEFAULT == 0);
    CHECK(_TAG == 1);
    CHECK(CF_TAG == 2);
    CHECK(CF_FUNCTION == 14);
    CHECK(CF_KEYWORD == 15);
    CHECK(SQL_KEYWORD == 22);
    CHECK(JS_KEYWORD == 23);
    CHECK(CSS_KEYWORD == 24);
}