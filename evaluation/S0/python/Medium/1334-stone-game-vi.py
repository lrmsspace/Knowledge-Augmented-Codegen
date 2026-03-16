# Source: https://leetcode.com/problems/stone-game-vi/   |   Difficulty: Medium
#
# Problem Description:
# Alice and Bob take turns playing a game, with Alice starting first.
#
# There are n stones in a pile. On each player's turn, they can remove a stone from the pile and receive points based on the stone's value. Alice and Bob may value the stones differently.
#
# You are given two integer arrays of length n, aliceValues and bobValues. Each aliceValues[i] and bobValues[i] represents how Alice and Bob, respectively, value the ith stone.
#
# The winner is the person with the most points after all the stones are chosen. If both players have the same amount of points, the game results in a draw. Both players will play optimally. Both players know the other's values.
#
# Determine the result of the game, and:
#
#
# 	If Alice wins, return 1.
# 	If Bob wins, return -1.
# 	If the game results in a draw, return 0.
#
# Example:
# Input: aliceValues = [1,3], bobValues = [2,1]
# Output: 1
# Explanation:
# If Alice takes stone 1 (0-indexed) first, Alice will receive 3 points.
# Bob can only choose stone 0, and will only receive 2 points.
# Alice wins.
#
# Constraints:
# n == aliceValues.length == bobValues.length
# 	1 <= n <= 105
# 	1 <= aliceValues[i], bobValues[i] <= 100
#

class Solution(object):
    def stoneGameVI(self, aliceValues, bobValues):
        """
        :type aliceValues: List[int]
        :type bobValues: List[int]
        :rtype: int
        """
        n = len(aliceValues)
        stones = []
        
        for i in range(n):
            stones.append((aliceValues[i] + bobValues[i], aliceValues[i], bobValues[i]))
        
        stones.sort(reverse=True)
        
        alice_score = 0
        bob_score = 0
        
        for i in range(n):
            if i % 2 == 0:
                alice_score += stones[i][1]
            else:
                bob_score += stones[i][2]
        
        if alice_score > bob_score:
            return 1
        elif bob_score > alice_score:
            return -1
        else:
            return 0