// Source: https://leetcode.com/problems/valid-permutations-for-di-sequence/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string s of length n where s[i] is either:
//
//
// 	'D' means decreasing, or
// 	'I' means increasing.
//
//
// A permutation perm of n + 1 integers of all the integers in the range [0, n] is called a valid permutation if for all valid i:
//
//
// 	If s[i] == 'D', then perm[i] > perm[i + 1], and
// 	If s[i] == 'I', then perm[i] < perm[i + 1].
//
//
// Return the number of valid permutations perm. Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: s = "DID"
// Output: 5
// Explanation: The 5 valid permutations of (0, 1, 2, 3) are:
// (1, 0, 3, 2)
// (2, 0, 3, 1)
// (2, 1, 3, 0)
// (3, 0, 2, 1)
// (3, 1, 2, 0)
//
// Constraints:
// n == s.length
// 	1 <= n <= 200
// 	s[i] is either 'I' or 'D'.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Knuth's Optimization (array, interval, dp-2d)
//   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
//   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
//   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
//   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numPermsDISequence(String s) {
        int n = s.length();
        int MOD = 1_000_000_007;
        int[][] dp = new int[n + 1][n + 1];

        // Base case: There's one way to arrange a single number
        for (int j = 0; j <= n; j++) {
            dp[0][j] = 1;
        }

        for (int i = 1; i <= n; i++) {
            if (s.charAt(i - 1) == 'I') {
                int cumSum = 0;
                for (int j = 0; j < i; j++) {
                    cumSum = (cumSum + dp[i - 1][j]) % MOD;
                    dp[i][j] = cumSum;
                }
            } else { // 'D'
                int cumSum = 0;
                for (int j = i - 1; j >= 0; j--) {
                    cumSum = (cumSum + dp[i - 1][j]) % MOD;
                    dp[i][j] = cumSum;
                }
            }
        }

        return dp[n][0];            
    }
}
