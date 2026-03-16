# Source: https://leetcode.com/problems/stone-game-iv/   |   Difficulty: Hard
#
# Problem Description:
# Alice and Bob take turns playing a game, with Alice starting first.
#
# Initially, there are n stones in a pile. On each player's turn, that player makes a move consisting of removing any non-zero square number of stones in the pile.
#
# Also, if a player cannot make a move, he/she loses the game.
#
# Given a positive integer n, return true if and only if Alice wins the game otherwise return false, assuming both players play optimally.
#
# Example:
# Input: n = 1
# Output: true
# Explanation: Alice can remove 1 stone winning the game because Bob doesn't have any moves.
#
# Constraints:
# 1 <= n <= 105
#

class Solution(object):
    def winnerSquareGame(self, n):
        """
        :type n: int
        :rtype: bool
        """
        dp = [False] * (n + 1)
        
        for i in range(1, n + 1):
            j = 1
            while j * j <= i:
                if not dp[i - j * j]:
                    dp[i] = True
                    break
                j += 1
        
        return dp[n]