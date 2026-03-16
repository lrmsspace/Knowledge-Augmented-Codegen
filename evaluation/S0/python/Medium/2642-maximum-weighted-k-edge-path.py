# Source: https://leetcode.com/problems/maximum-weighted-k-edge-path/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n and a Directed Acyclic Graph (DAG) with n nodes labeled from 0 to n - 1. This is represented by a 2D array edges, where edges[i] = [ui, vi, wi] indicates a directed edge from node ui to vi with weight wi.
#
# You are also given two integers, k and t.
#
# Your task is to determine the maximum possible sum of edge weights for any path in the graph such that:
#
#
# 	The path contains exactly k edges.
# 	The total sum of edge weights in the path is strictly less than t.
#
#
# Return the maximum possible sum of weights for such a path. If no such path exists, return -1.
#
# Example:
# Input: n = 3, edges = [[0,1,1],[1,2,2]], k = 2, t = 4
#
# Output: 3
#
# Explanation:
#
#
#
#
# 	The only path with k = 2 edges is 0 -> 1 -> 2 with weight 1 + 2 = 3 < t.
# 	Thus, the maximum possible sum of weights less than t is 3.
#
# Constraints:
# 1 <= n <= 300
# 	0 <= edges.length <= 300
# 	edges[i] = [ui, vi, wi]
# 	0 <= ui, vi < n
# 	ui != vi
# 	1 <= wi <= 10
# 	0 <= k <= 300
# 	1 <= t <= 600
# 	The input graph is guaranteed to be a DAG.
# 	There are no duplicate edges.
#

class Solution(object):
    def maxWeight(self, n, edges, k, t):
        """
        :type n: int
        :type edges: List[List[int]]
        :type k: int
        :type t: int
        :rtype: int
        """
        from collections import defaultdict
        import heapq

        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))

        dp = [[-1] * (k + 1) for _ in range(n)]
        dp[0][0] = 0

        for edge_count in range(1, k + 1):
            for u in range(n):
                if dp[u][edge_count - 1] != -1:
                    for v, w in graph[u]:
                        new_weight = dp[u][edge_count - 1] + w
                        if new_weight < t:
                            dp[v][edge_count] = max(dp[v][edge_count], new_weight)

        max_weight = -1
        for u in range(n):
            max_weight = max(max_weight, dp[u][k])

        return max_weight