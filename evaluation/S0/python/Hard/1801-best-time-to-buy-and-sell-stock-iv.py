# Source: https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.
#
# Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.
#
# Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).
#
# Example:
# Input: k = 2, prices = [2,4,1]
# Output: 2
# Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.
#
# Constraints:
# 1 <= k <= 100
# 	1 <= prices.length <= 1000
# 	0 <= prices[i] <= 1000
#

class Solution(object):
    def maxProfit(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """
        n = len(prices)
        if n == 0:
            return 0

        # If k is larger than n/2, we can make unlimited transactions
        if k >= n // 2:
            total_profit = 0
            for i in range(1, n):
                if prices[i] > prices[i - 1]:
                    total_profit += prices[i] - prices[i - 1]
            return total_profit

        # DP table where dp[i][j] represents the max profit up to day j with at most i transactions
        dp = [[0] * n for _ in range(k + 1)]

        for i in range(1, k + 1):
            max_diff = -prices[0]
            for j in range(1, n):
                dp[i][j] = max(dp[i][j - 1], prices[j] + max_diff)
                max_diff = max(max_diff, dp[i - 1][j] - prices[j])

        return dp[k][n - 1]