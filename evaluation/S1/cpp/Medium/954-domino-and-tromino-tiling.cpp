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
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numTilings(int n) {
        const int MOD = 1e9 + 7;
        if (n == 1) return 1;
        if (n == 2) return 2;
        if (n == 3) return 5;

        // dp[i] = number of ways to tile 2 x i board
        std::vector<int> dp(n + 1, 0);
        dp[1] = 1;
        dp[2] = 2;
        dp[3] = 5;

        for (int i = 4; i <= n; ++i) {
            dp[i] = (2 * dp[i - 1] % MOD + dp[i - 3]) % MOD;
        }

        return dp[n];           
    }
};
