// Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array prices where prices[i] is the price of a given stock on the ith day.
//
// On each day, you may decide to buy and/or sell the stock. You can only hold at most one share of the stock at any time. However, you can sell and buy the stock multiple times on the same day, ensuring you never hold than one share of the stock.
//
// Find and return the maximum profit you can achieve.
//
// Example:
// Input: prices = [7,1,5,3,6,4]
// Output: 7
// Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
// Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.
// Total profit is 4 + 3 = 7.
//
// Constraints:
// 1 <= prices.length <= 3 * 104
// 	0 <= prices[i] <= 104
//

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int totalProfit = 0;
        for (size_t i = 1; i < prices.size(); ++i) {
            if (prices[i] > prices[i - 1]) {
                totalProfit += prices[i] - prices[i - 1];
            }
        }
        return totalProfit;         
    }
};
