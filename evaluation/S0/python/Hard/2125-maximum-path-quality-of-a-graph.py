# Source: https://leetcode.com/problems/maximum-path-quality-of-a-graph/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected graph with n nodes numbered from 0 to n - 1 (inclusive). You are given a 0-indexed integer array values where values[i] is the value of the ith node. You are also given a 0-indexed 2D integer array edges, where each edges[j] = [uj, vj, timej] indicates that there is an undirected edge between the nodes uj and vj, and it takes timej seconds to travel between the two nodes. Finally, you are given an integer maxTime.
#
# A valid path in the graph is any path that starts at node 0, ends at node 0, and takes at most maxTime seconds to complete. You may visit the same node multiple times. The quality of a valid path is the sum of the values of the unique nodes visited in the path (each node's value is added at most once to the sum).
#
# Return the maximum quality of a valid path.
#
# Note: There are at most four edges connected to each node.
#
# Example:
# Input: values = [0,32,10,43], edges = [[0,1,10],[1,2,15],[0,3,10]], maxTime = 49
# Output: 75
# Explanation:
# One possible path is 0 -> 1 -> 0 -> 3 -> 0. The total time taken is 10 + 10 + 10 + 10 = 40 <= 49.
# The nodes visited are 0, 1, and 3, giving a maximal path quality of 0 + 32 + 43 = 75.
#
# Constraints:
# n == values.length
# 	1 <= n <= 1000
# 	0 <= values[i] <= 108
# 	0 <= edges.length <= 2000
# 	edges[j].length == 3 
# 	0 <= uj < vj <= n - 1
# 	10 <= timej, maxTime <= 100
# 	All the pairs [uj, vj] are unique.
# 	There are at most four edges connected to each node.
# 	The graph may not be connected.
#

class Solution(object):
    def maximalPathQuality(self, values, edges, maxTime):
        """
        :type values: List[int]
        :type edges: List[List[int]]
        :type maxTime: int
        :rtype: int
        """
        from collections import defaultdict
        import heapq

        graph = defaultdict(list)
        for u, v, t in edges:
            graph[u].append((v, t))
            graph[v].append((u, t))

        max_quality = 0
        n = len(values)

        def dfs(node, time_left, visited, quality):
            nonlocal max_quality
            if node == 0:
                max_quality = max(max_quality, quality)

            for neighbor, travel_time in graph[node]:
                if time_left >= travel_time:
                    added_quality = 0
                    if neighbor not in visited:
                        added_quality = values[neighbor]
                        visited.add(neighbor)

                    dfs(neighbor, time_left - travel_time, visited, quality + added_quality)

                    if added_quality > 0:
                        visited.remove(neighbor)

        visited = set()
        visited.add(0)
        dfs(0, maxTime, visited, values[0])

        return max_quality