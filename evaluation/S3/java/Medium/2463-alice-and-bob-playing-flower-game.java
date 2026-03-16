// Source: https://leetcode.com/problems/alice-and-bob-playing-flower-game/   |   Difficulty: Medium
//
// Problem Description:
// Alice and Bob are playing a turn-based game on a field, with two lanes of flowers between them. There are x flowers in the first lane between Alice and Bob, and y flowers in the second lane between them.
//
//
//
// The game proceeds as follows:
//
//
// 	Alice takes the first turn.
// 	In each turn, a player must choose either one of the lane and pick one flower from that side.
// 	At the end of the turn, if there are no flowers left at all in either lane, the current player captures their opponent and wins the game.
//
//
// Given two integers, n and m, the task is to compute the number of possible pairs (x, y) that satisfy the conditions:
//
//
// 	Alice must win the game according to the described rules.
// 	The number of flowers x in the first lane must be in the range [1,n].
// 	The number of flowers y in the second lane must be in the range [1,m].
//
//
// Return the number of possible pairs (x, y) that satisfy the conditions mentioned in the statement.
//
// Example:
// Input: n = 3, m = 2
// Output: 3
// Explanation: The following pairs satisfy conditions described in the statement: (1,2), (3,2), (2,1).
//
// Constraints:
// 1 <= n, m <= 105
//
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, counting, dp-2d)
//   • When to use: Use when counting non-attacking piece placements on a grid, especially when the problem can be decomposed into independent subproblems based on board properties like diagonals.
//   • Idea: This algorithm employs 2D dynamic programming to count the total number of ways to place non-attacking bishops on a chessboard. It leverages the independence of placements on black and white squares/diagonals, achieving a polynomial time complexity.
//   • Invariants: For any diagonal `i`, `D[i][j]` represents the number of ways to place `j` bishops on diagonal `i`.; Bishops placed on black diagonals do not attack bishops placed on white diagonals.
//   • Tips: Decompose the problem into independent subproblems for black and white squares/diagonals.; Identify the state for DP, typically `dp[diagonal_index][bishops_placed]`.
//   • Pitfalls: Incorrectly calculating the number of squares on each diagonal.; Overlapping bishops if diagonal definitions are not precise.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - 15 Puzzle Game: Existence Of The Solution (matrix, number, counting)
//   • When to use: Use this to quickly determine if a given 15-puzzle board configuration can be solved, avoiding exhaustive search. It's applicable when the goal is to check solvability rather than finding the solution path.
//   • Idea: This algorithm determines the solvability of a 15-puzzle configuration by analyzing the parity of inversions in the tile permutation and the blank tile's row. It involves counting inversions, which typically takes O(N^2) time for N tiles, or O(N log N) with a more advanced counting method.
//   • Invariants: The permutation used for inversion counting always excludes the blank tile.; Each pair of tiles (i, j) with i < j is considered exactly once for inversion counting.
//   • Tips: Remember to exclude the blank tile (0) when forming the permutation for inversion counting.; For a 4x4 grid, the blank tile's row (from bottom, 1-indexed) is crucial for the parity check.
//   • Pitfalls: Incorrectly including the blank tile (0) in the inversion count.; Miscalculating the blank tile's row index (e.g., 0-indexed from top vs. 1-indexed from bottom).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long flowerGame(int n, int m) {
        // Alice wins if the total number of flowers is odd, because she goes first.
        // Therefore, we need to count the pairs (x, y) such that x + y is odd.
        // This happens when one of them is even and the other is odd.

        // Count of odd numbers in [1, n]
        long oddCountN = (n + 1) / 2;
        // Count of even numbers in [1, n]
        long evenCountN = n / 2;

        // Count of odd numbers in [1, m]
        long oddCountM = (m + 1) / 2;
        // Count of even numbers in [1, m]
        long evenCountM = m / 2;

        // Pairs where x is odd and y is even
        long pairsOddEven = oddCountN * evenCountM;
        // Pairs where x is even and y is odd
        long pairsEvenOdd = evenCountN * oddCountM;

        // Total pairs where x + y is odd
        return pairsOddEven + pairsEvenOdd;         
    }
}
