# Source: https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected graph. You are given an integer n which is the number of nodes in the graph and an array edges, where each edges[i] = [ui, vi] indicates that there is an undirected edge between ui and vi.
#
# A connected trio is a set of three nodes where there is an edge between every pair of them.
#
# The degree of a connected trio is the number of edges where one endpoint is in the trio, and the other is not.
#
# Return the minimum degree of a connected trio in the graph, or -1 if the graph has no connected trios.
#
# Example:
# Input: n = 6, edges = [[1,2],[1,3],[3,2],[4,1],[5,2],[3,6]]
# Output: 3
# Explanation: There is exactly one trio, which is [1,2,3]. The edges that form its degree are bolded in the figure above.
#
# Constraints:
# 2 <= n <= 400
# 	edges[i].length == 2
# 	1 <= edges.length <= n * (n-1) / 2
# 	1 <= ui, vi <= n
# 	ui != vi
# 	There are no repeated edges.
#

class Solution(object):
    def minTrioDegree(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        graph = defaultdict(set)
        degree = [0] * (n + 1)

        for u, v in edges:
            graph[u].add(v)
            graph[v].add(u)
            degree[u] += 1
            degree[v] += 1

        min_degree = float('inf')

        for u in range(1, n + 1):
            for v in graph[u]:
                if v > u:
                    for w in graph[v]:
                        if w > v and w in graph[u]:
                            trio_degree = degree[u] + degree[v] + degree[w] - 6
                            min_degree = min(min_degree, trio_degree)

        return min_degree if min_degree != float('inf') else -1