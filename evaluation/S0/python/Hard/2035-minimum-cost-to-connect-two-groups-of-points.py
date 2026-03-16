# Source: https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/   |   Difficulty: Hard
#
# Problem Description:
# You are given two groups of points where the first group has size1 points, the second group has size2 points, and size1 >= size2.
#
# The cost of the connection between any two points are given in an size1 x size2 matrix where cost[i][j] is the cost of connecting point i of the first group and point j of the second group. The groups are connected if each point in both groups is connected to one or more points in the opposite group. In other words, each point in the first group must be connected to at least one point in the second group, and each point in the second group must be connected to at least one point in the first group.
#
# Return the minimum cost it takes to connect the two groups.
#
# Example:
# Input: cost = [[15, 96], [36, 2]]
# Output: 17
# Explanation: The optimal way of connecting the groups is:
# 1--A
# 2--B
# This results in a total cost of 17.
#
# Constraints:
# size1 == cost.length
# 	size2 == cost[i].length
# 	1 <= size1, size2 <= 12
# 	size1 >= size2
# 	0 <= cost[i][j] <= 100
#

class Solution(object):
    def connectTwoGroups(self, cost):
        """
        :type cost: List[List[int]]
        :rtype: int
        """
        m, n = len(cost), len(cost[0])
        dp = [float('inf')] * (1 << n)
        dp[0] = 0

        for i in range(m):
            new_dp = [float('inf')] * (1 << n)
            for mask in range(1 << n):
                for j in range(n):
                    new_mask = mask | (1 << j)
                    new_dp[new_mask] = min(new_dp[new_mask], dp[mask] + cost[i][j])
            dp = new_dp

        for j in range(n):
            bit = 1 << j
            for mask in range(1 << n):
                if mask & bit == 0:
                    dp[mask | bit] = min(dp[mask | bit], dp[mask] + min(cost[i][j] for i in range(m)))

        return dp[(1 << n) - 1]