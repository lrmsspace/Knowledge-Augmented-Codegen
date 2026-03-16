# Source: https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
#
# A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
#
# The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
#
# Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.
#
# Example:
# Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
# Output: 3
# Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
# 1) 1 --> 2 --> 5
# 2) 1 --> 2 --> 3 --> 5
# 3) 1 --> 3 --> 5
#
# Constraints:
# 1 <= n <= 2 * 104
# 	n - 1 <= edges.length <= 4 * 104
# 	edges[i].length == 3
# 	1 <= ui, vi <= n
# 	ui != vi
# 	1 <= weighti <= 105
# 	There is at most one edge between any two nodes.
# 	There is at least one path between any two nodes.
#

class Solution(object):
    def countRestrictedPaths(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        import heapq
        from collections import defaultdict

        MOD = 10**9 + 7

        # Build the graph
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        # Dijkstra's algorithm to find shortest paths from node n
        dist = [float('inf')] * (n + 1)
        dist[n] = 0
        min_heap = [(0, n)]  # (distance, node)

        while min_heap:
            d, node = heapq.heappop(min_heap)
            if d > dist[node]:
                continue
            for neighbor, weight in graph[node]:
                new_dist = d + weight
                if new_dist < dist[neighbor]:
                    dist[neighbor] = new_dist
                    heapq.heappush(min_heap, (new_dist, neighbor))

        # DFS with memoization to count restricted paths
        memo = {}

        def dfs(node):
            if node == n:
                return 1
            if node in memo:
                return memo[node]

            total_paths = 0
            for neighbor, _ in graph[node]:
                if dist[neighbor] < dist[node]:  # Restricted path condition
                    total_paths += dfs(neighbor)
                    total_paths %= MOD

            memo[node] = total_paths
            return total_paths

        return dfs(1)