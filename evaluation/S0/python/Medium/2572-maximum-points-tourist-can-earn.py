# Source: https://leetcode.com/problems/maximum-points-tourist-can-earn/   |   Difficulty: Medium
#
# Problem Description:
# You are given two integers, n and k, along with two 2D integer arrays, stayScore and travelScore.
#
# A tourist is visiting a country with n cities, where each city is directly connected to every other city. The tourist's journey consists of exactly k 0-indexed days, and they can choose any city as their starting point.
#
# Each day, the tourist has two choices:
#
#
# 	Stay in the current city: If the tourist stays in their current city curr during day i, they will earn stayScore[i][curr] points.
# 	Move to another city: If the tourist moves from their current city curr to city dest, they will earn travelScore[curr][dest] points.
#
#
# Return the maximum possible points the tourist can earn.
#
# Example:
# Input: n = 2, k = 1, stayScore = [[2,3]], travelScore = [[0,2],[1,0]]
#
# Output: 3
#
# Explanation:
#
# The tourist earns the maximum number of points by starting in city 1 and staying in that city.
#
# Constraints:
# 1 <= n <= 200
# 	1 <= k <= 200
# 	n == travelScore.length == travelScore[i].length == stayScore[i].length
# 	k == stayScore.length
# 	1 <= stayScore[i][j] <= 100
# 	0 <= travelScore[i][j] <= 100
# 	travelScore[i][i] == 0
#

class Solution(object):
    def maxScore(self, n, k, stayScore, travelScore):
        """
        :type n: int
        :type k: int
        :type stayScore: List[List[int]]
        :type travelScore: List[List[int]]
        :rtype: int
        """
        dp = [[0] * n for _ in range(k + 1)]
        
        for day in range(1, k + 1):
            for curr_city in range(n):
                # Option 1: Stay in the current city
                stay_points = dp[day - 1][curr_city] + stayScore[day - 1][curr_city]
                dp[day][curr_city] = max(dp[day][curr_city], stay_points)
                
                # Option 2: Move from another city
                for prev_city in range(n):
                    if prev_city != curr_city:
                        move_points = dp[day - 1][prev_city] + travelScore[prev_city][curr_city]
                        dp[day][curr_city] = max(dp[day][curr_city], move_points)
        
        return max(dp[k])