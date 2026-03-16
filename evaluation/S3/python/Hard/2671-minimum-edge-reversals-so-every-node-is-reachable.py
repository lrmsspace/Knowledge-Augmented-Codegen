# Source: https://leetcode.com/problems/minimum-edge-reversals-so-every-node-is-reachable/   |   Difficulty: Hard
#
# Problem Description:
# There is a simple directed graph with n nodes labeled from 0 to n - 1. The graph would form a tree if its edges were bi-directional.
#
# You are given an integer n and a 2D integer array edges, where edges[i] = [ui, vi] represents a directed edge going from node ui to node vi.
#
# An edge reversal changes the direction of an edge, i.e., a directed edge going from node ui to node vi becomes a directed edge going from node vi to node ui.
#
# For every node i in the range [0, n - 1], your task is to independently calculate the minimum number of edge reversals required so it is possible to reach any other node starting from node i through a sequence of directed edges.
#
# Return an integer array answer, where answer[i] is the  minimum number of edge reversals required so it is possible to reach any other node starting from node i through a sequence of directed edges.
#
# Example:
# Input: n = 4, edges = [[2,0],[2,1],[1,3]]
# Output: [1,1,0,2]
# Explanation: The image above shows the graph formed by the edges.
# For node 0: after reversing the edge [2,0], it is possible to reach any other node starting from node 0.
# So, answer[0] = 1.
# For node 1: after reversing the edge [2,1], it is possible to reach any other node starting from node 1.
# So, answer[1] = 1.
# For node 2: it is already possible to reach any other node starting from node 2.
# So, answer[2] = 0.
# For node 3: after reversing the edges [1,3] and [2,1], it is possible to reach any other node starting from node 3.
# So, answer[3] = 2.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ui == edges[i][0] < n
# 	0 <= vi == edges[i][1] < n
# 	ui != vi
# 	The input is generated such that if the edges were bi-directional, the graph would be a tree.
#
# Helpful references (internal KB):
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
#   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
#   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
#   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
#   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Prüfer code (tree, array, simulation, two-pointers)
#   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
#   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
#   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
#   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
#   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minEdgeReversals(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append((v, 0))  # Original direction
            graph[v].append((u, 1))  # Reversed direction

        def bfs(start):
            visited = [False] * n
            queue = deque([(start, 0)])  # (node, reversals)
            visited[start] = True
            total_reversals = 0

            while queue:
                node, reversals = queue.popleft()
                total_reversals += reversals

                for neighbor, cost in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        queue.append((neighbor, cost))

            return total_reversals

        return [bfs(i) for i in range(n)]