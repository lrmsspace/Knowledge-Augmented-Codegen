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

class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        // If k >= n/2, we can make unlimited transactions
        if (k >= n / 2) {
            int totalProfit = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i - 1]) {
                    totalProfit += prices[i] - prices[i - 1];
                }
            }
            return totalProfit;
        }
        
        // DP arrays
        vector<vector<int>> buy(k + 1, vector<int>(n, INT_MIN));
        vector<vector<int>> sell(k + 1, vector<int>(n, 0));
        
        for (int t = 1; t <= k; t++) {
            buy[t][0] = -prices[0];
            for (int d = 1; d < n; d++) {
                buy[t][d] = max(buy[t][d - 1], sell[t - 1][d - 1] - prices[d]);
                sell[t][d] = max(sell[t][d - 1], buy[t][d - 1] + prices[d]);
            }
        }
        
        return sell[k][n - 1];          
    }
};
