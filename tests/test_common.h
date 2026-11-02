// test_common.h - Common test utilities and mocks
#pragma once

#include <gtest/gtest.h>
#include <string>
#include <string_view>
#include <vector>

// Forward declarations for plugin types
namespace nppColdFusionNS {
    class DBNamespace;
    class nppCFShared;
    class LexerColdFusion;
    struct Status;
    enum class StyleId : int;
}

// Test fixture for autocomplete tests
class AutoCompleteTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize plugin shared instance
        // nppCFShared& cfs = nppCFShared::Instance();
    }
    
    void TearDown() override {
        // Cleanup
    }
};

// Test fixture for lexer tests
class LexerTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Test fixture for CFFunctions tests
class FunctionsTest : public ::testing::Test {
protected:
    void SetUp() override {
    }
    
    void TearDown() override {
    }
};

// Helper to check if string contains substring (case-insensitive)
bool ContainsIgnoreCase(std::string_view haystack, std::string_view needle);