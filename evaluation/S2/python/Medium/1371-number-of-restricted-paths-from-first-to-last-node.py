# Source: https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected weighted connected graph. You are given a positive integer n which denotes that the graph has n nodes labeled from 1 to n, and an array edges where each edges[i] = [ui, vi, weighti] denotes that there is an edge between nodes ui and vi with weight equal to weighti.
#
# A path from node start to node end is a sequence of nodes [z0, z1, z2, ..., zk] such that z0 = start and zk = end and there is an edge between zi and zi+1 where 0 <= i <= k-1.
#
# The distance of a path is the sum of the weights on the edges of the path. Let distanceToLastNode(x) denote the shortest distance of a path between node n and node x. A restricted path is a path that also satisfies that distanceToLastNode(zi) > distanceToLastNode(zi+1) where 0 <= i <= k-1.
#
# Return the number of restricted paths from node 1 to node n. Since that number may be too large, return it modulo 109 + 7.
#
# Example:
# Input: n = 5, edges = [[1,2,3],[1,3,3],[2,3,1],[1,4,2],[5,2,2],[3,5,1],[5,4,10]]
# Output: 3
# Explanation: Each circle contains the node number in black and its distanceToLastNode value in blue. The three restricted paths are:
# 1) 1 --> 2 --> 5
# 2) 1 --> 2 --> 3 --> 5
# 3) 1 --> 3 --> 5
#
# Constraints:
# 1 <= n <= 2 * 104
# 	n - 1 <= edges.length <= 4 * 104
# 	edges[i].length == 3
# 	1 <= ui, vi <= n
# 	ui != vi
# 	1 <= weighti <= 105
# 	There is at most one edge between any two nodes.
# 	There is at least one path between any two nodes.
#
# Helpful references (internal KB):
# - Second Best Minimum Spanning Tree (graph, tree, mst-kruskal, lca, binary-lifting, enumeration)
#   • When to use: When you need to find a spanning tree with the second smallest total edge weight, typically after finding the primary Minimum Spanning Tree.
#   • Idea: This algorithm finds the second best Minimum Spanning Tree by iterating through non-MST edges, adding each to the MST to form a cycle, and then removing the maximum weight edge on that cycle (excluding the added edge). It leverages Kruskal's for the initial MST and LCA with binary lifting for efficient path maximum queries, achieving an overall time complexity of O(E log E + E log V).
#   • Invariants: The initial MST is always a valid spanning tree with minimum total weight.; For any non-MST edge (u, v) added, a unique cycle is formed in the current graph.
#   • Tips: Precompute LCA and maximum edge weights on paths using binary lifting for efficiency.; The initial MST can be found using Kruskal's or Prim's algorithm.
#   • Pitfalls: Incorrectly identifying the maximum weight edge on the cycle when adding a non-MST edge.; Forgetting to exclude the newly added edge itself when finding the maximum edge on the cycle.
# - Shortest Paths (graph, topo, dp-1d)
#   • When to use: This algorithm finds the shortest paths from a single source vertex to all other vertices in a directed acyclic graph (DAG) with arbitrary edge weights.
#   • Idea: This algorithm computes single-source shortest paths in a Directed Acyclic Graph (DAG) by processing vertices in topological order, relaxing outgoing edges. It achieves a time complexity of O(V + E).
#   • Invariants: The distance to the source vertex, distTo[s], remains 0 throughout the algorithm.; For any vertex v, distTo[v] always stores the shortest path found so far from s to v.
#   • Tips: First, perform a topological sort on the DAG to determine the processing order.; Initialize all distances to infinity, except the source vertex which is zero.
#   • Pitfalls: Applying this algorithm to a graph containing cycles will yield incorrect results.; An incorrect topological sort order will lead to incorrect shortest path calculations.
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
    def countRestrictedPaths(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        import heapq
        from collections import defaultdict

        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        # Step 1: Dijkstra's to find shortest distance from node n to all nodes
        dist = {i: float('inf') for i in range(1, n + 1)}
        dist[n] = 0
        min_heap = [(0, n)]
        
        while min_heap:
            d, node = heapq.heappop(min_heap)
            if d > dist[node]:
                continue
            for neighbor, weight in graph[node]:
                new_dist = d + weight
                if new_dist < dist[neighbor]:
                    dist[neighbor] = new_dist
                    heapq.heappush(min_heap, (new_dist, neighbor))

        # Step 2: DFS with memoization to count restricted paths from node 1 to node n
        memo = {}

        def dfs(node):
            if node == n:
                return 1
            if node in memo:
                return memo[node]
            total_paths = 0
            for neighbor, _ in graph[node]:
                if dist[node] > dist[neighbor]:  # Check the restricted path condition
                    total_paths += dfs(neighbor)
                    total_paths %= (10**9 + 7)  # Modulo to prevent overflow
            memo[node] = total_paths
            return total_paths

        return dfs(1)