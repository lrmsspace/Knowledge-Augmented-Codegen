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

/**
 * @param {number[]} prices
 * @param {number} k
 * @return {number}
 */
var maximumProfit = function(prices, k) {
    const n = prices.length;
    const dp = Array.from({ length: k + 1 }, () => Array(n).fill(0));   
    for (let t = 1; t <= k; t++) {
        let maxDiff = -prices[0];
        for (let d = 1; d < n; d++) {
            dp[t][d] = Math.max(dp[t][d - 1], prices[d] + maxDiff);
            maxDiff = Math.max(maxDiff, dp[t - 1][d - 1] - prices[d]);
        }
    }
    return dp[k][n - 1];    
};
