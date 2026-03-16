// Source: https://leetcode.com/problems/count-number-of-ways-to-place-houses/   |   Difficulty: Medium
//
// Problem Description:
// There is a street with n * 2 plots, where there are n plots on each side of the street. The plots on each side are numbered from 1 to n. On each plot, a house can be placed.
//
// Return the number of ways houses can be placed such that no two houses are adjacent to each other on the same side of the street. Since the answer may be very large, return it modulo 109 + 7.
//
// Note that if a house is placed on the ith plot on one side of the street, a house can also be placed on the ith plot on the other side of the street.
//
// Example:
// Input: n = 1
// Output: 4
// Explanation: 
// Possible arrangements:
// 1. All plots are empty.
// 2. A house is placed on one side of the street.
// 3. A house is placed on the other side of the street.
// 4. Two houses are placed, one on each side of the street.
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

int countHousePlacements(int n) {
    long long mod = 1000000007;
    long long dp[n + 1];
    dp[0] = 1; // Base case: 1 way to arrange houses on 0 plots
    dp[1] = 2; // Base case: 2 ways to arrange houses on 1 plot (house or no house)

    for (int i = 2; i <= n; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2]) % mod; // Fibonacci-like relation
    }

    long long result = (dp[n] * dp[n]) % mod; // Total arrangements for both sides of the street
    return (int)result;     
}
