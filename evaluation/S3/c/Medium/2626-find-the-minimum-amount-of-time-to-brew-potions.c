// Source: https://leetcode.com/problems/find-the-minimum-amount-of-time-to-brew-potions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, skill and mana, of length n and m, respectively.
//
// In a laboratory, n wizards must brew m potions in order. Each potion has a mana capacity mana[j] and must pass through all the wizards sequentially to be brewed properly. The time taken by the ith wizard on the jth potion is timeij = skill[i] * mana[j].
//
// Since the brewing process is delicate, a potion must be passed to the next wizard immediately after the current wizard completes their work. This means the timing must be synchronized so that each wizard begins working on a potion exactly when it arrives. ​
//
// Return the minimum amount of time required for the potions to be brewed properly.
//
// Example:
// Input: skill = [1,5,2,4], mana = [5,1,4,2]
//
// Output: 110
//
// Explanation:
//
//
// 	
// 		
// 			Potion Number
// 			Start time
// 			Wizard 0 done by
// 			Wizard 1 done by
// 			Wizard 2 done by
// 			Wizard 3 done by
// 		
// 		
// 			0
// 			0
// 			5
// 			30
// 			40
// 			60
// 		
// 		
// 			1
// 			52
// 			53
// 			58
// 			60
// 			64
// 		
// 		
// 			2
// 			54
// 			58
// 			78
// 			86
// 			102
// 		
// 		
// 			3
// 			86
// 			88
// 			98
// 			102
// 			110
// 		
// 	
//
//
// As an example for why wizard 0 cannot start working on the 1st potion before time t = 52, consider the case where the wizards started preparing the 1st potion at time t = 50. At time t = 58, wizard 2 is done with the 1st potion, but wizard 3 will still be working on the 0th potion till time t = 60.
//
// Constraints:
// n == skill.length
// 	m == mana.length
// 	1 <= n, m <= 5000
// 	1 <= mana[i], skill[i] <= 5000
//
// Helpful references (internal KB):
// - interval-dp (array, interval-dp)
//   • When to use: When a problem involves finding an optimal value for a contiguous range of elements, and solutions for larger ranges can be derived by merging optimal solutions of smaller sub-ranges.
//   • Idea: An extension of dynamic programming where subproblems are defined over contiguous intervals, solving for dp[i][j] by iterating through all possible split points k within [i, j]. This often results in O(N^3) time complexity.
//   • Invariants: dp[i][j] represents the optimal solution for the interval [i, j].; When computing dp[i][j], all subproblems dp[x][y] where y - x + 1 < j - i + 1 are already solved.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length, then by start index.
//   • Pitfalls: Off-by-one errors in interval boundaries or split points.; Incorrect iteration order, leading to uncomputed subproblems.
// - interval-dp (array, interval-dp, prefix-sum)
//   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
//   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
//   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
//   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
//   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minTime(int* skill, int skillSize, int* mana, int manaSize) {
    long long dp[manaSize][manaSize];
    for (int i = 0; i < manaSize; i++) {
        dp[i][i] = 0;
        for (int j = 0; j < skillSize; j++) {
            dp[i][i] += (long long)skill[j] * mana[i];
        }
    }

    for (int len = 2; len <= manaSize; len++) {
        for (int l = 0; l + len - 1 < manaSize; l++) {
            int r = l + len - 1;
            dp[l][r] = LLONG_MAX;
            for (int k = l; k < r; k++) {
                long long time = dp[l][k] + dp[k + 1][r];
                if (time < dp[l][r]) {
                    dp[l][r] = time;
                }
            }
        }
    }

    return dp[0][manaSize - 1];     
}
