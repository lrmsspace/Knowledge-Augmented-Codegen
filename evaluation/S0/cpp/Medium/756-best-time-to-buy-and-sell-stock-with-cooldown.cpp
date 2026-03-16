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
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;

        vector<int> hold(n, 0);    // Max profit on day i when holding a stock
        vector<int> sold(n, 0);    // Max profit on day i when just sold a stock
        vector<int> rest(n, 0);    // Max profit on day i when in cooldown or doing nothing

        hold[0] = -prices[0];
        sold[0] = 0;
        rest[0] = 0;

        for (int i = 1; i < n; ++i) {
            hold[i] = max(hold[i - 1], rest[i - 1] - prices[i]);
            sold[i] = hold[i - 1] + prices[i];
            rest[i] = max(rest[i - 1], sold[i - 1]);
        }

        return max(sold[n - 1], rest[n - 1]);           
    }
};
