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
// - Divide and Conquer DP (array, number, divide-and-conquer, dp-2d)
//   • When to use: Use when a problem can be broken into smaller, independent subproblems, and their solutions combine to solve the original. Also applicable when overlapping subproblems benefit from memoization or tabulation.
//   • Idea: This approach solves problems by recursively breaking them into smaller subproblems, solving each once, and storing results in a 2D table to avoid recomputation. It typically achieves a time complexity of O(N*M) or O(N^2) depending on state definition.
//   • Invariants: The DP table entry `dp[i][j]` correctly stores the optimal solution for the subproblem defined by `i` and `j`.; All subproblems `dp[x][y]` where `x < i` or `y < j` (or based on dependency order) are already computed and correct.
//   • Tips: Clearly define the state variables for your 2D DP table.; Establish the base cases before defining recursive relations.
//   • Pitfalls: Incorrectly defining state transitions or recurrence relations.; Missing or incorrect base cases leading to infinite recursion or wrong results.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} coins
 * @return {number}
 */
var maximumAmount = function(coins) {
    const m = coins.length;
    const n = coins[0].length;
    
    // dp[i][j][k] represents the maximum coins collected at cell (i, j) with k neutralizations used
    const dp = Array.from({ length: m }, () => 
        Array.from({ length: n }, () => 
            Array(3).fill(-Infinity)
        )
    );
    
    // Base case
    dp[0][0][0] = coins[0][0] >= 0 ? coins[0][0] : -coins[0][0];
    
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            for (let k = 0; k <= 2; k++) {
                if (i === 0 && j === 0) continue; // Skip the starting cell
                
                const currentCoins = coins[i][j];
                
                // Move from the top cell
                if (i > 0) {
                    // If current cell has a robber and we can neutralize
                    if (currentCoins < 0 && k > 0) {
                        dp[i][j][k] = Math.max(dp[i][j][k], dp[i - 1][j][k - 1] + (-currentCoins));
                    }
                    // If current cell has a robber and we don't neutralize
                    if (currentCoins < 0) {
                        dp[i][j][k] = Math.max(dp[i][j][k], dp[i - 1][j][k] + currentCoins);
                    }
                    // If current cell has coins
                    if (currentCoins >= 0) {
                        dp[i][j][k] = Math.max(dp[i][j][k], dp[i - 1][j][k] + currentCoins);
                    }
                }
                
                // Move from the left cell
                if (j > 0) {
                    // If current cell has a robber and we can neutralize
                    if (currentCoins < 0 && k > 0) {
                        dp[i][j][k] = Math.max(dp[i][j][k], dp[i][j - 1][k - 1] + (-currentCoins));
                    }
                    // If current cell has a robber and we don't neutralize
                    if (currentCoins < 0) {
                        dp[i][j][k] = Math.max(dp[i][j][k], dp[i][j - 1][k] + currentCoins);
                    }
                    // If current cell has coins
                    if (currentCoins >= 0) {
                        dp[i][j][k] = Math.max(dp[i][j][k], dp[i][j - 1][k] + currentCoins);
                    }
                }
            }
        }
    }
    
    // Find the maximum coins collected at the bottom-right cell with any number of neutralizations used
    return Math.max(dp[m - 1][n - 1][0], dp[m - 1][n - 1][1], dp[m - 1][n - 1][2]);
};
