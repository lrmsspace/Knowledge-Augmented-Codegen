# Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
#
# You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
#
# Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
#
# The degree of a node is the number of edges connected to it.
#
# Example:
# Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
# Output: true
# Explanation: The above diagram shows a valid way of adding an edge.
# Every node in the resulting graph is connected to an even number of edges.
#
# Constraints:
# 3 <= n <= 105
# 	2 <= edges.length <= 105
# 	edges[i].length == 2
# 	1 <= ai, bi <= n
# 	ai != bi
# 	There are no repeated edges.
#
# Helpful references (internal KB):
# - Finding faces of a planar graph (graph, array, dfs, enumeration)
#   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
#   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
#   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
#   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
#   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
# - Undirected Graphs (graph, matrix, simulation)
#   • When to use: Use when modeling symmetric relationships between entities, analyzing graph properties like connectivity or degrees, or simulating processes on a network where connections are bidirectional.
#   • Idea: An undirected graph consists of a set of vertices and a set of edges, where each edge connects two vertices symmetrically. Basic operations often have a time complexity of O(V+E) or O(V^2) depending on representation.
#   • Invariants: For every edge (u, v) in the graph, the edge (v, u) also exists.; The sum of degrees of all vertices equals twice the number of edges.
#   • Tips: Choose adjacency list for sparse graphs, adjacency matrix for dense graphs.; Degrees of vertices are easily calculated from adjacency representations.
#   • Pitfalls: Forgetting to add both (u,v) and (v,u) when using an adjacency matrix or list.; Not handling disconnected components during full graph traversals.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
#   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
#   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
#   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
#   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
#   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isPossible(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict

        degree = [0] * (n + 1)
        for u, v in edges:
            degree[u] += 1
            degree[v] += 1

        odd_degree_nodes = [i for i in range(1, n + 1) if degree[i] % 2 == 1]

        if len(odd_degree_nodes) == 0:
            return True
        elif len(odd_degree_nodes) == 2:
            u, v = odd_degree_nodes
            if [u, v] not in edges and [v, u] not in edges:
                return True
            for w in range(1, n + 1):
                if w != u and w != v and ([u, w] not in edges and [w, u] not in edges) and ([v, w] not in edges and [w, v] not in edges):
                    return True
            return False
        elif len(odd_degree_nodes) == 4:
            a, b, c, d = odd_degree_nodes
            pairs = [(a, b), (a, c), (a, d), (b, c), (b, d), (c, d)]
            valid_pairs = []
            for x, y in pairs:
                if [x, y] not in edges and [y, x] not in edges:
                    valid_pairs.append((x, y))
            return len(valid_pairs) >= 2
        else:
            return False