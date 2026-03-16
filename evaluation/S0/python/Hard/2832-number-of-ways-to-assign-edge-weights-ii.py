# Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
#
# Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
#
# The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
#
# You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.
#
# Return an array answer, where answer[i] is the number of valid assignments for queries[i].
#
# Since the answer may be large, apply modulo 109 + 7 to each answer[i].
#
# Note: For each query, disregard all edges not in the path between node ui and vi.
#
# Example:
# Input: edges = [[1,2]], queries = [[1,1],[1,2]]
#
# Output: [0,1]
#
# Explanation:
#
#
# 	Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
# 	Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi]
# 	1 <= queries.length <= 105
# 	queries[i] == [ui, vi]
# 	1 <= ui, vi <= n
# 	edges represents a valid tree.
#

class Solution(object):
    def assignEdgeWeights(self, edges, queries):
        """
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        MOD = 10**9 + 7
        n = len(edges) + 1
        
        from collections import defaultdict, deque
        
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        depth = [0] * (n + 1)
        visited = [False] * (n + 1)
        visited[1] = True
        
        queue = deque([1])
        while queue:
            node = queue.popleft()
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    depth[neighbor] = depth[node] + 1
                    queue.append(neighbor)
        
        result = []
        for u, v in queries:
            path_length = depth[u] + depth[v] - 2 * depth[self.lca(u, v, depth, graph)]
            if path_length % 2 == 1:
                result.append(pow(2, path_length - 1, MOD))
            else:
                result.append(0)
        
        return result