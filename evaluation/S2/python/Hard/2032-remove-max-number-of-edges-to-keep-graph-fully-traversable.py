# Source: https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/   |   Difficulty: Hard
#
# Problem Description:
# Alice and Bob have an undirected graph of n nodes and three types of edges:
#
#
# 	Type 1: Can be traversed by Alice only.
# 	Type 2: Can be traversed by Bob only.
# 	Type 3: Can be traversed by both Alice and Bob.
#
#
# Given an array edges where edges[i] = [typei, ui, vi] represents a bidirectional edge of type typei between nodes ui and vi, find the maximum number of edges you can remove so that after removing the edges, the graph can still be fully traversed by both Alice and Bob. The graph is fully traversed by Alice and Bob if starting from any node, they can reach all other nodes.
#
# Return the maximum number of edges you can remove, or return -1 if Alice and Bob cannot fully traverse the graph.
#
# Example:
# Input: n = 4, edges = [[3,1,2],[3,2,3],[1,1,3],[1,2,4],[1,1,2],[2,3,4]]
# Output: 2
# Explanation: If we remove the 2 edges [1,1,2] and [1,1,3]. The graph will still be fully traversable by Alice and Bob. Removing any additional edge will not make it so. So the maximum number of edges we can remove is 2.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= edges.length <= min(105, 3 * n * (n - 1) / 2)
# 	edges[i].length == 3
# 	1 <= typei <= 3
# 	1 <= ui < vi <= n
# 	All tuples (typei, ui, vi) are distinct.
#
# Helpful references (internal KB):
# - Finding Bridges Online (graph, ds, union-find, counting)
#   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
#   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
#   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
#   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
#   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
#   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
#   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
#   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
#   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
#   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxNumEdgesToRemove(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        # Union-Find (Disjoint Set Union) implementation
        class UnionFind:
            def __init__(self, size):
                self.parent = list(range(size))
                self.rank = [1] * size
                self.components = size  # Track the number of components

            def find(self, u):
                if self.parent[u] != u:
                    self.parent[u] = self.find(self.parent[u])  # Path compression
                return self.parent[u]

            def union(self, u, v):
                root_u = self.find(u)
                root_v = self.find(v)

                if root_u != root_v:
                    # Union by rank
                    if self.rank[root_u] > self.rank[root_v]:
                        self.parent[root_v] = root_u
                    elif self.rank[root_u] < self.rank[root_v]:
                        self.parent[root_u] = root_v
                    else:
                        self.parent[root_v] = root_u
                        self.rank[root_u] += 1
                    self.components -= 1  # Decrease component count

        # Initialize Union-Find for Alice and Bob
        uf_alice = UnionFind(n)
        uf_bob = UnionFind(n)

        edges_removed = 0

        # Process type 3 edges first (shared by Alice and Bob)
        for t, u, v in edges:
            if t == 3:
                if uf_alice.union(u - 1, v - 1):  # If union is successful, it means they were in different components
                    uf_bob.union(u - 1, v - 1)  # Also union for Bob
                else:
                    edges_removed += 1  # Edge is redundant

        # Process type 1 edges (Alice only)
        for t, u, v in edges:
            if t == 1:
                if not uf_alice.union(u - 1, v - 1):  # If union is not successful, it means they were already connected
                    edges_removed += 1  # Edge is redundant

        # Process type 2 edges (Bob only)
        for t, u, v in edges:
            if t == 2:
                if not uf_bob.union(u - 1, v - 1):  # If union is not successful, it means they were already connected
                    edges_removed += 1  # Edge is redundant

        # Check if both Alice and Bob can fully traverse the graph
        if uf_alice.components == 1 and uf_bob.components == 1:
            return edges_removed
        else:
            return -1