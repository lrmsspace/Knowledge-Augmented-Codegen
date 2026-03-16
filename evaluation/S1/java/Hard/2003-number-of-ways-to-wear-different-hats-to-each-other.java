// Source: https://leetcode.com/problems/number-of-ways-to-wear-different-hats-to-each-other/   |   Difficulty: Hard
//
// Problem Description:
// There are n people and 40 types of hats labeled from 1 to 40.
//
// Given a 2D integer array hats, where hats[i] is a list of all hats preferred by the ith person.
//
// Return the number of ways that n people can wear different hats from each other.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: hats = [[3,4],[4,5],[5]]
// Output: 1
// Explanation: There is only one way to choose hats given the conditions. 
// First person choose hat 3, Second person choose hat 4 and last one hat 5.
//
// Constraints:
// n == hats.length
// 	1 <= n <= 10
// 	1 <= hats[i].length <= 40
// 	1 <= hats[i][j] <= 40
// 	hats[i] contains a list of unique integers.
//
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Binomial Coefficients (array, dp-2d)
//   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
//   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
//   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
//   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
//   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numberWays(List<List<Integer>> hats) {
        int MOD = 1_000_000_007;
        int n = hats.size();
        int maxMask = 1 << n;

        // dp[mask]: number of ways to assign hats to people represented by mask
        long[] dp = new long[maxMask];
        dp[0] = 1;

        // For each hat from 1 to 40
        for (int hat = 1; hat <= 40; hat++) {
            // For each person, check if they like this hat
            List<Integer> persons = new ArrayList<>();
            for (int person = 0; person < n; person++) {
                if (hats.get(person).contains(hat)) {
                    persons.add(person);
                }
            }

            // Update dp array in reverse order to avoid overwriting
            for (int mask = maxMask - 1; mask >= 0; mask--) {
                for (int person : persons) {
                    if ((mask & (1 << person)) == 0) { // If person is not assigned a hat yet
                        int newMask = mask | (1 << person);
                        dp[newMask] = (dp[newMask] + dp[mask]) % MOD;
                    }
                }
            }
        }

        return (int) dp[maxMask - 1];           
    }
}
