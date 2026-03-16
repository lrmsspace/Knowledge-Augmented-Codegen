# Source: https://leetcode.com/problems/minimum-edge-weight-equilibrium-queries-in-a-tree/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates that there is an edge between nodes ui and vi with weight wi in the tree.
#
# You are also given a 2D integer array queries of length m, where queries[i] = [ai, bi]. For each query, find the minimum number of operations required to make the weight of every edge on the path from ai to bi equal. In one operation, you can choose any edge of the tree and change its weight to any value.
#
# Note that:
#
#
# 	Queries are independent of each other, meaning that the tree returns to its initial state on each new query.
# 	The path from ai to bi is a sequence of distinct nodes starting with node ai and ending with node bi such that every two adjacent nodes in the sequence share an edge in the tree.
#
#
# Return an array answer of length m where answer[i] is the answer to the ith query.
#
# Example:
# Input: n = 7, edges = [[0,1,1],[1,2,1],[2,3,1],[3,4,2],[4,5,2],[5,6,2]], queries = [[0,3],[3,6],[2,6],[0,6]]
# Output: [0,0,1,3]
# Explanation: In the first query, all the edges in the path from 0 to 3 have a weight of 1. Hence, the answer is 0.
# In the second query, all the edges in the path from 3 to 6 have a weight of 2. Hence, the answer is 0.
# In the third query, we change the weight of edge [2,3] to 2. After this operation, all the edges in the path from 2 to 6 have a weight of 2. Hence, the answer is 1.
# In the fourth query, we change the weights of edges [0,1], [1,2] and [2,3] to 2. After these operations, all the edges in the path from 0 to 6 have a weight of 2. Hence, the answer is 3.
# For each queries[i], it can be shown that answer[i] is the minimum number of operations needed to equalize all the edge weights in the path from ai to bi.
#
# Constraints:
# 1 <= n <= 104
# 	edges.length == n - 1
# 	edges[i].length == 3
# 	0 <= ui, vi < n
# 	1 <= wi <= 26
# 	The input is generated such that edges represents a valid tree.
# 	1 <= queries.length == m <= 2 * 104
# 	queries[i].length == 2
# 	0 <= ai, bi < n
#

class Solution(object):
    def minOperationsQueries(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, Counter
        import sys
        sys.setrecursionlimit(10**7)

        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        LOG = 15
        parent = [[-1] * n for _ in range(LOG)]
        depth = [0] * n
        weight_count = [defaultdict(int) for _ in range(n)]

        def dfs(u, p):
            for v, w in tree[u]:
                if v == p:
                    continue
                depth[v] = depth[u] + 1
                parent[0][v] = u
                weight_count[v] = weight_count[u].copy()
                weight_count[v][w] += 1
                dfs(v, u)

        dfs(0, -1)

        for k in range(1, LOG):
            for v in range(n):
                if parent[k - 1][v] != -1:
                    parent[k][v] = parent[k - 1][parent[k - 1][v]]

        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u
            for k in range(LOG - 1, -1, -1):
                if depth[u] - (1 << k) >= depth[v]:
                    u = parent[k][u]
            if u == v:
                return u
            for k in range(LOG - 1, -1, -1):
                if parent[k][u] != parent[k][v]:
                    u = parent[k][u]
                    v = parent[k][v]
            return parent[0][u]

        result = []
        for a, b in queries:
            ancestor = lca(a, b)
            total_edges = depth[a] + depth[b] - 2 * depth[ancestor]
            max_freq = 0
            for w in range(1, 27):
                freq = weight_count[a].get(w, 0) + weight_count[b].get(w, 0) - 2 * weight_count[ancestor].get(w, 0)
                max_freq = max(max_freq, freq)
            result.append(total_edges - max_freq)

        return result