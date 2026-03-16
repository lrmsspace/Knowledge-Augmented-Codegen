// Source: https://leetcode.com/problems/domino-and-tromino-tiling/   |   Difficulty: Medium
//
// Problem Description:
// You have two types of tiles: a 2 x 1 domino shape and a tromino shape. You may rotate these shapes.
//
// Given an integer n, return the number of ways to tile an 2 x n board. Since the answer may be very large, return it modulo 109 + 7.
//
// In a tiling, every square must be covered by a tile. Two tilings are different if and only if there are two 4-directionally adjacent cells on the board such that exactly one of the tilings has both squares occupied by a tile.
//
// Example:
// Input: n = 3
// Output: 5
// Explanation: The five different ways are shown above.
//
// Constraints:
// 1 <= n <= 1000
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

int numTilings(int n) {
    if (n == 1) return 1;
    if (n == 2) return 2;

    int mod = 1000000007;
    long long dp[n + 1];
    dp[1] = 1;
    dp[2] = 2;

    for (int i = 3; i <= n; i++) {
        dp[i] = (dp[i - 1] + dp[i - 2] + 2 * dp[i - 3]) % mod;
    }

    return dp[n];       
}
