// Source: https://leetcode.com/problems/consecutive-characters/   |   Difficulty: Easy
//
// Problem Description:
// The power of the string is the maximum length of a non-empty substring that contains only one unique character.
//
// Given a string s, return the power of s.
//
// Example:
// Input: s = "leetcode"
// Output: 2
// Explanation: The substring "ee" is of length 2 with the character 'e' only.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of only lowercase English letters.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int maxPower(string s) {
        int max_length = 1;
        int current_length = 1;

        for (size_t i = 1; i < s.length(); ++i) {
            if (s[i] == s[i - 1]) {
                ++current_length;
            } else {
                max_length = std::max(max_length, current_length);
                current_length = 1;
            }
        }

        // Check the last sequence
        max_length = std::max(max_length, current_length);

        return max_length;          
    }
};
