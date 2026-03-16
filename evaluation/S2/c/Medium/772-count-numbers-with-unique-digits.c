// Source: https://leetcode.com/problems/count-numbers-with-unique-digits/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer n, return the count of all numbers with unique digits, x, where 0 <= x < 10n.
//
// Example:
// Input: n = 2
// Output: 91
// Explanation: The answer should be the total numbers in the range of 0 ≤ x < 100, excluding 11,22,33,44,55,66,77,88,99
//
// Constraints:
// 0 <= n <= 8
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

int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1; // Only the number 0 is valid
    if (n > 10) n = 10; // There are only 10 unique digits (0-9)

    int count = 10; // Start with all single-digit numbers (0-9)
    int uniqueDigits = 9; // For the first digit, we have 9 options (1-9)
    int availableDigits = 9; // For the next digits, we have 9 options left (including 0)

    for (int i = 2; i <= n; i++) {
        count += uniqueDigits * availableDigits;
        uniqueDigits--;
        availableDigits--;
    }

    return count;       
}
