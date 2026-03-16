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

int numTilings(int n) {
    const int MOD = 1e9 + 7;
    if (n == 1) return 1;
    if (n == 2) return 2;
    
    // dp[i] = number of ways to tile a 2 x i board
    int dp[n + 1];
    dp[0] = 1; // Base case: one way to tile a 2 x 0 board (do nothing)
    dp[1] = 1; // One way to tile a 2 x 1 board
    dp[2] = 2; // Two ways to tile a 2 x 2 board

    for (int i = 3; i <= n; i++) {
        dp[i] = (2 * dp[i - 1]) % MOD; // Place a vertical domino or two horizontal dominoes
        for (int j = 0; j <= i - 3; j++) {
            dp[i] = (dp[i] + dp[j]) % MOD; // Place a tromino covering the last three columns
        }
    }

    return dp[n];       
}
