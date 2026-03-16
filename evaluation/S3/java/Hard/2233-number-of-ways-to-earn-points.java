// Source: https://leetcode.com/problems/number-of-ways-to-earn-points/   |   Difficulty: Hard
//
// Problem Description:
// There is a test that has n types of questions. You are given an integer target and a 0-indexed 2D integer array types where types[i] = [counti, marksi] indicates that there are counti questions of the ith type, and each one of them is worth marksi points.
//
//
//
//
// Return the number of ways you can earn exactly target points in the exam. Since the answer may be too large, return it modulo 109 + 7.
//
// Note that questions of the same type are indistinguishable.
//
//
// 	For example, if there are 3 questions of the same type, then solving the 1st and 2nd questions is the same as solving the 1st and 3rd questions, or the 2nd and 3rd questions.
//
// Example:
// Input: target = 6, types = [[6,1],[3,2],[2,3]]
// Output: 7
// Explanation: You can earn 6 points in one of the seven ways:
// - Solve 6 questions of the 0th type: 1 + 1 + 1 + 1 + 1 + 1 = 6
// - Solve 4 questions of the 0th type and 1 question of the 1st type: 1 + 1 + 1 + 1 + 2 = 6
// - Solve 2 questions of the 0th type and 2 questions of the 1st type: 1 + 1 + 2 + 2 = 6
// - Solve 3 questions of the 0th type and 1 question of the 2nd type: 1 + 1 + 1 + 3 = 6
// - Solve 1 question of the 0th type, 1 question of the 1st type and 1 question of the 2nd type: 1 + 2 + 3 = 6
// - Solve 3 questions of the 1st type: 2 + 2 + 2 = 6
// - Solve 2 questions of the 2nd type: 3 + 3 = 6
//
// Constraints:
// 1 <= target <= 1000
// 	n == types.length
// 	1 <= n <= 50
// 	types[i].length == 2
// 	1 <= counti, marksi <= 50
//
// Helpful references (internal KB):
// - Binomial Coefficients (array, enumeration)
//   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
//   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
//   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
//   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
//   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
// - Binomial Coefficients (array, dp-2d)
//   • When to use: Use when you need to compute many binomial coefficients, especially for values up to a certain N, or when working with modulo arithmetic where division is not straightforward.
//   • Idea: This method computes binomial coefficients using Pascal's identity, building a 2D DP table where C(n, k) = C(n-1, k-1) + C(n-1, k). It has a time complexity of O(N^2) for computing all coefficients up to N.
//   • Invariants: For each cell dp[i][j], it stores the value of C(i, j).; At the start of computing row i, all values for row i-1 are correctly calculated and available.
//   • Tips: Optimize space by storing only the current and previous row of the DP table.; For O(1) lookup after precomputation, calculate all factorials and inverse factorials modulo a prime.
//   • Pitfalls: Direct division for C(n,k) = n! / (k!(n-k)!) is problematic with modulo arithmetic unless the modulo is prime.; Integer overflow can occur for large N and K if not handled with appropriate data types or modulo operations.
// - Modular Multiplicative Inverse (array, number, dp-1d)
//   • When to use: Use when division operations are required in modular arithmetic, especially for combinatorics or probability problems under a modulus. It's crucial for precomputing inverses efficiently for a range of numbers.
//   • Idea: Calculates the modular multiplicative inverse of a number 'a' modulo 'm', which is an integer 'x' such that (a * x) % m == 1. When precomputing inverses for a range [1, N], a linear time O(N) dynamic programming approach can be used.
//   • Invariants: For all k in [1, i-1], inv[k] correctly stores k^(-1) % m.; inv[i] is computed using previously calculated inv[m % i].
//   • Tips: For prime modulus 'm', a^(m-2) % m (Fermat's Little Theorem) is efficient for a single inverse.; The Extended Euclidean Algorithm works for any 'm' if gcd(a, m) = 1.
//   • Pitfalls: A modular inverse only exists if gcd(a, m) == 1.; Fermat's Little Theorem is only applicable when the modulus 'm' is prime.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int waysToReachTarget(int target, int[][] types) {
        int mod = 1_000_000_007;
        int n = types.length;

        // Step 1: Precompute binomial coefficients using Pascal's triangle
        int maxCount = 0;
        for (int[] type : types) {
            maxCount = Math.max(maxCount, type[0]);
        }
        int[][] C = new int[maxCount + 1][maxCount + 1];
        for (int i = 0; i <= maxCount; i++) {
            C[i][0] = 1;
            for (int j = 1; j <= i; j++) {
                C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % mod;
            }
        }

        // Step 2: Initialize DP array
        int[] dp = new int[target + 1];
        dp[0] = 1; // Base case: one way to achieve target of 0 (do nothing)

        // Step 3: Fill DP array using the types of questions
        for (int[] type : types) {
            int count = type[0];
            int marks = type[1];

            // Create a temporary array to store new DP values
            int[] newDp = new int[target + 1];
            System.arraycopy(dp, 0, newDp, 0, dp.length);

            for (int t = target; t >= marks; t--) {
                for (int k = 1; k <= count && k * marks <= t; k++) {
                    newDp[t] = (newDp[t] + (long) dp[t - k * marks] * C[count][k]) % mod;
                }
            }
            dp = newDp; // Update dp with the new values
        }

        return dp[target];          
    }
}
