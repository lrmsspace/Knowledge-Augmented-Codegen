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

int maxProfit(int k, int* prices, int pricesSize) {
    if (pricesSize == 0 || k == 0) return 0;

    // If k is larger than half the number of days, we can make unlimited transactions
    if (k >= pricesSize / 2) {
        int maxProfit = 0;
        for (int i = 1; i < pricesSize; i++) {
            if (prices[i] > prices[i - 1]) {
                maxProfit += prices[i] - prices[i - 1];
            }
        }
        return maxProfit;
    }

    // DP arrays
    int buy[k + 1];
    int sell[k + 1];

    // Initialize buy array with minimum values
    for (int i = 0; i <= k; i++) {
        buy[i] = INT_MIN;
        sell[i] = 0;
    }

    // Fill DP arrays
    for (int priceIdx = 0; priceIdx < pricesSize; priceIdx++) {
        int price = prices[priceIdx];
        for (int transaction = 1; transaction <= k; transaction++) {
            buy[transaction] = fmax(buy[transaction], sell[transaction - 1] - price);
            sell[transaction] = fmax(sell[transaction], buy[transaction] + price);
        }
    }

    return sell[k];
            
}
