# Source: https://leetcode.com/problems/paint-house-iii/   |   Difficulty: Hard
#
# Problem Description:
# There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that have been painted last summer should not be painted again.
#
# A neighborhood is a maximal group of continuous houses that are painted with the same color.
#
#
# 	For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2}, {1,1}].
#
#
# Given an array houses, an m x n matrix cost and an integer target where:
#
#
# 	houses[i]: is the color of the house i, and 0 if the house is not painted yet.
# 	cost[i][j]: is the cost of paint the house i with the color j + 1.
#
#
# Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods. If it is not possible, return -1.
#
# Example:
# Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
# Output: 9
# Explanation: Paint houses of this way [1,2,2,1,1]
# This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
# Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
#
# Constraints:
# m == houses.length == cost.length
# 	n == cost[i].length
# 	1 <= m <= 100
# 	1 <= n <= 20
# 	1 <= target <= m
# 	0 <= houses[i] <= n
# 	1 <= cost[i][j] <= 104
#

class Solution(object):
    def minCost(self, houses, cost, m, n, target):
        """
        :type houses: List[int]
        :type cost: List[List[int]]
        :type m: int
        :type n: int
        :type target: int
        :rtype: int
        """
        import sys
        dp = [[[sys.maxsize] * (target + 1) for _ in range(n + 1)] for _ in range(m + 1)]
        dp[0][0][0] = 0
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                for k in range(1, target + 1):
                    if houses[i - 1] != 0 and houses[i - 1] != j:
                        continue
                    cost_to_paint = 0 if houses[i - 1] == j else cost[i - 1][j - 1]
                    for p in range(1, n + 1):
                        if p == j:
                            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][p][k] + cost_to_paint)
                        else:
                            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][p][k - 1] + cost_to_paint)
        
        ans = min(dp[m][j][target] for j in range(1, n + 1))
        return -1 if ans == sys.maxsize else ans