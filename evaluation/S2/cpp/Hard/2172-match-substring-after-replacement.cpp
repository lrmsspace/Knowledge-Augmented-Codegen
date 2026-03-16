// Source: https://leetcode.com/problems/match-substring-after-replacement/   |   Difficulty: Hard
//
// Problem Description:
// You are given two strings s and sub. You are also given a 2D character array mappings where mappings[i] = [oldi, newi] indicates that you may perform the following operation any number of times:
//
//
// 	Replace a character oldi of sub with newi.
//
//
// Each character in sub cannot be replaced more than once.
//
// Return true if it is possible to make sub a substring of s by replacing zero or more characters according to mappings. Otherwise, return false.
//
// A substring is a contiguous non-empty sequence of characters within a string.
//
// Example:
// Input: s = "fool3e7bar", sub = "leet", mappings = [["e","3"],["t","7"],["t","8"]]
// Output: true
// Explanation: Replace the first 'e' in sub with '3' and 't' in sub with '7'.
// Now sub = "l3e7" is a substring of s, so we return true.
//
// Constraints:
// 1 <= sub.length <= s.length <= 5000
// 	0 <= mappings.length <= 1000
// 	mappings[i].length == 2
// 	oldi != newi
// 	s and sub consist of uppercase and lowercase English letters and digits.
// 	oldi and newi are either uppercase or lowercase English letters or digits.
//
// Helpful references (internal KB):
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
// - Suffix Array (array, string, simulation, two-pointers)
//   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
//   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
//   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
//   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
//   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    bool matchReplacement(string s, string sub, vector<vector<char>>& mappings) {
        // Build a mapping from old characters to their possible replacements
        unordered_map<char, unordered_set<char>> charMap;
        for (const auto& mapping : mappings) {
            charMap[mapping[0]].insert(mapping[1]);
        }

        int sLen = s.size(), subLen = sub.size();

        // Check each substring of s that has the same length as sub
        for (int i = 0; i <= sLen - subLen; ++i) {
            bool match = true;
            for (int j = 0; j < subLen; ++j) {
                char sChar = s[i + j];
                char subChar = sub[j];

                // Check if the characters match directly or through a mapping
                if (sChar != subChar && 
                    (charMap.find(subChar) == charMap.end() || charMap[subChar].find(sChar) == charMap[subChar].end())) {
                    match = false;
                    break;
                }
            }
            if (match) return true; // Found a valid substring
        }

        return false; // No valid substring found           
    }
};
