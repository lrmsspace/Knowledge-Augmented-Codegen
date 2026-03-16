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

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if (n == 0) return 0;
        
        vector<int> leftProfits(n, 0);
        vector<int> rightProfits(n, 0);
        
        // Left to right pass
        int minPrice = prices[0];
        for (int i = 1; i < n; i++) {
            minPrice = min(minPrice, prices[i]);
            leftProfits[i] = max(leftProfits[i - 1], prices[i] - minPrice);
        }
        
        // Right to left pass
        int maxPrice = prices[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            maxPrice = max(maxPrice, prices[i]);
            rightProfits[i] = max(rightProfits[i + 1], maxPrice - prices[i]);
        }
        
        // Combine results
        int maxProfit = 0;
        for (int i = 0; i < n; i++) {
            maxProfit = max(maxProfit, leftProfits[i] + rightProfits[i]);
        }
        
        return maxProfit;           
    }
};
