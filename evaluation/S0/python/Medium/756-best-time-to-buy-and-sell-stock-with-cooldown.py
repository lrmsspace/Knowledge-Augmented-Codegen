# Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array prices where prices[i] is the price of a given stock on the ith day.
#
# Find the maximum profit you can achieve. You may complete as many transactions as you like (i.e., buy one and sell one share of the stock multiple times) with the following restrictions:
#
#
# 	After you sell your stock, you cannot buy stock on the next day (i.e., cooldown one day).
#
#
# Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
#
# Example:
# Input: prices = [1,2,3,0,2]
# Output: 3
# Explanation: transactions = [buy, sell, cooldown, buy, sell]
#
# Constraints:
# 1 <= prices.length <= 5000
# 	0 <= prices[i] <= 1000
#

class Solution(object):
    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """
        if not prices:
            return 0

        n = len(prices)
        buy = [0] * n
        sell = [0] * n
        cooldown = [0] * n

        buy[0] = -prices[0]
        sell[0] = 0
        cooldown[0] = 0

        for i in range(1, n):
            buy[i] = max(buy[i - 1], cooldown[i - 1] - prices[i])
            sell[i] = max(sell[i - 1], buy[i - 1] + prices[i])
            cooldown[i] = max(cooldown[i - 1], sell[i - 1])

        return sell[-1]