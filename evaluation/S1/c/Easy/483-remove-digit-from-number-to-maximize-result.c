// Source: https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string number representing a positive integer and a character digit.
//
// Return the resulting string after removing exactly one occurrence of digit from number such that the value of the resulting string in decimal form is maximized. The test cases are generated such that digit occurs at least once in number.
//
// Example:
// Input: number = "123", digit = "3"
// Output: "12"
// Explanation: There is only one '3' in "123". After removing '3', the result is "12".
//
// Constraints:
// 2 <= number.length <= 100
// 	number consists of digits from '1' to '9'.
// 	digit is a digit from '1' to '9'.
// 	digit occurs at least once in number.
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

char* removeDigit(char* number, char digit) {
    int len = 0;
    while (number[len] != '\0') {
        len++;
    }

    char* result = NULL;

    for (int i = 0; i < len; i++) {
        if (number[i] == digit) {
            // Create a new string without the digit at index i
            char* candidate = (char*)malloc(len); // len - 1 + 1 for null terminator
            int k = 0;
            for (int j = 0; j < len; j++) {
                if (j != i) {
                    candidate[k++] = number[j];
                }
            }
            candidate[k] = '\0';

            // Compare with the current best result
            if (result == NULL || strcmp(candidate, result) > 0) {
                if (result != NULL) {
                    free(result);
                }
                result = candidate;
            } else {
                free(candidate);
            }
        }
    }

    return result;      
}
