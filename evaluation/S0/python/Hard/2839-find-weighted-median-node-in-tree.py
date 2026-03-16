# Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
#
# The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
#
# You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
#
# Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
#
# Example:
# Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
#
# Output: [0,1]
#
# Explanation:
#
#
#
#
# 	
# 		
# 			Query
# 			Path
# 			Edge
# 			Weights
# 			Total
# 			Path
# 			Weight
# 			Half
# 			Explanation
# 			Answer
# 		
# 	
# 	
# 		
# 			[1, 0]
# 			1 → 0
# 			[7]
# 			7
# 			3.5
# 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
# 			0
# 		
# 		
# 			[0, 1]
# 			0 → 1
# 			[7]
# 			7
# 			3.5
# 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
# 			1
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi, wi]
# 	0 <= ui, vi < n
# 	1 <= wi <= 109
# 	1 <= queries.length <= 105
# 	queries[j] == [uj, vj]
# 	0 <= uj, vj < n
# 	The input is generated such that edges represents a valid tree.
#

class Solution(object):
    def findMedian(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict
        import bisect

        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        parent = [-1] * n
        depth = [0] * n
        dist = [0] * n
        LOG = 17
        up = [[-1] * n for _ in range(LOG)]

        def dfs(u, p):
            for v, w in tree[u]:
                if v != p:
                    parent[v] = u
                    depth[v] = depth[u] + 1
                    dist[v] = dist[u] + w
                    up[0][v] = u
                    dfs(v, u)

        dfs(0, -1)

        for i in range(1, LOG):
            for v in range(n):
                if up[i - 1][v] != -1:
                    up[i][v] = up[i - 1][up[i - 1][v]]

        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u
            diff = depth[u] - depth[v]
            for i in range(LOG):
                if diff & (1 << i):
                    u = up[i][u]
            if u == v:
                return u
            for i in reversed(range(LOG)):
                if up[i][u] != up[i][v]:
                    u = up[i][u]
                    v = up[i][v]
            return parent[u]

        def get_kth_ancestor(u, k):
            for i in range(LOG):
                if k & (1 << i):
                    u = up[i][u]
            return u

        result = []
        for u, v in queries:
            ancestor = lca(u, v)
            total_dist = dist[u] + dist[v] - 2 * dist[ancestor]
            half_dist = total_dist / 2

            if dist[u] - dist[ancestor] >= half_dist:
                low, high = 0, depth[u] - depth[ancestor]
                while low < high:
                    mid = (low + high) // 2
                    if dist[u] - dist[get_kth_ancestor(u, mid)] >= half_dist:
                        low = mid + 1
                    else:
                        high = mid
                median = get_kth_ancestor(u, low - 1)
            else:
                half_dist -= dist[u] - dist[ancestor]
                low, high = 0, depth[v] - depth[ancestor]
                while low < high:
                    mid = (low + high) // 2
                    if dist[get_kth_ancestor(v, mid)] - dist[ancestor] >= half_dist:
                        high = mid
                    else:
                        low = mid + 1
                median = get_kth_ancestor(v, low)
            result.append(median)
        return result