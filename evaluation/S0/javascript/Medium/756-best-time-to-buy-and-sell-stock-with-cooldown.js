// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array prices where prices[i] is the price of a given stock on the ith day.
//
// Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
//
//
// 	After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
//
//
// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
//
// Example:
// Input: prices = [1,2,3,0,2]
// Output: 3
// Explanation: transactions = [buy, sell, cooldown, buy, sell]
//
// Constraints:
// 1 <= prices.length <= 5000
// 	0 <= prices[i] <= 1000
//

/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(prices) {
    const n = prices.length;
    if (n <= 1) return 0;
    let buy = -prices[0];
    let sell = 0;
    let cooldown = 0;
    for (let i = 1; i < n; i++) {
        const prevBuy = buy;
        buy = Math.max(buy, cooldown - prices[i]);
        cooldown = Math.max(cooldown, sell);
        sell = prevBuy + prices[i];
    }
    return Math.max(sell, cooldown);
};