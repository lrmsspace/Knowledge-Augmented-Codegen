// Source: https://leetcode.com/problems/three-divisors/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer n, return true if n has exactly three positive divisors. Otherwise, return false.
//
// An integer m is a divisor of n if there exists an integer k such that n = k * m.
//
// Example:
// Input: n = 2
// Output: false
// Explantion: 2 has only two divisors: 1 and 2.
//
// Constraints:
// 1 <= n <= 104
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

bool isThree(int n) {
    if (n < 2) {
        return false; // 1 has only one divisor
    }

    int divisorCount = 0;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            divisorCount++; // Count the divisor
            if (i != n / i) {
                divisorCount++; // Count the complementary divisor if it's different
            }
        }
        if (divisorCount > 3) {
            return false; // More than three divisors, no need to continue
        }
    }

    return divisorCount == 3; // Return true if exactly three divisors      
}
