# Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array prices where prices[i] is the price of a given stock on the ith day.
#
# Find the maximum profit you can achieve. You may complete at most two transactions.
#
# Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
#
# Example:
# Input: prices = [3,3,5,0,0,3,1,4]
# Output: 6
# Explanation: Buy on day 4 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.
# Then buy on day 7 (price = 1) and sell on day 8 (price = 4), profit = 4-1 = 3.
#
# Constraints:
# 1 <= prices.length <= 105
# 	0 <= prices[i] <= 105
#

class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        n = len(prices)
        if n == 0:
            return 0
        
        # First pass: max profit
        left_profits = [0] * n
        min_price = prices[0]

        for i in range(1, n):
            min_price = min(min_price, prices[i])
            left_profits[i] = max(left_profits[i-1], prices[i] - min_price)
        # Second pass: max profit
        max_price = prices[-1]
        max_total_profit = left_profits[-1]
        right_profit = 0
        for i in range(n-2, -1, -1):
            max_price = max(max_price, prices[i])
            right_profit = max(right_profit, max_price - prices[i])
            max_total_profit = max(max_total_profit, left_profits[i] + right_profit)
        return max_total_profit