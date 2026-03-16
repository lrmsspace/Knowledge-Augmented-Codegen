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

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize == 0) return 0;

    int hold = -prices[0]; // Max profit when holding a stock
    int sold = 0;          // Max profit when just sold a stock
    int rest = 0;          // Max profit when in cooldown or doing nothing

    for (int i = 1; i < pricesSize; i++) {
        int prev_sold = sold;
        sold = hold + prices[i]; // Sell the stock held
        hold = (hold > rest - prices[i]) ? hold : (rest - prices[i]); // Buy stock or keep holding
        rest = (rest > prev_sold) ? rest : prev_sold; // Cooldown or do nothing
    }

    return (sold > rest) ? sold : rest; // Max profit will be either in sold or rest state      
}
