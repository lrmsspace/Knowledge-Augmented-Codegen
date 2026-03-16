# Source: https://leetcode.com/problems/maximal-network-rank/   |   Difficulty: Medium
#
# Problem Description:
# There is an infrastructure of n cities with some number of roads connecting these cities. Each roads[i] = [ai, bi] indicates that there is a bidirectional road between cities ai and bi.
#
# The network rank of two different cities is defined as the total number of directly connected roads to either city. If a road is directly connected to both cities, it is only counted once.
#
# The maximal network rank of the infrastructure is the maximum network rank of all pairs of different cities.
#
# Given the integer n and the array roads, return the maximal network rank of the entire infrastructure.
#
# Example:
# Input: n = 4, roads = [[0,1],[0,3],[1,2],[1,3]]
# Output: 4
# Explanation: The network rank of cities 0 and 1 is 4 as there are 4 roads that are connected to either 0 or 1. The road between 0 and 1 is only counted once.
#
# Constraints:
# 2 <= n <= 100
# 	0 <= roads.length <= n * (n - 1) / 2
# 	roads[i].length == 2
# 	0 <= ai, bi <= n-1
# 	ai != bi
# 	Each pair of cities has at most one road connecting them.
#

class Solution(object):
    def maximalNetworkRank(self, n, roads):
        """
        :type n: int
        :type roads: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        road_count = [0] * n
        connected = defaultdict(set)

        for a, b in roads:
            road_count[a] += 1
            road_count[b] += 1
            connected[a].add(b)
            connected[b].add(a)

        max_rank = 0

        for i in range(n):
            for j in range(i + 1, n):
                current_rank = road_count[i] + road_count[j]
                if j in connected[i]:
                    current_rank -= 1
                max_rank = max(max_rank, current_rank)

        return max_rank