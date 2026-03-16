// Source: https://leetcode.com/problems/maximum-energy-boost-from-two-drinks/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays energyDrinkA and energyDrinkB of the same length n by a futuristic sports scientist. These arrays represent the energy boosts per hour provided by two different energy drinks, A and B, respectively.
//
// You want to maximize your total energy boost by drinking one energy drink per hour. However, if you want to switch from consuming one energy drink to the other, you need to wait for one hour to cleanse your system (meaning you won't get any energy boost in that hour).
//
// Return the maximum total energy boost you can gain in the next n hours.
//
// Note that you can start consuming either of the two energy drinks.
//
// Example:
// Input: energyDrinkA = [1,3,1], energyDrinkB = [3,1,1]
//
// Output: 5
//
// Explanation:
//
// To gain an energy boost of 5, drink only the energy drink A (or only B).
//
// Constraints:
// n == energyDrinkA.length == energyDrinkB.length
// 	3 <= n <= 105
// 	1 <= energyDrinkA[i], energyDrinkB[i] <= 105
//
// Helpful references (internal KB):
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long maxEnergyBoost(int[] energyDrinkA, int[] energyDrinkB) {
        int n = energyDrinkA.length;
        long[][] dp = new long[n][3];
        // dp[i][0] - max energy boost at hour i when drink A is consumed
        // dp[i][1] - max energy boost at hour i when drink B is consumed
        // dp[i][2] - max energy boost at hour i when no drink is consumed (cleansing hour)

        dp[0][0] = energyDrinkA[0];
        dp[0][1] = energyDrinkB[0];
        dp[0][2] = 0;

        for (int i = 1; i < n; i++) {
            dp[i][0] = Math.max(dp[i - 1][0], dp[i - 1][2]) + energyDrinkA[i];
            dp[i][1] = Math.max(dp[i - 1][1], dp[i - 1][2]) + energyDrinkB[i];
            dp[i][2] = Math.max(dp[i - 1][0], dp[i - 1][1]);
        }

        return Math.max(dp[n - 1][0], Math.max(dp[n - 1][1], dp[n - 1][2]));            
    }
}
