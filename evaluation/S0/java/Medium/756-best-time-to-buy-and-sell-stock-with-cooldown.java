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

class Solution {
    public int maxProfit(int[] prices) {
        if (prices == null || prices.length == 0) {
            return 0;
        }

        int n = prices.length;
        int[][] dp = new int[n][2];

        dp[0][0] = 0;           // Not holding stock on day 0
        dp[0][1] = -prices[0]; // Holding stock on day 0

        for (int i = 1; i < n; i++) {
            dp[i][0] = Math.max(dp[i - 1][0], dp[i - 1][1] + prices[i]);
            dp[i][1] = Math.max(dp[i - 1][1], (i >= 2 ? dp[i - 2][0] : 0) - prices[i]);
        }

        return dp[n - 1][0];            
    }
}
