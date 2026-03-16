// Source: https://leetcode.com/problems/valid-parentheses/   |   Difficulty: Easy
//
// Problem Description:
// Given a string s containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
//
// An input string is valid if:
//
//
// 	Open brackets must be closed by the same type of brackets.
// 	Open brackets must be closed in the correct order.
// 	Every close bracket has a corresponding open bracket of the same type.
//
// Example:
// Input: s = "()"
//
// Output: true
//
// Constraints:
// 1 <= s.length <= 104
// 	s consists of parentheses only '()[]{}'.
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

bool isValid(char* s) {
    char stack[10000];
    int top = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(' || c == '{' || c == '[') {
            stack[++top] = c;
        } else {
            if (top == -1) return false;
            char last = stack[top--];
            if ((c == ')' && last != '(') ||
                (c == '}' && last != '{') ||
                (c == ']' && last != '[')) {
                return false;
            }
        }
    }
    return top == -1;       
}
