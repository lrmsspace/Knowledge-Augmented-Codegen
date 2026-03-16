// Source: https://leetcode.com/problems/largest-palindromic-number/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string num consisting of digits only.
//
// Return the largest palindromic integer (in the form of a string) that can be formed using digits taken from num. It should not contain leading zeroes.
//
// Example:
// Input: num = "444947137"
// Output: "7449447"
// Explanation: 
// Use the digits "4449477" from "444947137" to form the palindromic integer "7449447".
// It can be shown that "7449447" is the largest palindromic integer that can be formed.
//
// Constraints:
// 1 <= num.length <= 105
// 	num consists of digits.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* largestPalindromic(char* num) {
    int count[10] = {0};
    for (char* p = num; *p; ++p) {
        count[*p - '0']++;
    }

    char left[50000] = {0};
    int left_len = 0;
    char middle = '\0';

    for (int digit = 9; digit >= 0; --digit) {
        while (count[digit] >= 2) {
            if (left_len > 0 || digit != 0) { // Avoid leading zero
                left[left_len++] = '0' + digit;
                count[digit] -= 2;
            } else {
                break;
            }
        }
    }

    for (int digit = 9; digit >= 0; --digit) {
        if (count[digit] > 0) {
            middle = '0' + digit;
            break;
        }
    }

    int total_len = left_len * 2 + (middle ? 1 : 0);
    char* result = (char*)malloc(total_len + 1);
    if (!result) return NULL;

    int pos = 0;
    for (int i = 0; i < left_len; ++i) {
        result[pos++] = left[i];
    }
    if (middle) {
        result[pos++] = middle;
    }
    for (int i = left_len - 1; i >= 0; --i) {
        result[pos++] = left[i];
    }
    result[pos] = '\0';

    return result;      
}
