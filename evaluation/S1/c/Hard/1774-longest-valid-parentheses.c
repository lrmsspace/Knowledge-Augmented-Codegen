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
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int longestValidParentheses(char* s) {
    int maxLen = 0;
    int left = 0, right = 0;
    char *p = s;

    // Left to right scan
    while (*p) {
        if (*p == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            int len = 2 * right;
            if (len > maxLen) {
                maxLen = len;
            }
        } else if (right > left) {
            left = right = 0;
        }
        p++;
    }

    // Right to left scan
    left = right = 0;
    p--;
    while (p >= s) {
        if (*p == '(') {
            left++;
        } else {
            right++;
        }
        if (left == right) {
            int len = 2 * left;
            if (len > maxLen) {
                maxLen = len;
            }
        } else if (left > right) {
            left = right = 0;
        }
        p--;
    }

    return maxLen;      
}
