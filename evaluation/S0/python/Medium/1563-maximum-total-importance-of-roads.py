# Source: https://leetcode.com/problems/maximum-total-importance-of-roads/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n denoting the number of cities in a country. The cities are numbered from 0 to n - 1.
#
# You are also given a 2D integer array roads where roads[i] = [ai, bi] denotes that there exists a bidirectional road connecting cities ai and bi.
#
# You need to assign each city with an integer value from 1 to n, where each value can only be used once. The importance of a road is then defined as the sum of the values of the two cities it connects.
#
# Return the maximum total importance of all roads possible after assigning the values optimally.
#
# Example:
# Input: n = 5, roads = [[0,1],[1,2],[2,3],[0,2],[1,3],[2,4]]
# Output: 43
# Explanation: The figure above shows the country and the assigned values of [2,4,5,3,1].
# - The road (0,1) has an importance of 2 + 4 = 6.
# - The road (1,2) has an importance of 4 + 5 = 9.
# - The road (2,3) has an importance of 5 + 3 = 8.
# - The road (0,2) has an importance of 2 + 5 = 7.
# - The road (1,3) has an importance of 4 + 3 = 7.
# - The road (2,4) has an importance of 5 + 1 = 6.
# The total importance of all roads is 6 + 9 + 8 + 7 + 7 + 6 = 43.
# It can be shown that we cannot obtain a greater total importance than 43.
#
# Constraints:
# 2 <= n <= 5 * 104
# 	1 <= roads.length <= 5 * 104
# 	roads[i].length == 2
# 	0 <= ai, bi <= n - 1
# 	ai != bi
# 	There are no duplicate roads.
#

class Solution(object):
    def maximumImportance(self, n, roads):
        """
        :type n: int
        :type roads: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        degree = [0] * n
        for a, b in roads:
            degree[a] += 1
            degree[b] += 1

        nodes = sorted(range(n), key=lambda x: degree[x])
        
        importance = [0] * n
        for i, node in enumerate(nodes):
            importance[node] = i + 1

        total_importance = 0
        for a, b in roads:
            total_importance += importance[a] + importance[b]

        return total_importance