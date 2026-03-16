// Source: https://leetcode.com/problems/longest-valid-parentheses/   |   Difficulty: Hard
//
// Problem Description:
// Given a string containing just the characters '(' and ')', return the length of the longest valid (well-formed) parentheses substring.
//
// Example:
// Input: s = "(()"
// Output: 2
// Explanation: The longest valid parentheses substring is "()".
//
// Constraints:
// 0 <= s.length <= 3 * 104
// 	s[i] is '(', or ')'.
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
    int longestValidParentheses(string s) {
        int max_len = 0;
        int left = 0, right = 0;

        // Left to right scan
        for (char c : s) {
            if (c == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                max_len = max(max_len, 2 * right);
            } else if (right > left) {
                left = right = 0;
            }
        }

        left = right = 0;
        // Right to left scan
        for (int i = s.length() - 1; i >= 0; --i) {
            char c = s[i];
            if (c == '(') {
                left++;
            } else {
                right++;
            }
            if (left == right) {
                max_len = max(max_len, 2 * left);
            } else if (left > right) {
                left = right = 0;
            }
        }

        return max_len;         
    }
};
