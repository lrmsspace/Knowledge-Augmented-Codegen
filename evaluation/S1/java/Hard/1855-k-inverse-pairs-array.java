// Source: https://leetcode.com/problems/k-inverse-pairs-array/   |   Difficulty: Hard
//
// Problem Description:
// For an integer array nums, an inverse pair is a pair of integers [i, j] where 0 <= i < j < nums.length and nums[i] > nums[j].
//
// Given two integers n and k, return the number of different arrays consisting of numbers from 1 to n such that there are exactly k inverse pairs. Since the answer can be huge, return it modulo 109 + 7.
//
// Example:
// Input: n = 3, k = 0
// Output: 1
// Explanation: Only the array [1,2,3] which consists of numbers from 1 to 3 has exactly 0 inverse pairs.
//
// Constraints:
// 1 <= n <= 1000
// 	0 <= k <= 1000
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - Modular Multiplicative Inverse (array, number, dp-1d)
//   • When to use: Use when division operations are required in modular arithmetic, especially for combinatorics or probability problems under a modulus. It's crucial for precomputing inverses efficiently for a range of numbers.
//   • Idea: Calculates the modular multiplicative inverse of a number 'a' modulo 'm', which is an integer 'x' such that (a * x) % m == 1. When precomputing inverses for a range [1, N], a linear time O(N) dynamic programming approach can be used.
//   • Invariants: For all k in [1, i-1], inv[k] correctly stores k^(-1) % m.; inv[i] is computed using previously calculated inv[m % i].
//   • Tips: For prime modulus 'm', a^(m-2) % m (Fermat's Little Theorem) is efficient for a single inverse.; The Extended Euclidean Algorithm works for any 'm' if gcd(a, m) = 1.
//   • Pitfalls: A modular inverse only exists if gcd(a, m) == 1.; Fermat's Little Theorem is only applicable when the modulus 'm' is prime.
// - Counting labeled graphs (number, dp-2d, counting, recursion)
//   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
//   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
//   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
//   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
//   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int kInversePairs(int n, int k) {
        int MOD = 1_000_000_007;
        int[][] dp = new int[n + 1][k + 1];
        dp[0][0] = 1;

        for (int i = 1; i <= n; i++) {
            dp[i][0] = 1; // There's always one way to arrange i numbers with 0 inverse pairs
            for (int j = 1; j <= k; j++) {
                dp[i][j] = (dp[i][j - 1] + dp[i - 1][j]) % MOD;
                if (j >= i) {
                    dp[i][j] = (dp[i][j] - dp[i - 1][j - i] + MOD) % MOD;
                }
            }
        }

        return dp[n][k];            
    }
}
