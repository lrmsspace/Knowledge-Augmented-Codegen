// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array prices where prices[i] is the price of a given stock on the ith day.
//
// Find the maximum profit you can achieve. You may complete at most two transactions.
//
// Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
//
// Example:
// Input: prices = [3,3,5,0,0,3,1,4]
// Output: 6
// Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
// Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
//
// Constraints:
// 1 <= prices.length <= 105
// 	0 <= prices[i] <= 105
//

/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfit = function(prices) {

    const n = prices.length;
    if (n === 0) return 0;
    const leftProfits = new Array(n).fill(0);
    const rightProfits = new Array(n).fill(0);
    let minPrice = prices[0];
    for (let i = 1; i < n; i++) {
        minPrice = Math.min(minPrice, prices[i]);
        leftProfits[i] = Math.max(leftProfits[i - 1], prices[i] - minPrice);
    }
    let maxPrice = prices[n - 1];
    for (let i = n - 2; i >= 0; i--) {
        maxPrice = Math.max(maxPrice, prices[i]);
        rightProfits[i] = Math.max(rightProfits[i + 1], maxPrice - prices[i]);
    }
    let maxProfit = 0;
    for (let i = 0; i < n; i++) {
        maxProfit = Math.max(maxProfit, leftProfits[i] + rightProfits[i]);
    }
    return maxProfit;   
};
