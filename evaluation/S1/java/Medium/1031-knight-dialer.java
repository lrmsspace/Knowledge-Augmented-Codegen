// Source: https://leetcode.com/problems/knight-dialer/   |   Difficulty: Medium
//
// Problem Description:
// The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagram:
//
// A chess knight can move as indicated in the chess diagram below:
//
// We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).
//
// Given an integer n, return how many distinct phone numbers of length n we can dial.
//
// You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.
//
// As the answer may be very large, return the answer modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 10
// Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
//
// Constraints:
// 1 <= n <= 5000
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int knightDialer(int n) {
        int MOD = 1_000_000_007;
        // Possible moves for a knight from each digit
        int[][] moves = {
            {4, 6},    // from 0
            {6, 8},    // from 1
            {7, 9},    // from 2
            {4, 8},    // from 3
            {0, 3, 9}, // from 4
            {},        // from 5 (no moves)
            {0, 1, 7}, // from 6
            {2, 6},    // from 7
            {1, 3},    // from 8
            {2, 4}     // from 9
        };

        // dp[i][j] will be the number of distinct numbers of length i ending with digit j
        long[][] dp = new long[n + 1][10];

        // Base case: for length 1, there's one way to end with each digit
        for (int j = 0; j <= 9; j++) {
            dp[1][j] = 1;
        }

        // Fill the dp table
        for (int i = 2; i <= n; i++) {
            for (int j = 0; j <= 9; j++) {
                for (int move : moves[j]) {
                    dp[i][j] = (dp[i][j] + dp[i - 1][move]) % MOD;
                }
            }
        }

        // Sum all ways to form numbers of length n
        long result = 0;
        for (int j = 0; j <= 9; j++) {
            result = (result + dp[n][j]) % MOD;
        }

        return (int) result;            
    }
}
