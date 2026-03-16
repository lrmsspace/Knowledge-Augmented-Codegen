# Source: https://leetcode.com/problems/stone-game-vii/   |   Difficulty: Medium
#
# Problem Description:
# Alice and Bob take turns playing a game, with Alice starting first.
#
# There are n stones arranged in a row. On each player's turn, they can remove either the leftmost stone or the rightmost stone from the row and receive points equal to the sum of the remaining stones' values in the row. The winner is the one with the higher score when there are no stones left to remove.
#
# Bob found that he will always lose this game (poor Bob, he always loses), so he decided to minimize the score's difference. Alice's goal is to maximize the difference in the score.
#
# Given an array of integers stones where stones[i] represents the value of the ith stone from the left, return the difference in Alice and Bob's score if they both play optimally.
#
# Example:
# Input: stones = [5,3,1,4,2]
# Output: 6
# Explanation: 
# - Alice removes 2 and gets 5 + 3 + 1 + 4 = 13 points. Alice = 13, Bob = 0, stones = [5,3,1,4].
# - Bob removes 5 and gets 3 + 1 + 4 = 8 points. Alice = 13, Bob = 8, stones = [3,1,4].
# - Alice removes 3 and gets 1 + 4 = 5 points. Alice = 18, Bob = 8, stones = [1,4].
# - Bob removes 1 and gets 4 points. Alice = 18, Bob = 12, stones = [4].
# - Alice removes 4 and gets 0 points. Alice = 18, Bob = 12, stones = [].
# The score difference is 18 - 12 = 6.
#
# Constraints:
# n == stones.length
# 	2 <= n <= 1000
# 	1 <= stones[i] <= 1000
#

class Solution(object):
    def stoneGameVII(self, stones):
        """
        :type stones: List[int]
        :rtype: int
        """
        n = len(stones)
        prefix_sum = [0] * (n + 1)
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + stones[i]

        dp = [[0] * n for _ in range(n)]

        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                total = prefix_sum[j + 1] - prefix_sum[i]
                dp[i][j] = max(total - stones[i] - dp[i + 1][j],
                               total - stones[j] - dp[i][j - 1])

        return dp[0][n - 1]