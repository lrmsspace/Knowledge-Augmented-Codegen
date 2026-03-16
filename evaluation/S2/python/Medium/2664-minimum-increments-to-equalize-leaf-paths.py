# Source: https://leetcode.com/problems/minimum-increments-to-equalize-leaf-paths/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n and an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi] indicates an edge from node ui to vi .
#
# Each node i has an associated cost given by cost[i], representing the cost to traverse that node.
#
# The score of a path is defined as the sum of the costs of all nodes along the path.
#
# Your goal is to make the scores of all root-to-leaf paths equal by increasing the cost of any number of nodes by any non-negative amount.
#
# Return the minimum number of nodes whose cost must be increased to make all root-to-leaf path scores equal.
#
# Example:
# Input: n = 3, edges = [[0,1],[0,2]], cost = [2,1,3]
#
# Output: 1
#
# Explanation:
#
#
#
# There are two root-to-leaf paths:
#
#
# 	Path 0 → 1 has a score of 2 + 1 = 3.
# 	Path 0 → 2 has a score of 2 + 3 = 5.
#
#
# To make all root-to-leaf path scores equal to 5, increase the cost of node 1 by 2.
# Only one node is increased, so the output is 1.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi]
# 	0 <= ui, vi < n
# 	cost.length == n
# 	1 <= cost[i] <= 109
# 	The input is generated such that edges represents a valid tree.
#
# Helpful references (internal KB):
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Prüfer code (tree, heap, simulation, greedy)
#   • When to use: Use to uniquely encode a labeled tree into a sequence of numbers or reconstruct a labeled tree from such a sequence. It's valuable for counting labeled trees and problems involving tree generation.
#   • Idea: Prüfer code uniquely encodes a labeled tree into a sequence by iteratively removing the smallest-labeled leaf and recording its neighbor. This process, which can be implemented in O(N log N) or O(N) time, continues until only two nodes remain.
#   • Invariants: The generated sequence contains `k` elements after `k` leaf removals.; All nodes with degree 1 are correctly identified as leaves.
#   • Tips: Maintain an array of node degrees for O(1) degree updates.; Use a min-priority queue or a `next_leaf` pointer for efficient smallest leaf retrieval.
#   • Pitfalls: Forgetting to update neighbor degrees after removing a leaf.; Incorrectly identifying the next smallest leaf, especially when new leaves are formed.
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
    def minIncrease(self, n, edges, cost):
        """
        :type n: int
        :type edges: List[List[int]]
        :type cost: List[int]
        :rtype: int
        """
        from collections import defaultdict

        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)

        def dfs(node):
            if node not in tree:
                return cost[node], 0  # (max_path_cost, increments_needed)
            
            max_child_cost = 0
            increments_needed = 0
            
            for child in tree[node]:
                child_cost, child_increments = dfs(child)
                max_child_cost = max(max_child_cost, child_cost)
                increments_needed += child_increments
            
            if cost[node] < max_child_cost:
                increments_needed += 1
                return max_child_cost, increments_needed
            else:
                return cost[node], increments_needed

        _, result = dfs(0)
        return result