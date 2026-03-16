// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.
//
// Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.
//
// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
//
// Example:
// Input: k = 2, prices = [2,4,1]
// Output: 2
// Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
//
// Constraints:
// 1 <= k <= 100
// 	1 <= prices.length <= 1000
// 	0 <= prices[i] <= 1000
//

/**
 * @param {number} k
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(k, prices) {
    


    let n = prices.length;
    if (n <= 1) return 0;

    // If k is large enough, we can make as many transactions as we want
    if (k >= Math.floor(n / 2)) {
        let maxProfit = 0;
        for (let i = 1; i < n; i++) {
            if (prices[i] > prices[i - 1]) {
                maxProfit += prices[i] - prices[i - 1];
            }
        }
        return maxProfit;
    }

    // DP approach for limited transactions
    const dp = Array.from({ length: k + 1 }, () => new Array(n).fill(0));
    for (let i = 1; i <= k; i++) {
        let maxDiff = -prices[0];
        for (let j = 1; j < n; j++) {
            dp[i][j] = Math.max(dp[i][j - 1], prices[j] + maxDiff);
            maxDiff = Math.max(maxDiff, dp[i - 1][j] - prices[j]);
        }
    }
    return dp[k][n - 1];    
        
};
