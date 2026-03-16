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
# Helpful references (internal KB):
# - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
#   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
#   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
#   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
#   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
#   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumWeight(self, edges, queries):
        """
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        # Build the tree from edges
        from collections import defaultdict
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        # Precompute the depth and parent for each node using DFS
        n = len(tree)
        LOG = n.bit_length()  # Maximum power of 2 less than n
        parent = [[-1] * n for _ in range(LOG)]
        depth = [0] * n

        def dfs(node, par):
            for neighbor, weight in tree[node]:
                if neighbor == par:
                    continue
                parent[0][neighbor] = node
                depth[neighbor] = depth[node] + weight
                dfs(neighbor, node)

        dfs(0, -1)

        # Precompute ancestors for binary lifting
        for j in range(1, LOG):
            for i in range(n):
                if parent[j-1][i] != -1:
                    parent[j][i] = parent[j-1][parent[j-1][i]]

        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u
            diff = depth[u] - depth[v]
            for i in range(LOG):
                if diff & (1 << i):
                    u = parent[i][u]
            if u == v:
                return u
            for i in reversed(range(LOG)):
                if parent[i][u] != parent[i][v]:
                    u = parent[i][u]
                    v = parent[i][v]
            return parent[0][u]

        def distance(u, v):
            ancestor = lca(u, v)
            return depth[u] + depth[v] - 2 * depth[ancestor]

        result = []
        for src1, src2, dest in queries:
            dist_src1_dest = distance(src1, dest)
            dist_src2_dest = distance(src2, dest)
            dist_src1_src2 = distance(src1, src2)
            total_weight = dist_src1_dest + dist_src2_dest - dist_src1_src2
            result.append(total_weight)

        return result
            