// Source: https://leetcode.com/problems/binary-string-with-substrings-representing-1-to-n/   |   Difficulty: Medium
//
// Problem Description:
// Given a binary string s and a positive integer n, return true if the binary representation of all the integers in the range [1, n] are substrings of s, or false otherwise.
//
// A substring is a contiguous sequence of characters within a string.
//
// Example:
// Input: s = "0110", n = 3
// Output: true
//
// Constraints:
// 1 <= s.length <= 1000
// 	s[i] is either '0' or '1'.
// 	1 <= n <= 109
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
    bool queryString(string s, int n) {
        for (int i = 1; i <= n; ++i) {
            string binary = to_binary(i);
            if (s.find(binary) == string::npos) {
                return false;
            }
        }
        return true;            
    }
};
