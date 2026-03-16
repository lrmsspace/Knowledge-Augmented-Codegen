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
# Helpful references (internal KB):
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
#   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
#   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
#   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
#   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
#   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxTargetNodes(self, edges1, edges2):
        """
        :type edges1: List[List[int]]
        :type edges2: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        def build_graph(edges):
            graph = defaultdict(list)
            for u, v in edges:
                graph[u].append(v)
                graph[v].append(u)
            return graph

        def bfs(graph, start):
            visited = set()
            queue = deque([start])
            count = 0
            while queue:
                node = queue.popleft()
                if node not in visited:
                    visited.add(node)
                    count += 1
                    for neighbor in graph[node]:
                        if neighbor not in visited:
                            queue.append(neighbor)
            return count

        graph1 = build_graph(edges1)
        graph2 = build_graph(edges2)

        n = len(edges1) + 1
        m = len(edges2) + 1
        result = [0] * n

        for i in range(n):
            max_targets = 0
            for j in range(m):
                # Connect node i from tree 1 to node j from tree 2
                # Calculate the number of target nodes for node i
                targets_in_tree1 = bfs(graph1, i)
                targets_in_tree2 = bfs(graph2, j)
                max_targets = max(max_targets, targets_in_tree1 + targets_in_tree2 - 1)  # -1 to avoid double counting the connected node
            result[i] = max_targets

        return result