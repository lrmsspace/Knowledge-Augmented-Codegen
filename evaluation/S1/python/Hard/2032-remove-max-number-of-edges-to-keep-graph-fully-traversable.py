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
# - 0-1 BFS (graph, deque, 01-bfs, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
#   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
#   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
#   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
#   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
# - Minimum Spanning Trees (graph, greedy)
#   • When to use: When you need to find a subset of edges in a connected, edge-weighted graph that connects all vertices with the minimum possible total edge weight. Useful for network design problems where minimizing connection costs is crucial.
#   • Idea: A Minimum Spanning Tree (MST) algorithm finds a subset of edges in an edge-weighted graph that connects all vertices with the minimum possible total weight, forming a tree. This is typically solved using greedy approaches with a time complexity often involving sorting edges or using a priority queue.
#   • Invariants: The set of edges selected so far always forms a forest.; Each connected component formed by the chosen edges is a valid subtree of some Minimum Spanning Tree.
#   • Tips: Greedy approaches often work by iteratively adding the cheapest valid edge or expanding from a starting vertex.; The cut property and cycle property are fundamental for proving correctness of MST algorithms.
#   • Pitfalls: Assuming the graph is always connected; disconnected graphs require finding a minimum spanning forest.; Incorrectly applying the greedy choice without ensuring it maintains the MST property (e.g., creating a cycle).
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
                self.count = size  # Number of disjoint sets

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
                    self.count -= 1  # Decrease count of disjoint sets
                    return True
                return False

        # Initialize Union-Find for Alice and Bob
        uf_alice = UnionFind(n)
        uf_bob = UnionFind(n)

        edges_used = 0

        # Process type 3 edges first (shared by both Alice and Bob)
        for t, u, v in edges:
            if t == 3:
                if uf_alice.union(u - 1, v - 1):  # Convert to 0-based index
                    uf_bob.union(u - 1, v - 1)  # Ensure Bob's union is also updated
                    edges_used += 1

        # Process type 1 edges (Alice only)
        for t, u, v in edges:
            if t == 1:
                if uf_alice.union(u - 1, v - 1):
                    edges_used += 1

        # Process type 2 edges (Bob only)
        for t, u, v in edges:
            if t == 2:
                if uf_bob.union(u - 1, v - 1):
                    edges_used += 1

        # Check if both Alice and Bob can traverse the entire graph
        if uf_alice.count == 1 and uf_bob.count == 1:
            return len(edges) - edges_used
        else:
            return -1
            