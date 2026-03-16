# Source: https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/   |   Difficulty: Hard
#
# Problem Description:
# There are n piles of coins on a table. Each pile consists of a positive number of coins of assorted denominations.
#
# In one move, you can choose any coin on top of any pile, remove it, and add it to your wallet.
#
# Given a list piles, where piles[i] is a list of integers denoting the composition of the ith pile from top to bottom, and a positive integer k, return the maximum total value of coins you can have in your wallet if you choose exactly k coins optimally.
#
# Example:
# Input: piles = [[1,100,3],[7,8,9]], k = 2
# Output: 101
# Explanation:
# The above diagram shows the different ways we can choose k coins.
# The maximum total we can obtain is 101.
#
# Constraints:
# n == piles.length
# 	1 <= n <= 1000
# 	1 <= piles[i][j] <= 105
# 	1 <= k <= sum(piles[i].length) <= 2000
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxValueOfCoins(self, piles, k):
        """
        :type piles: List[List[int]]
        :type k: int
        :rtype: int
        """
        n = len(piles)
        dp = [0] * (k + 1)

        for pile in piles:
            prefix_sum = [0]
            for coin in pile:
                prefix_sum.append(prefix_sum[-1] + coin)

            for j in range(k, 0, -1):
                for x in range(1, min(j, len(pile)) + 1):
                    dp[j] = max(dp[j], dp[j - x] + prefix_sum[x])

        return dp[k]