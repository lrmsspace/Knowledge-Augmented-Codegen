// Source: https://leetcode.com/problems/dice-roll-simulation/   |   Difficulty: Hard
//
// Problem Description:
// A die simulator generates a random number from 1 to 6 for each roll. You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times.
//
// Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls. Since the answer may be too large, return it modulo 109 + 7.
//
// Two sequences are considered different if at least one element differs from each other.
//
// Example:
// Input: n = 2, rollMax = [1,1,2,2,2,3]
// Output: 34
// Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.
//
// Constraints:
// 1 <= n <= 5000
// 	rollMax.length == 6
// 	1 <= rollMax[i] <= 15
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
// - Longest Increasing Subsequence (array, coordinate-compress, segment-tree, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements must be strictly increasing. It is applicable for problems requiring optimal substructure on sequences with an increasing property.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence such that all elements of the subsequence are in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search or a segment tree with coordinate compression.
//   • Invariants: The `dp` array (or segment tree) stores information about the smallest ending element for increasing subsequences of various lengths.; The `dp` array, if used, remains sorted in strictly increasing order.
//   • Tips: The O(N log N) solution uses a `dp` array storing the smallest ending element for all increasing subsequences of a given length.; Binary search (`lower_bound`) efficiently finds the correct position to update in the `dp` array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates; LIS typically requires strictly increasing elements.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int dieSimulator(int n, int[] rollMax) {
        final int MOD = 1_000_000_007;
        int faces = 6;

        // dp[i][j][k]: number of sequences of length i, ending with face j, with k consecutive j's
        int[][][] dp = new int[n + 1][faces][16];

        // Base case: for sequences of length 1
        for (int j = 0; j < faces; j++) {
            dp[1][j][1] = 1;
        }

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < faces; j++) {
                for (int k = 1; k <= rollMax[j]; k++) {
                    if (k == 1) {
                        // If we are placing a different face, sum all sequences of length i-1
                        for (int m = 0; m < faces; m++) {
                            if (m != j) {
                                for (int l = 1; l <= rollMax[m]; l++) {
                                    dp[i][j][k] = (dp[i][j][k] + dp[i - 1][m][l]) % MOD;
                                }
                            }
                        }
                    } else {
                        // If we are placing the same face, extend the sequence
                        dp[i][j][k] = dp[i - 1][j][k - 1];
                    }
                }
            }
        }

        // Sum all valid sequences of length n
        int result = 0;
        for (int j = 0; j < faces; j++) {
            for (int k = 1; k <= rollMax[j]; k++) {
                result = (result + dp[n][j][k]) % MOD;
            }
        }

        return result;          
    }
}
