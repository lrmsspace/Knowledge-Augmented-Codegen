# Source: https://leetcode.com/problems/perfect-squares/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the least number of perfect square numbers that sum to n.
#
# A perfect square is an integer that is the square of an integer; in other words, it is the product of some integer with itself. For example, 1, 4, 9, and 16 are perfect squares while 3 and 11 are not.
#
# Example:
# Input: n = 12
# Output: 3
# Explanation: 12 = 4 + 4 + 4.
#
# Constraints:
# 1 <= n <= 104
#

class Solution(object):
    def numSquares(self, n):
        """
        :type n: int
        :rtype: int
        """
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            j = 1
            while j * j <= i:
                dp[i] = min(dp[i], dp[i - j * j] + 1)
                j += 1
                
        return dp[n]