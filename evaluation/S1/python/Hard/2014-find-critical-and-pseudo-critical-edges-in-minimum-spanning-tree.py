# Source: https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/   |   Difficulty: Hard
#
# Problem Description:
# Given a weighted undirected connected graph with n vertices numbered from 0 to n - 1, and an array edges where edges[i] = [ai, bi, weighti] represents a bidirectional and weighted edge between nodes ai and bi. A minimum spanning tree (MST) is a subset of the graph's edges that connects all vertices without cycles and with the minimum possible total edge weight.
#
# Find all the critical and pseudo-critical edges in the given graph's minimum spanning tree (MST). An MST edge whose deletion from the graph would cause the MST weight to increase is called a critical edge. On the other hand, a pseudo-critical edge is that which can appear in some MSTs but not all.
#
# Note that you can return the indices of the edges in any order.
#
# Example:
# Input: n = 5, edges = [[0,1,1],[1,2,1],[2,3,2],[0,3,2],[0,4,3],[3,4,3],[1,4,6]]
# Output: [[0,1],[2,3,4,5]]
# Explanation: The figure above describes the graph.
# The following figure shows all the possible MSTs:
#
# Notice that the two edges 0 and 1 appear in all MSTs, therefore they are critical edges, so we return them in the first list of the output.
# The edges 2, 3, 4, and 5 are only part of some MSTs, therefore they are considered pseudo-critical edges. We add them to the second list of the output.
#
# Constraints:
# 2 <= n <= 100
# 	1 <= edges.length <= min(200, n * (n - 1) / 2)
# 	edges[i].length == 3
# 	0 <= ai < bi < n
# 	1 <= weighti <= 1000
# 	All pairs (ai, bi) are distinct.
#
# Helpful references (internal KB):
# - Minimum spanning tree - Kruskal with Disjoint Set Union (graph, ds, mst-kruskal, union-find)
#   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or the number of edges is not excessively large compared to vertices.
#   • Idea: Sorts all graph edges by weight and iteratively adds the cheapest edge that connects two previously disconnected components using a Disjoint Set Union (DSU) data structure. This process builds an MST with O(M log M) or O(M log N) time complexity.
#   • Invariants: After processing k edges, the chosen edges form a forest where each tree is a component of the MST.; Any edge not yet processed has a weight greater than or equal to all processed edges.
#   • Tips: Sort edges by weight in non-decreasing order.; Initialize DSU such that each vertex is in its own set.
#   • Pitfalls: Forgetting to sort edges, leading to an incorrect MST.; Inefficient DSU implementation without path compression or union by rank/size.
# - Finding bridges in a graph in O(N+M) (graph, dfs)
#   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
#   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
#   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
#   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
#   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
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
    def findCriticalAndPseudoCriticalEdges(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: List[List[int]]
        """
        # Step 1: Kruskal's algorithm to find the weight of the MST
        def kruskal(n, edges, exclude_edge=None, include_edge=None):
            parent = list(range(n))
            rank = [0] * n
            
            def find(x):
                if parent[x] != x:
                    parent[x] = find(parent[x])
                return parent[x]
            
            def union(x, y):
                rootX = find(x)
                rootY = find(y)
                if rootX != rootY:
                    if rank[rootX] > rank[rootY]:
                        parent[rootY] = rootX
                    elif rank[rootX] < rank[rootY]:
                        parent[rootX] = rootY
                    else:
                        parent[rootY] = rootX
                        rank[rootX] += 1
            
            total_weight = 0
            
            # If we need to include a specific edge, do it first
            if include_edge is not None:
                u, v, w, idx = include_edge
                union(u, v)
                total_weight += w
            
            for u, v, w, idx in edges:
                if idx == exclude_edge:
                    continue
                if find(u) != find(v):
                    union(u, v)
                    total_weight += w
            
            # Check if all vertices are connected
            root = find(0)
            for i in range(1, n):
                if find(i) != root:
                    return float('inf')  # Not all vertices are connected
            
            return total_weight
        
        # Step 2: Sort edges by weight and keep track of original indices
        indexed_edges = [(u, v, w, i) for i, (u, v, w) in enumerate(edges)]
        indexed_edges.sort(key=lambda x: x[2])  # Sort by weight
        
        # Step 3: Find the weight of the original MST
        original_mst_weight = kruskal(n, indexed_edges)
        
        critical_edges = []
        pseudo_critical_edges = []
        
        # Step 4: Check each edge for critical and pseudo-critical status
        for u, v, w, idx in indexed_edges:
            # Check if it's a critical edge
            if kruskal(n, indexed_edges, exclude_edge=idx) > original_mst_weight:
                critical_edges.append(idx)
            # Check if it's a pseudo-critical edge
            elif kruskal(n, indexed_edges, include_edge=(u, v, w, idx)) == original_mst_weight:
                pseudo_critical_edges.append(idx)

        return [critical_edges, pseudo_critical_edges]  