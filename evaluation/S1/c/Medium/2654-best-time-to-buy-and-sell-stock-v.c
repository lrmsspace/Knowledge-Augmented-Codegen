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
// - Knapsack Problem (array, knapsack, dp-1d, dp-2d)
//   • When to use: Use when selecting items, each with a weight and value, to maximize total value within a limited capacity, where each item can be chosen multiple times. It is suitable for problems exhibiting optimal substructure and overlapping subproblems.
//   • Idea: The Knapsack Problem involves selecting items to maximize total value within a fixed capacity. The complete knapsack variant, where items can be taken multiple times, is typically solved using dynamic programming in O(nW) time and O(W) space.
//   • Invariants: For 2D DP `f[i][j]`, it represents the maximum value obtainable using only the first `i` items with a total weight not exceeding `j`.; For 1D DP `dp[j]`, after processing item `i`, it stores the maximum value obtainable with a total weight not exceeding `j`, considering all items up to `i`.
//   • Tips: For the complete knapsack, iterate capacity `j` forwards (from `w_i` to `W`) when using 1D DP to allow multiple selections of the current item.; The 1D DP array `dp[j]` stores the maximum value achievable for exactly capacity `j`.
//   • Pitfalls: Confusing 0-1 knapsack with complete knapsack, especially in the 1D DP iteration direction for capacity.; Incorrectly initializing the DP array, leading to incorrect base cases or propagation.
// - Digit DP (array, number, digit-dp)
//   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
//   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
//   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
//   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
//   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long maximumProfit(int* prices, int pricesSize, int k) {
    // DP array to store maximum profit at each transaction count
    long long dp[k + 1];
    for (int i = 0; i <= k; i++) {
        dp[i] = 0;
    }

    for (int t = 1; t <= k; t++) {
        long long maxDiffBuy = -prices[0];   // Max profit after buying
        long long maxDiffSell = prices[0];   // Max profit after short selling

        for (int d = 1; d < pricesSize; d++) {
            // Update dp[t] for normal transaction
            dp[t] = dp[t] > prices[d] + maxDiffBuy ? dp[t] : prices[d] + maxDiffBuy;
            maxDiffBuy = maxDiffBuy > dp[t - 1] - prices[d] ? maxDiffBuy : dp[t - 1] - prices[d];

            // Update dp[t] for short selling transaction
            dp[t] = dp[t] > maxDiffSell - prices[d] ? dp[t] : maxDiffSell - prices[d];
            maxDiffSell = maxDiffSell > dp[t - 1] + prices[d] ? maxDiffSell : dp[t - 1] + prices[d];
        }
    }

    return dp[k];       
}
