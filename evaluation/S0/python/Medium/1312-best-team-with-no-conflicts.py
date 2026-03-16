# Source: https://leetcode.com/problems/best-team-with-no-conflicts/   |   Difficulty: Medium
#
# Problem Description:
# You are the manager of a basketball team. For the upcoming tournament, you want to choose the team with the highest overall score. The score of the team is the sum of scores of all the players in the team.
#
# However, the basketball team is not allowed to have conflicts. A conflict exists if a younger player has a strictly higher score than an older player. A conflict does not occur between players of the same age.
#
# Given two lists, scores and ages, where each scores[i] and ages[i] represents the score and age of the ith player, respectively, return the highest overall score of all possible basketball teams.
#
# Example:
# Input: scores = [1,3,5,10,15], ages = [1,2,3,4,5]
# Output: 34
# Explanation: You can choose all the players.
#
# Constraints:
# 1 <= scores.length, ages.length <= 1000
# 	scores.length == ages.length
# 	1 <= scores[i] <= 106
# 	1 <= ages[i] <= 1000
#

class Solution(object):
    def bestTeamScore(self, scores, ages):
        """
        :type scores: List[int]
        :type ages: List[int]
        :rtype: int
        """
        players = sorted(zip(ages, scores))
        n = len(players)
        dp = [0] * n
        
        for i in range(n):
            dp[i] = players[i][1]
            for j in range(i):
                if players[i][1] >= players[j][1]:
                    dp[i] = max(dp[i], dp[j] + players[i][1])
        
        return max(dp)