// Source: https://leetcode.com/problems/sum-of-square-numbers/   |   Difficulty: Medium
//
// Problem Description:
// Given a non-negative integer c, decide whether there're two integers a and b such that a2 + b2 = c.
//
// Example:
// Input: c = 5
// Output: true
// Explanation: 1 * 1 + 2 * 2 = 5
//
// Constraints:
// 0 <= c <= 231 - 1
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

bool judgeSquareSum(int c) {
    for (long long a = 0; a * a <= c; a++) {
        long long b = c - a * a;
        long long sqrt_b = (long long)sqrt(b);
        if (sqrt_b * sqrt_b == b) {
            return true;
        }
    }
    return false;       
}
