// test_common.h - Common test utilities and mocks for Doctest
#pragma once

#include "doctest.h"
#include <string>
#include <string_view>
#include <vector>
#include <algorithm>

// Forward declarations for plugin types
namespace nppColdFusionNS {
    class DBNamespace;
    class nppCFShared;
    class LexerColdFusion;
    struct Status;
    enum class StyleId : int;
}

// Helper to check if string contains substring (case-insensitive)
inline bool ContainsIgnoreCase(std::string_view haystack, std::string_view needle) {
    if (needle.empty()) return true;
    if (haystack.size() < needle.size()) return false;
    
    for (size_t i = 0; i <= haystack.size() - needle.size(); ++i) {
        bool match = true;
        for (size_t j = 0; j < needle.size(); ++j) {
            char h = haystack[i + j];
            char n = needle[j];
            if (h >= 'A' && h <= 'Z') h = h - 'A' + 'a';
            if (n >= 'A' && n <= 'Z') n = n - 'A' + 'a';
            if (h != n) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    return false;
}

// Doctest doesn't need test fixtures with SetUp/TearDown for these simple tests
// We'll use plain TEST_CASE instead