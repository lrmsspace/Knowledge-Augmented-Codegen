// Source: https://leetcode.com/problems/soup-servings/   |   Difficulty: Medium
//
// Problem Description:
// You have two soups, A and B, each starting with n mL. On every turn, one of the following four serving operations is chosen at random, each with probability 0.25 independent of all previous turns:
//
//
// 	pour 100 mL from type A and 0 mL from type B
// 	pour 75 mL from type A and 25 mL from type B
// 	pour 50 mL from type A and 50 mL from type B
// 	pour 25 mL from type A and 75 mL from type B
//
//
// Note:
//
//
// 	There is no operation that pours 0 mL from A and 100 mL from B.
// 	The amounts from A and B are poured simultaneously during the turn.
// 	If an operation asks you to pour more than you have left of a soup, pour all that remains of that soup.
//
//
// The process stops immediately after any turn in which one of the soups is used up.
//
// Return the probability that A is used up before B, plus half the probability that both soups are used up in the same turn. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: n = 50
// Output: 0.62500
// Explanation: 
// If we perform either of the first two serving operations, soup A will become empty first.
// If we perform the third operation, A and B will become empty at the same time.
// If we perform the fourth operation, B will become empty first.
// So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
//
// Constraints:
// 0 <= n <= 109
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Simulated Annealing (array, number, randomized, simulation)
//   • When to use: Use when seeking a near-optimal solution for complex optimization problems with many local optima, especially when exact solutions are computationally infeasible or too slow.
//   • Idea: Simulated Annealing is a probabilistic metaheuristic for global optimization, inspired by the annealing process in metallurgy. It explores the search space by accepting worse solutions with a probability that decreases over time, aiming to escape local optima.
//   • Invariants: The `s_best` state always represents the lowest energy found across all iterations so far.; The temperature `T` is always non-negative and decreases monotonically with each iteration.
//   • Tips: Start with a sufficiently high initial temperature to allow broad exploration.; Choose a slow cooling schedule (decay rate) for better solution quality, at the cost of longer runtime.
//   • Pitfalls: Getting stuck in local minima if the cooling schedule is too fast.; Excessive runtime if the cooling schedule is too slow or initial temperature is too high.
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
    public double soupServings(int n) {
        if (n >= 5000) {
            return 1.0;
        }

        int size = (n + 24) / 25;
        double[][] dp = new double[size + 1][size + 1];

        for (int i = 0; i <= size; i++) {
            for (int j = 0; j <= size; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 0.5;
                } else if (i == 0) {
                    dp[i][j] = 1.0;
                } else if (j == 0) {
                    dp[i][j] = 0.0;
                } else {
                    dp[i][j] = 0.25 * (dp[Math.max(0, i - 4)][j] +
                                      dp[Math.max(0, i - 3)][Math.max(0, j - 1)] +
                                      dp[Math.max(0, i - 2)][Math.max(0, j - 2)] +
                                      dp[Math.max(0, i - 1)][Math.max(0, j - 3)]);
                }
            }
        }

        return dp[size][size];          
    }
}
