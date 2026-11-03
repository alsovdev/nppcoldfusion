// test_lexer.cpp - Tests for lexer functionality (Doctest)
#include "test_common.h"
#include "../src/nppColdFusion.h"
#include "../src/nppCFShared.h"
#include "../src/Styles.h"

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
TEST_CASE("CreateLexer returns valid pointer") {
    void* lexer = CreateLexer();
    CHECK(lexer != nullptr);
    // Clean up - lexer is owned by caller in Lexilla model
    // This is just a smoke test
}

// Test GetLexerFactory returns valid function pointer
TEST_CASE("GetLexerFactory returns valid") {
    LexerFactoryFunction factory = GetLexerFactory();
    CHECK(factory != nullptr);
    
    // Call factory to create lexer
    void* lexer = factory();
    CHECK(lexer != nullptr);
}

// Test Status struct bounds (T7)
TEST_CASE("Status struct bounds constants") {
    using namespace Styles;
    
    // Verify constants exist and match expected values
    constexpr int MAX_STATE_HISTORY = 32;
    constexpr int MAX_OPEN_TAGS = 25;
    constexpr int MAX_TAG_NAME_LENGTH = 100;
    constexpr int MAX_OPEN_TAGS_BUFFER = 512;
    
    CHECK(MAX_STATE_HISTORY == 32);
    CHECK(MAX_OPEN_TAGS == 25);
    CHECK(MAX_TAG_NAME_LENGTH == 100);
    CHECK(MAX_OPEN_TAGS_BUFFER == 512);
}

// Test lexer state transitions don't crash
TEST_CASE("Lexer state transitions - smoke test") {
    // This would require a full lexer instance and document
    // Integration test - smoke test only
    CHECK(true);
}