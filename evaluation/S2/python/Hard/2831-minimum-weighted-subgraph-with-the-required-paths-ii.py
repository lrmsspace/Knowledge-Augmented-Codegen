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
# - Lowest Common Ancestor - Tarjan's off-line algorithm (tree, ds, dfs, union-find)
#   • When to use: Use when you need to answer multiple Lowest Common Ancestor (LCA) queries on a static tree, and all queries are available before processing.
#   • Idea: Tarjan's off-line LCA algorithm efficiently computes the Lowest Common Ancestor for multiple pairs of nodes in a tree using a single Depth-First Search traversal combined with a Disjoint Set Union data structure, achieving nearly linear time complexity.
#   • Invariants: When DFS is at node `v`, all its children's subtrees have been fully processed and merged into `v`'s DSU set.; For any node `x` whose DFS has completed, `ancestor[find_set(x)]` stores an ancestor of `x` on the path to the root.
#   • Tips: Initialize each node as its own set in DSU with itself as the ancestor.; Process queries for a node only after its children's subtrees are fully processed.
#   • Pitfalls: Not suitable for online LCA queries or dynamic tree structures.; Incorrectly updating the `ancestor` array in the DSU can lead to wrong LCAs.
# - Second Best Minimum Spanning Tree (graph, array, mst-kruskal, enumeration)
#   • When to use: Use when you need to find a spanning tree with the second smallest total edge weight, often for redundancy or alternative network path planning. It's applicable in scenarios requiring fault tolerance beyond a single optimal solution.
#   • Idea: This algorithm finds a spanning tree with the second minimum total edge weight in a connected, undirected graph. It involves finding the primary MST, then modifying it by replacing one MST edge with a non-MST edge.
#   • Invariants: The primary MST is always a valid spanning tree with minimum total weight.; Adding any non-MST edge (u,v) to the MST creates exactly one cycle.
#   • Tips: First, compute the primary Minimum Spanning Tree (MST) using an algorithm like Kruskal's or Prim's.; For each edge not in the MST, adding it to the MST creates a unique cycle. Find the maximum weight edge on this cycle.
#   • Pitfalls: Naively recomputing an entire MST for each removed edge is inefficient (O(V * E log E)).; Incorrectly identifying the maximum weight edge on the cycle formed by adding a non-MST edge.
# - Heavy-light decomposition (tree, array, dfs, divide-and-conquer, tree-dp)
#   • When to use: When you need to efficiently perform path queries or updates on a tree, transforming tree paths into linear segments for data structures like segment trees.
#   • Idea: Heavy-light decomposition partitions a tree into disjoint heavy paths, ensuring any root-to-node path crosses at most O(log N) heavy paths. This reduces tree path queries to segment operations, typically achieving O(log^2 N) or O(log N) complexity.
#   • Invariants: Every node is part of exactly one heavy path.; Traversing from any node to the root involves at most O(log N) heavy path switches.
#   • Tips: Precompute subtree sizes for all nodes to identify heavy edges.; Map heavy paths to contiguous array segments for efficient range queries.
#   • Pitfalls: Misidentifying heavy edges or having more than one heavy child per node.; Off-by-one errors when converting tree path segments to array indices.
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
        # Step 1: Build the tree from edges
        from collections import defaultdict
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))
        
        # Step 2: Precompute LCA and path weights using DFS
        n = len(tree)
        LOG = n.bit_length()  # Maximum depth for binary lifting
        parent = [[-1] * n for _ in range(LOG)]
        max_weight = [[0] * n for _ in range(LOG)]
        depth = [0] * n
        
        def dfs(node, par):
            for neighbor, weight in tree[node]:
                if neighbor == par:
                    continue
                parent[0][neighbor] = node
                max_weight[0][neighbor] = weight
                depth[neighbor] = depth[node] + 1
                dfs(neighbor, node)
        
        dfs(0, -1)  # Assuming node 0 is the root
        
        # Step 3: Binary lifting preprocessing
        for i in range(1, LOG):
            for j in range(n):
                if parent[i-1][j] != -1:
                    parent[i][j] = parent[i-1][parent[i-1][j]]
                    max_weight[i][j] = max(max_weight[i-1][j], max_weight[i-1][parent[i-1][j]])
        
        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u
            diff = depth[u] - depth[v]
            max_edge = 0
            
            for i in range(LOG):
                if diff & (1 << i):
                    max_edge = max(max_edge, max_weight[i][u])
                    u = parent[i][u]
            
            if u == v:
                return u, max_edge
            
            for i in reversed(range(LOG)):
                if parent[i][u] != parent[i][v]:
                    max_edge = max(max_edge, max_weight[i][u], max_weight[i][v])
                    u = parent[i][u]
                    v = parent[i][v]
            
            return parent[0][u], max(max_edge, max_weight[0][u], max_weight[0][v])
        
        # Step 4: Process queries
        answer = []
        for src1, src2, dest in queries:
            lca_node, max_edge = lca(src1, src2)
            lca_dest, max_edge_dest = lca(dest, lca_node)
            answer.append(max(max_edge, max_edge_dest))

        return answer