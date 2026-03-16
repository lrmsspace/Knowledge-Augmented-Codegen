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
    int max_length = 0;
    int stack[30000]; // Stack to hold indices of '(' characters
    int top = -1; // Stack pointer

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            // Push the index of '(' onto the stack
            stack[++top] = i;
        } else {
            // If we encounter a ')', check if there's a matching '('
            if (top >= 0) {
                // Pop the last '(' index from the stack
                top--;
                // Calculate the length of the current valid substring
                int current_length;
                if (top >= 0) {
                    current_length = i - stack[top]; // Length from the last unmatched '('
                } else {
                    current_length = i + 1; // Length from the start of the string
                }
                // Update max_length if current_length is greater
                if (current_length > max_length) {
                    max_length = current_length;
                }
            }
        }
    }

    return max_length;      
}
