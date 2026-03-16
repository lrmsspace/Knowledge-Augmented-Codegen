# Source: https://leetcode.com/problems/minimum-weighted-subgraph-with-the-required-paths-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected weighted tree with n nodes, numbered from 0 to n - 1. It is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi.​
#
# Additionally, you are given a 2D integer array queries, where queries[j] = [src1j, src2j, destj].
#
# Return an array answer of length equal to queries.length, where answer[j] is the minimum total weight of a subtree such that it is possible to reach destj from both src1j and src2j using edges in this subtree.
#
# A subtree here is any connected subset of nodes and edges of the original tree forming a valid tree.
#
# Example:
# Input: edges = [[0,1,2],[1,2,3],[1,3,5],[1,4,4],[2,5,6]], queries = [[2,3,4],[0,2,5]]
#
# Output: [12,11]
#
# Explanation:
#
# The blue edges represent one of the subtrees that yield the optimal answer.
#
#
#
#
# 	
# 	answer[0]: The total weight of the selected subtree that ensures a path from src1 = 2 and src2 = 3 to dest = 4 is 3 + 5 + 4 = 12.
# 	
# 	
# 	answer[1]: The total weight of the selected subtree that ensures a path from src1 = 0 and src2 = 2 to dest = 5 is 2 + 3 + 6 = 11.
#
# Constraints:
# 3 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 3
# 	0 <= ui, vi < n
# 	1 <= wi <= 104
# 	1 <= queries.length <= 105
# 	queries[j].length == 3
# 	0 <= src1j, src2j, destj < n
# 	src1j, src2j, and destj are pairwise distinct.
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def minimumWeight(self, edges, queries):
        """
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Build the tree as an adjacency list
        from collections import defaultdict, deque
        import sys

        sys.setrecursionlimit(10**7)

        n = len(edges) + 1
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        # Precompute parent and depth for LCA
        LOG = 17  # since n <= 10^5, log2(10^5) < 17
        parent = [[-1] * n for _ in range(LOG)]
        depth = [0] * n
        dist = [0] * n

        def dfs(u, p):
            for v, w in tree[u]:
                if v != p:
                    parent[0][v] = u
                    depth[v] = depth[u] + 1
                    dist[v] = dist[u] + w
                    dfs(v, u)

        dfs(0, -1)

        for k in range(1, LOG):
            for v in range(n):
                if parent[k-1][v] != -1:
                    parent[k][v] = parent[k-1][parent[k-1][v]]

        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u
            diff = depth[u] - depth[v]
            for k in range(LOG):
                if diff & (1 << k):
                    u = parent[k][u]
            if u == v:
                return u
            for k in reversed(range(LOG)):
                if parent[k][u] != parent[k][v]:
                    u = parent[k][u]
                    v = parent[k][v]
            return parent[0][u]

        def path_weight(u, v):
            ancestor = lca(u, v)
            return dist[u] + dist[v] - 2 * dist[ancestor]

        result = []
        for src1, src2, dest in queries:
            total_weight = path_weight(src1, dest) + path_weight(src2, dest)
            result.append(total_weight)

        return result