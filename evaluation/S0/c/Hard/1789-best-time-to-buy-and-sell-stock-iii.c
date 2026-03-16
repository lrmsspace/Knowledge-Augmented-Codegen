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

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;
    int firstBuy = -prices[0];
    int firstSell = 0;
    int secondBuy = -prices[0];
    int secondSell = 0;

    for (int i = 1; i < pricesSize; ++i) {
        firstBuy = (firstBuy > -prices[i]) ? firstBuy : -prices[i];
        firstSell = (firstSell > firstBuy + prices[i]) ? firstSell : firstBuy + prices[i];
        secondBuy = (secondBuy > firstSell - prices[i]) ? secondBuy : firstSell - prices[i];
        secondSell = (secondSell > secondBuy + prices[i]) ? secondSell : secondBuy + prices[i];
    }

    return secondSell;      
}
