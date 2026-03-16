# Source: https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/   |   Difficulty: Hard
#
# Problem Description:
# There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.
#
# You must connect one node from the first tree with another node from the second tree with an edge.
#
# Return the minimum possible diameter of the resulting tree.
#
# The diameter of a tree is the length of the longest path between any two nodes in the tree.
#
# Example:
# Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]
#
# Output: 3
#
# Explanation:
#
# We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.
#
# Constraints:
# 1 <= n, m <= 105
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
    def minimumDiameterAfterMerge(self, edges1, edges2):
        """
        :type edges1: List[List[int]]
        :type edges2: List[List[int]]
        :rtype: int
        """
        def bfs(edges, start):
            from collections import deque
            n = len(edges) + 1
            graph = [[] for _ in range(n)]
            for u, v in edges:
                graph[u].append(v)
                graph[v].append(u)
            
            dist = [-1] * n
            dist[start] = 0
            queue = deque([start])
            while queue:
                node = queue.popleft()
                for neighbor in graph[node]:
                    if dist[neighbor] == -1:
                        dist[neighbor] = dist[node] + 1
                        queue.append(neighbor)
            farthest_node = dist.index(max(dist))
            return farthest_node, max(dist)
        
        def tree_diameter(edges):
            far_node, _ = bfs(edges, 0)
            _, diameter = bfs(edges, far_node)
            return diameter
        
        dia1 = tree_diameter(edges1)
        dia2 = tree_diameter(edges2)
        
        return max(dia1, dia2, (dia1 + 1) // 2 + (dia2 + 1) // 2 + 1)