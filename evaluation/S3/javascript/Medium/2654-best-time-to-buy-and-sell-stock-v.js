// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-v/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array prices where prices[i] is the price of a stock in dollars on the ith day, and an integer k.
//
// You are allowed to make at most k transactions, where each transaction can be either of the following:
//
//
// 	
// 	Normal transaction: Buy on day i, then sell on a later day j where i < j. You profit prices[j] - prices[i].
// 	
// 	
// 	Short selling transaction: Sell on day i, then buy back on a later day j where i < j. You profit prices[i] - prices[j].
// 	
//
//
// Note that you must complete each transaction before starting another. Additionally, you can't buy or sell on the same day you are selling or buying back as part of a previous transaction.
//
// Return the maximum total profit you can earn by making at most k transactions.
//
// Example:
// Input: prices = [1,7,9,8,2], k = 2
//
// Output: 14
//
// Explanation:
// We can make $14 of profit through 2 transactions:
//
//
// 	A normal transaction: buy the stock on day 0 for $1 then sell it on day 2 for $9.
// 	A short selling transaction: sell the stock on day 3 for $8 then buy back on day 4 for $2.
//
// Constraints:
// 2 <= prices.length <= 103
// 	1 <= prices[i] <= 109
// 	1 <= k <= prices.length / 2
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Knapsack Problem (array, deque, knapsack, dp-1d, monotonic-queue)
//   • When to use: When optimizing the knapsack problem where multiple identical items are available, reducing the DP transition from O(max_count) to O(1) using a sliding window maximum technique.
//   • Idea: The Knapsack problem involves selecting items with weights and values to maximize total value within a capacity constraint. This specific variant, often for multiple identical items, uses dynamic programming optimized with a monotonic queue to achieve an O(NW) time complexity.
//   • Invariants: `dp[c]` represents the maximum value achievable for capacity `c` considering all items processed up to the current iteration.; For each remainder `y`, the deque stores indices `k` such that `G_{k, y}` values are monotonically decreasing from front to back.
//   • Tips: Carefully define DP states, often `dp[c]` for the maximum value at capacity `c`.; For multiple items, iterate through items and then capacities, or vice-versa, considering `w_i` remainder groups.
//   • Pitfalls: Incorrectly handling item counts or capacity limits in DP transitions.; Off-by-one errors in monotonic queue window management, leading to incorrect maximums.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} prices
 * @param {number} k
 * @return {number}
 */
var maximumProfit = function(prices, k) {
    const n = prices.length;
    if (n === 0) return 0;

    // dp[i][j][0] = max profit on day i with j transactions and no stock in hand
    // dp[i][j][1] = max profit on day i with j transactions and one stock in hand
    const dp = Array.from({ length: n }, () => 
        Array.from({ length: k + 1 }, () => [0, -Infinity])
    );

    for (let i = 0; i < n; i++) {
        for (let j = 1; j <= k; j++) {
            if (i > 0) {
                dp[i][j][0] = Math.max(dp[i - 1][j][0], dp[i - 1][j][1] + prices[i]);
                dp[i][j][1] = Math.max(dp[i - 1][j][1], dp[i - 1][j - 1][0] - prices[i]);
            } else {
                // Base case for the first day
                dp[i][j][0] = 0;
                dp[i][j][1] = -prices[i];
            }
        }
    }

    let maxProfit = 0;
    for (let j = 1; j <= k; j++) {
        maxProfit = Math.max(maxProfit, dp[n - 1][j][0]);
    }
    
    return maxProfit;
};
