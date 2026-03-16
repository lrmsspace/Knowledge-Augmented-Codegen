// Source: https://leetcode.com/problems/minimum-cost-for-tickets/   |   Difficulty: Medium
//
// Problem Description:
// You have planned some train traveling one year in advance. The days of the year in which you will travel are given as an integer array days. Each day is an integer from 1 to 365.
//
// Train tickets are sold in three different ways:
//
//
// 	a 1-day pass is sold for costs[0] dollars,
// 	a 7-day pass is sold for costs[1] dollars, and
// 	a 30-day pass is sold for costs[2] dollars.
//
//
// The passes allow that many days of consecutive travel.
//
//
// 	For example, if we get a 7-day pass on day 2, then we can travel for 7 days: 2, 3, 4, 5, 6, 7, and 8.
//
//
// Return the minimum number of dollars you need to travel every day in the given list of days.
//
// Example:
// Input: days = [1,4,6,7,8,20], costs = [2,7,15]
// Output: 11
// Explanation: For example, here is one way to buy passes that lets you travel your travel plan:
// On day 1, you bought a 1-day pass for costs[0] = $2, which covered day 1.
// On day 3, you bought a 7-day pass for costs[1] = $7, which covered days 3, 4, ..., 9.
// On day 20, you bought a 1-day pass for costs[0] = $2, which covered day 20.
// In total, you spent $11 and covered all the days of your travel.
//
// Constraints:
// 1 <= days.length <= 365
// 	1 <= days[i] <= 365
// 	days is in strictly increasing order.
// 	costs.length == 3
// 	1 <= costs[i] <= 1000
//
// Helpful references (internal KB):
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Shortest Paths (array, graph, dp-1d)
//   • When to use: To find the path with the minimum total weight or cost between two vertices, or from a single source to all other reachable vertices, in an edge-weighted graph.
//   • Idea: Shortest path algorithms determine the path with the least cumulative weight between nodes in a graph. This often involves a dynamic programming approach, iteratively updating minimum distances to achieve an optimal O(V*E) or O(E log V) complexity.
//   • Invariants: distTo[v] always stores the minimum path length from the source to v discovered so far.; For any edge u -> v, if distTo[u] is final, then distTo[v] will eventually be min(distTo[v], distTo[u] + weight(u,v)).
//   • Tips: Initialize the source distance to 0 and all other distances to infinity.; Use a `distTo` array to store the current shortest distances from the source.
//   • Pitfalls: Failing to detect or handle negative cycles, which can lead to infinite loops or incorrect results.; Incorrectly initializing distances or edge relaxation logic.
// - Sparse Table (array, sparse-table, enumeration)
//   • When to use: Use when you need to perform many range queries on a static array, especially when the query operation is associative and idempotent, allowing for O(1) query time after O(N log N) precomputation.
//   • Idea: A Sparse Table is a data structure that precomputes answers for all possible range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like min/max/gcd and O(log N) for non-idempotent associative operations, after an O(N log N) build time.
//   • Invariants: After precomputation, dp[k][i] stores the result for the range [i, i + 2^k - 1].; For any k > 0, dp[k][i] is the result of combining dp[k-1][i] and dp[k-1][i + 2^(k-1)].
//   • Tips: Precompute log2 values for faster range length calculations.; Store dp[k][i] as the result for range [i, i + 2^k - 1].
//   • Pitfalls: Does not support updates to array elements efficiently.; Requires O(N log N) space, which can be significant for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int mincostTickets(int* days, int daysSize, int* costs, int costsSize) {
    int dp[366] = {0};
    int daySet[366] = {0};
    for (int i = 0; i < daysSize; i++) {
        daySet[days[i]] = 1;
    }

    for (int i = 1; i <= 365; i++) {
        if (!daySet[i]) {
            dp[i] = dp[i - 1];
            continue;
        }
        int cost1 = dp[i - 1] + costs[0];
        int cost7 = dp[i - 7 >= 0 ? i - 7 : 0] + costs[1];
        int cost30 = dp[i - 30 >= 0 ? i - 30 : 0] + costs[2];
        dp[i] = cost1 < cost7 ? (cost1 < cost30 ? cost1 : cost30) : (cost7 < cost30 ? cost7 : cost30);
    }

    return dp[365];     
}
