# Source: https://leetcode.com/problems/maximize-the-number-of-target-nodes-after-connecting-trees-ii/   |   Difficulty: Hard
#
# Problem Description:
# There exist two undirected trees with n and m nodes, labeled from [0, n - 1] and [0, m - 1], respectively.
#
# You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
#
# Node u is target to node v if the number of edges on the path from u to v is even. Note that a node is always target to itself.
#
# Return an array of n integers answer, where answer[i] is the maximum possible number of nodes that are target to node i of the first tree if you had to connect one node from the first tree to another node in the second tree.
#
# Note that queries are independent from each other. That is, for every query you will remove the added edge before proceeding to the next query.
#
# Example:
# Input: edges1 = [[0,1],[0,2],[2,3],[2,4]], edges2 = [[0,1],[0,2],[0,3],[2,7],[1,4],[4,5],[4,6]]
#
# Output: [8,7,7,8,8]
#
# Explanation:
#
#
# 	For i = 0, connect node 0 from the first tree to node 0 from the second tree.
# 	For i = 1, connect node 1 from the first tree to node 4 from the second tree.
# 	For i = 2, connect node 2 from the first tree to node 7 from the second tree.
# 	For i = 3, connect node 3 from the first tree to node 0 from the second tree.
# 	For i = 4, connect node 4 from the first tree to node 4 from the second tree.
#
# Constraints:
# 2 <= n, m <= 105
# 	edges1.length == n - 1
# 	edges2.length == m - 1
# 	edges1[i].length == edges2[i].length == 2
# 	edges1[i] = [ai, bi]
# 	0 <= ai, bi < n
# 	edges2[i] = [ui, vi]
# 	0 <= ui, vi < m
# 	The input is generated such that edges1 and edges2 represent valid trees.
#

class Solution(object):
    def maxTargetNodes(self, edges1, edges2):
        """
        :type edges1: List[List[int]]
        :type edges2: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        def bfs_count_parity(edges, n):
            graph = defaultdict(list)
            for u, v in edges:
                graph[u].append(v)
                graph[v].append(u)

            parity_count = [0, 0]
            visited = [False] * n
            queue = deque([(0, 0)])  # (node, depth)
            visited[0] = True

            while queue:
                node, depth = queue.popleft()
                parity_count[depth % 2] += 1
                for neighbor in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        queue.append((neighbor, depth + 1))

            return parity_count

        n1 = len(edges1) + 1
        n2 = len(edges2) + 1

        parity_count1 = bfs_count_parity(edges1, n1)
        parity_count2 = bfs_count_parity(edges2, n2)

        result = []
        for i in range(n1):
            if i % 2 == 0:
                result.append(parity_count1[0] + parity_count2[0])
            else:
                result.append(parity_count1[1] + parity_count2[1])

        return result   