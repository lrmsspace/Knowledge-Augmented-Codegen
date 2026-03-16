# Source: https://leetcode.com/problems/paint-house-iv/   |   Difficulty: Medium
#
# Problem Description:
# You are given an even integer n representing the number of houses arranged in a straight line, and a 2D array cost of size n x 3, where cost[i][j] represents the cost of painting house i with color j + 1.
#
# The houses will look beautiful if they satisfy the following conditions:
#
#
# 	No two adjacent houses are painted the same color.
# 	Houses equidistant from the ends of the row are not painted the same color. For example, if n = 6, houses at positions (0, 5), (1, 4), and (2, 3) are considered equidistant.
#
#
# Return the minimum cost to paint the houses such that they look beautiful.
#
# Example:
# Input: n = 4, cost = [[3,5,7],[6,2,9],[4,8,1],[7,3,5]]
#
# Output: 9
#
# Explanation:
#
# The optimal painting sequence is [1, 2, 3, 2] with corresponding costs [3, 2, 1, 3]. This satisfies the following conditions:
#
#
# 	No adjacent houses have the same color.
# 	Houses at positions 0 and 3 (equidistant from the ends) are not painted the same color (1 != 2).
# 	Houses at positions 1 and 2 (equidistant from the ends) are not painted the same color (2 != 3).
#
#
# The minimum cost to paint the houses so that they look beautiful is 3 + 2 + 1 + 3 = 9.
#
# Constraints:
# 2 <= n <= 105
# 	n is even.
# 	cost.length == n
# 	cost[i].length == 3
# 	0 <= cost[i][j] <= 105
#

class Solution(object):
    def minCost(self, n, cost):
        """
        :type n: int
        :type cost: List[List[int]]
        :rtype: int
        """
        dp = [[[float('inf')] * 3 for _ in range(3)] for _ in range(n // 2)]
        
        # Initialize the first pair of houses
        for c1 in range(3):
            for c2 in range(3):
                if c1 != c2:
                    dp[0][c1][c2] = cost[0][c1] + cost[1][c2]
        
        # Fill the DP table
        for i in range(1, n // 2):
            for c1 in range(3):
                for c2 in range(3):
                    if c1 != c2:
                        for pc1 in range(3):
                            for pc2 in range(3):
                                if pc1 != pc2 and pc1 != c2 and pc2 != c1:
                                    dp[i][c1][c2] = min(dp[i][c1][c2], dp[i - 1][pc1][pc2] + cost[2 * i][c1] + cost[2 * i + 1][c2])
        
        # Find the minimum cost from the last pair of houses
        min_cost = float('inf')
        for c1 in range(3):
            for c2 in range(3):
                if c1 != c2:
                    min_cost = min(min_cost, dp[n // 2 - 1][c1][c2])
        
        return min_cost