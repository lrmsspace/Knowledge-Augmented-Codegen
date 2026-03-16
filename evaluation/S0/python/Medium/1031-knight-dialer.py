# Source: https://leetcode.com/problems/knight-dialer/   |   Difficulty: Medium
#
# Problem Description:
# The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagram:
#
# A chess knight can move as indicated in the chess diagram below:
#
# We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).
#
# Given an integer n, return how many distinct phone numbers of length n we can dial.
#
# You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.
#
# As the answer may be very large, return the answer modulo 109 + 7.
#
# Example:
# Input: n = 1
# Output: 10
# Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
#
# Constraints:
# 1 <= n <= 5000
#

class Solution(object):
    def knightDialer(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        # Possible moves for a knight from each digit
        moves = {
            0: [4, 6],
            1: [6, 8],
            2: [7, 9],
            3: [4, 8],
            4: [0, 3, 9],
            5: [],
            6: [0, 1, 7],
            7: [2, 6],
            8: [1, 3],
            9: [2, 4]
        }
        
        # dp[i][j] will be the number of distinct numbers of length i ending with digit j
        dp = [[0] * 10 for _ in range(n + 1)]
        
        # Base case: For length 1, there's one way to end with each digit
        for j in range(10):
            dp[1][j] = 1
        
        # Fill the dp table
        for i in range(2, n + 1):
            for j in range(10):
                for move in moves[j]:
                    dp[i][j] = (dp[i][j] + dp[i - 1][move]) % MOD
        
        # Sum all ways to form numbers of length n
        return sum(dp[n]) % MOD