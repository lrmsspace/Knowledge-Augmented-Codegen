// Source: https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s of '(' , ')' and lowercase English characters.
//
// Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.
//
// Formally, a parentheses string is valid if and only if:
//
//
// 	It is the empty string, contains only lowercase characters, or
// 	It can be written as AB (A concatenated with B), where A and B are valid strings, or
// 	It can be written as (A), where A is a valid string.
//
// Example:
// Input: s = "lee(t(c)o)de)"
// Output: "lee(t(c)o)de"
// Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is either '(' , ')', or lowercase English letter.
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

char* minRemoveToMakeValid(char* s) {
    int len = 0;
    while (s[len]) len++;

    // First pass: Remove invalid ')'
    char* temp = (char*)malloc((len + 1) * sizeof(char));
    int open = 0;
    int idx = 0;
    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            open++;
            temp[idx++] = s[i];
        } else if (s[i] == ')') {
            if (open > 0) {
                open--;
                temp[idx++] = s[i];
            }
        } else {
            temp[idx++] = s[i];
        }
    }
    temp[idx] = '\0';

    // Second pass: Remove invalid '(' from the end
    char* result = (char*)malloc((idx + 1) * sizeof(char));
    int close = 0;
    int res_idx = 0;
    for (int i = idx - 1; i >= 0; i--) {
        if (temp[i] == ')') {
            close++;
            result[res_idx++] = temp[i];
        } else if (temp[i] == '(') {
            if (close > 0) {
                close--;
                result[res_idx++] = temp[i];
            }
        } else {
            result[res_idx++] = temp[i];
        }
    }
    result[res_idx] = '\0';

    // Reverse the result to get the final valid string
    for (int i = 0; i < res_idx / 2; i++) {
        char tmp_char = result[i];
        result[i] = result[res_idx - 1 - i];
        result[res_idx - 1 - i] = tmp_char;
    }

    free(temp);
    return result;      
}
