// Source: https://leetcode.com/problems/divide-two-integers/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers dividend and divisor, divide two integers without using multiplication, division, and mod operator.
//
// The integer division should truncate toward zero, which means losing its fractional part. For example, 8.345 would be truncated to 8, and -2.7335 would be truncated to -2.
//
// Return the quotient after dividing dividend by divisor.
//
// Note: Assume we are dealing with an environment that could only store integers within the 32-bit signed integer range: [−231, 231 − 1]. For this problem, if the quotient is strictly greater than 231 - 1, then return 231 - 1, and if the quotient is strictly less than -231, then return -231.
//
// Example:
// Input: dividend = 10, divisor = 3
// Output: 3
// Explanation: 10/3 = 3.33333.. which is truncated to 3.
//
// Constraints:
// -231 <= dividend, divisor <= 231 - 1
// 	divisor != 0
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

int divide(int dividend, int divisor) {
    // Handle overflow case
    if (dividend == -2147483648 && divisor == -1) {
        return 2147483647; // Return INT_MAX
    }

    // Determine the sign of the result
    int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;

    // Convert both dividend and divisor to positive values
    long long absDividend = dividend < 0 ? -(long long)dividend : dividend;
    long long absDivisor = divisor < 0 ? -(long long)divisor : divisor;

    long long quotient = 0;
    while (absDividend >= absDivisor) {
        absDividend -= absDivisor;
        quotient++;
    }

    return sign * quotient;     
}
