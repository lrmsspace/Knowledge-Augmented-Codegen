// Source: https://leetcode.com/problems/rearranging-fruits/   |   Difficulty: Hard
//
// Problem Description:
// You have two fruit baskets containing n fruits each. You are given two 0-indexed integer arrays basket1 and basket2 representing the cost of fruit in each basket. You want to make both baskets equal. To do so, you can use the following operation as many times as you want:
//
//
// 	Choose two indices i and j, and swap the ith fruit of basket1 with the jth fruit of basket2.
// 	The cost of the swap is min(basket1[i], basket2[j]).
//
//
// Two baskets are considered equal if sorting them according to the fruit cost makes them exactly the same baskets.
//
// Return the minimum cost to make both the baskets equal or -1 if impossible.
//
// Example:
// Input: basket1 = [4,2,2,2], basket2 = [1,4,1,2]
// Output: 1
// Explanation: Swap index 1 of basket1 with index 0 of basket2, which has cost 1. Now basket1 = [4,1,2,2] and basket2 = [2,4,1,2]. Rearranging both the arrays makes them equal.
//
// Constraints:
// basket1.length == basket2.length
// 	1 <= basket1.length <= 105
// 	1 <= basket1[i], basket2[i] <= 109
//
// Helpful references (internal KB):
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
// - Stars and bars (number, counting)
//   • When to use: Use when counting the number of ways to distribute identical items into distinct bins, or finding the number of non-negative integer solutions to a linear equation. It is also applicable for problems with lower bounds on variables.
//   • Idea: Stars and bars is a combinatorial technique used to count the number of ways to place 'n' identical items into 'k' distinct bins, or equivalently, to find the number of non-negative integer solutions to x1 + ... + xk = n.
//   • Invariants: The total number of 'stars' (items) remains constant throughout any transformation.; The number of 'bars' (separators) is always one less than the number of bins (variables).
//   • Tips: Visualize items as 'stars' and separators as 'bars' to understand the arrangement.; Transform problems with lower bounds (x_i >= a_i) into non-negative solutions (x_i' >= 0).
//   • Pitfalls: Confusing identical items with distinct items, which requires a different counting method.; Incorrectly applying the formula when variables have lower bounds other than zero without transformation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} basket1
 * @param {number[]} basket2
 * @return {number}
 */
var minCost = function(basket1, basket2) {
    const n = basket1.length;
    const countMap = new Map();
    let totalCost = 0;

    for (let i = 0; i < n; i++) {
        countMap.set(basket1[i], (countMap.get(basket1[i]) || 0) + 1);
        countMap.set(basket2[i], (countMap.get(basket2[i]) || 0) - 1);
        totalCost += Math.min(basket1[i], basket2[i]);
    }

    const excess = [];
    for (const [fruit, count] of countMap.entries()) {
        if (count % 2 !== 0) {
            return -1; // Impossible to balance
        }
        if (count > 0) {
            excess.push(...Array(count / 2).fill(fruit));
        }
    }

    excess.sort((a, b) => a - b);
    const minFruitCost = Math.min(...basket1, ...basket2);

    let swapCost = 0;
    for (let i = 0; i < excess.length / 2; i++) {
        swapCost += Math.min(excess[i], minFruitCost * 2);
    }

    return swapCost;
};
