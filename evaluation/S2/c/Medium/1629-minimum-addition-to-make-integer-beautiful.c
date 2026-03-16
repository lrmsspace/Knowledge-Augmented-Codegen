// Source: https://leetcode.com/problems/minimum-addition-to-make-integer-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers n and target.
//
// An integer is considered beautiful if the sum of its digits is less than or equal to target.
//
// Return the minimum non-negative integer x such that n + x is beautiful. The input will be generated such that it is always possible to make n beautiful.
//
// Example:
// Input: n = 16, target = 6
// Output: 4
// Explanation: Initially n is 16 and its digit sum is 1 + 6 = 7. After adding 4, n becomes 20 and digit sum becomes 2 + 0 = 2. It can be shown that we can not make n beautiful with adding non-negative integer less than 4.
//
// Constraints:
// 1 <= n <= 1012
// 	1 <= target <= 150
// 	The input will be generated such that it is always possible to make n beautiful.
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

long long makeIntegerBeautiful(long long n, int target) {
    long long x = 0;
    long long multiplier = 1;
    while (1) {
        long long sum_digits = 0;
        long long temp = n + x;
        while (temp > 0) {
            sum_digits += temp % 10;
            temp /= 10;
        }
        if (sum_digits <= target) {
            return x;
        }
        x += multiplier * ((10 - (n + x) % 10) % 10);
        multiplier *= 10;
    }       
}
