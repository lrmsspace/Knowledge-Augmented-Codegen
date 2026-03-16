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
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
#   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
#   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
#   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
#   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
#   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
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
            graph[u].append((v, 0))  # Original direction, cost 0
            graph[v].append((u, 1))  # Reversed direction, cost 1

        def bfs(start):
            dist = [float('inf')] * n
            dist[start] = 0
            queue = deque([start])

            while queue:
                node = queue.popleft()
                for neighbor, cost in graph[node]:
                    if dist[node] + cost < dist[neighbor]:
                        dist[neighbor] = dist[node] + cost
                        if cost == 0:
                            queue.appendleft(neighbor)  # Prioritize original direction
                        else:
                            queue.append(neighbor)  # Reversed direction goes to the back of the queue
            return dist

        return [bfs(i) for i in range(n)]