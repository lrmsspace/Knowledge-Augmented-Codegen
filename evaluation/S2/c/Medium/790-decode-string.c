// Source: https://leetcode.com/problems/decode-string/   |   Difficulty: Medium
//
// Problem Description:
// Given an encoded string, return its decoded string.
//
// The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
//
// You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
//
// The test cases are generated so that the length of the output will never exceed 105.
//
// Example:
// Input: s = "3[a]2[bc]"
// Output: "aaabcbc"
//
// Constraints:
// 1 <= s.length <= 30
// 	s consists of lowercase English letters, digits, and square brackets '[]'.
// 	s is guaranteed to be a valid input.
// 	All the integers in s are in the range [1, 300].
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

char* decodeString(char* s) {
    int len = strlen(s);
    char* stack[len];
    int top = -1;

    for (int i = 0; i < len; i++) {
        if (s[i] != ']') {
            stack[++top] = &s[i];
        } else {
            char* substr_start = NULL;
            while (top >= 0 && *stack[top] != '[') {
                substr_start = stack[top--];
            }
            top--; // Pop the '['

            char* num_start = NULL;
            while (top >= 0 && isdigit(*stack[top])) {
                num_start = stack[top--];
            }

            int repeat_count = atoi(num_start);
            int substr_len = &s[i] - substr_start;

            char* decoded_substr = malloc(repeat_count * substr_len + 1);
            decoded_substr[0] = '\0';

            for (int j = 0; j < repeat_count; j++) {
                strncat(decoded_substr, substr_start, substr_len);
            }

            stack[++top] = decoded_substr;
        }
    }

    char* result = malloc(len + 1);
    result[0] = '\0';
    for (int i = 0; i <= top; i++) {
        strcat(result, stack[i]);
    }

    return result;      
}
