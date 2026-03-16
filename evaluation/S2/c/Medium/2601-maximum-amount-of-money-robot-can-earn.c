// Source: https://leetcode.com/problems/maximum-amount-of-money-robot-can-earn/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid. A robot starts at the top-left corner of the grid (0, 0) and wants to reach the bottom-right corner (m - 1, n - 1). The robot can move either right or down at any point in time.
//
// The grid contains a value coins[i][j] in each cell:
//
//
// 	If coins[i][j] >= 0, the robot gains that many coins.
// 	If coins[i][j] < 0, the robot encounters a robber, and the robber steals the absolute value of coins[i][j] coins.
//
//
// The robot has a special ability to neutralize robbers in at most 2 cells on its path, preventing them from stealing coins in those cells.
//
// Note: The robot's total coins can be negative.
//
// Return the maximum profit the robot can gain on the route.
//
// Example:
// Input: coins = [[0,1,-1],[1,-2,3],[2,-3,4]]
//
// Output: 8
//
// Explanation:
//
// An optimal path for maximum coins is:
//
//
// 	Start at (0, 0) with 0 coins (total coins = 0).
// 	Move to (0, 1), gaining 1 coin (total coins = 0 + 1 = 1).
// 	Move to (1, 1), where there's a robber stealing 2 coins. The robot uses one neutralization here, avoiding the robbery (total coins = 1).
// 	Move to (1, 2), gaining 3 coins (total coins = 1 + 3 = 4).
// 	Move to (2, 2), gaining 4 coins (total coins = 4 + 4 = 8).
//
// Constraints:
// m == coins.length
// 	n == coins[i].length
// 	1 <= m, n <= 500
// 	-1000 <= coins[i][j] <= 1000
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

int maximumAmount(int** coins, int coinsSize, int* coinsColSize) {
    int m = coinsSize;
    int n = coinsColSize[0];
    
    // dp[i][j][k] represents the maximum coins collected at cell (i, j) with k neutralizations used
    int dp[m][n][3];
    
    // Initialize the dp array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 3; k++) {
                dp[i][j][k] = -1000000000; // A very small number to represent negative infinity
            }
        }
    }
    
    // Base case
    dp[0][0][0] = coins[0][0];
    
    // Fill the dp array
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < 3; k++) {
                if (i == 0 && j == 0) continue; // Skip the starting cell
                
                int currentCoins = coins[i][j];
                
                // If we come from the left cell
                if (j > 0) {
                    dp[i][j][k] = fmax(dp[i][j][k], dp[i][j-1][k] + currentCoins);
                    if (k > 0 && currentCoins < 0) {
                        dp[i][j][k] = fmax(dp[i][j][k], dp[i][j-1][k-1]); // Use neutralization
                    }
                }
                
                // If we come from the top cell
                if (i > 0) {
                    dp[i][j][k] = fmax(dp[i][j][k], dp[i-1][j][k] + currentCoins);
                    if (k > 0 && currentCoins < 0) {
                        dp[i][j][k] = fmax(dp[i][j][k], dp[i-1][j][k-1]); // Use neutralization
                    }
                }
            }
        }
    }
    
    // The answer is the maximum coins collected at the bottom-right corner with any number of neutralizations used
    int maxCoins = -1000000000;     
    for (int k = 0; k < 3; k++) {
        maxCoins = fmax(maxCoins, dp[m-1][n-1][k]);
    }
    return maxCoins;
}
