# Source: https://leetcode.com/problems/number-of-ways-to-assign-edge-weights-ii/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected tree with n nodes labeled from 1 to n, rooted at node 1. The tree is represented by a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi.
#
# Initially, all edges have a weight of 0. You must assign each edge a weight of either 1 or 2.
#
# The cost of a path between any two nodes u and v is the total weight of all edges in the path connecting them.
#
# You are given a 2D integer array queries. For each queries[i] = [ui, vi], determine the number of ways to assign weights to edges in the path such that the cost of the path between ui and vi is odd.
#
# Return an array answer, where answer[i] is the number of valid assignments for queries[i].
#
# Since the answer may be large, apply modulo 109 + 7 to each answer[i].
#
# Note: For each query, disregard all edges not in the path between node ui and vi.
#
# Example:
# Input: edges = [[1,2]], queries = [[1,1],[1,2]]
#
# Output: [0,1]
#
# Explanation:
#
#
# 	Query [1,1]: The path from Node 1 to itself consists of no edges, so the cost is 0. Thus, the number of valid assignments is 0.
# 	Query [1,2]: The path from Node 1 to Node 2 consists of one edge (1 → 2). Assigning weight 1 makes the cost odd, while 2 makes it even. Thus, the number of valid assignments is 1.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi]
# 	1 <= queries.length <= 105
# 	queries[i] == [ui, vi]
# 	1 <= ui, vi <= n
# 	edges represents a valid tree.
#
# Helpful references (internal KB):
# - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
#   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
#   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
#   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
#   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
#   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
# - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
#   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
#   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
#   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
#   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
#   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
# - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, lca)
#   • When to use: Use this technique for efficiently answering multiple Range Minimum Queries on a static array, especially when an asymptotically optimal O(1) query time solution is required.
#   • Idea: This algorithm solves the static Range Minimum Query problem by first constructing a Cartesian tree from the input array, then reducing RMQ queries to Lowest Common Ancestor queries on this tree. It achieves an optimal O(N) preprocessing time and O(1) query time.
#   • Invariants: For any node `u` in the Cartesian tree, `value(u)` is the minimum among all values in the original array segment represented by `u`'s subtree.; The in-order traversal of the Cartesian tree nodes' original array indices yields the original array `A`'s indices in increasing order.
#   • Tips: Construct the Cartesian tree efficiently in O(N) time, typically using a stack-based approach.; The value of the LCA of two nodes in the Cartesian tree corresponds to the minimum in the original array range between their indices.
#   • Pitfalls: Incorrectly building the Cartesian tree, especially when handling duplicate values or edge cases like empty arrays.; The Farach-Colton and Bender LCA algorithm is complex to implement and often requires significant effort.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def assignEdgeWeights(self, edges, queries):
        """
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque
        import sys
        sys.setrecursionlimit(10**7)

        MOD = 10**9 + 7
        n = len(edges) + 1

        # Build the tree as an adjacency list
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        # Precompute the depth and parent of each node using DFS
        depth = [0] * (n + 1)
        parent = [[0] * (n + 1) for _ in range(20)]  # up to 2^19 ancestors

        def dfs(node, par):
            parent[0][node] = par
            for neighbor in tree[node]:
                if neighbor != par:
                    depth[neighbor] = depth[node] + 1
                    dfs(neighbor, node)

        dfs(1, 0)

        # Precompute ancestors for binary lifting
        for k in range(1, 20):
            for v in range(1, n + 1):
                parent[k][v] = parent[k - 1][parent[k - 1][v]]

        def lca(u, v):
            if depth[u] < depth[v]:
                u, v = v, u
            # Lift u up to the same depth as v
            diff = depth[u] - depth[v]
            for k in range(20):
                if diff & (1 << k):
                    u = parent[k][u]
            if u == v:
                return u
            # Lift both u and v up until their parents are the same
            for k in reversed(range(20)):
                if parent[k][u] != parent[k][v]:
                    u = parent[k][u]
                    v = parent[k][v]
            return parent[0][u]

        results = []
        for u, v in queries:
            ancestor = lca(u, v)
            path_length = depth[u] + depth[v] - 2 * depth[ancestor]
            # The number of ways to assign weights is 2^(path_length - 1) if path_length > 0 else 0
            if path_length == 0:
                results.append(0)
            else:
                results.append(pow(2, path_length - 1, MOD))

        return results