# Source: https://leetcode.com/problems/find-weighted-median-node-in-tree/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n and an undirected, weighted tree rooted at node 0 with n nodes numbered from 0 to n - 1. This is represented by a 2D array edges of length n - 1, where edges[i] = [ui, vi, wi] indicates an edge from node ui to vi with weight wi.
#
# The weighted median node is defined as the first node x on the path from ui to vi such that the sum of edge weights from ui to x is greater than or equal to half of the total path weight.
#
# You are given a 2D integer array queries. For each queries[j] = [uj, vj], determine the weighted median node along the path from uj to vj.
#
# Return an array ans, where ans[j] is the node index of the weighted median for queries[j].
#
# Example:
# Input: n = 2, edges = [[0,1,7]], queries = [[1,0],[0,1]]
#
# Output: [0,1]
#
# Explanation:
#
#
#
#
# 	
# 		
# 			Query
# 			Path
# 			Edge
# 			Weights
# 			Total
# 			Path
# 			Weight
# 			Half
# 			Explanation
# 			Answer
# 		
# 	
# 	
# 		
# 			[1, 0]
# 			1 → 0
# 			[7]
# 			7
# 			3.5
# 			Sum from 1 → 0 = 7 >= 3.5, median is node 0.
# 			0
# 		
# 		
# 			[0, 1]
# 			0 → 1
# 			[7]
# 			7
# 			3.5
# 			Sum from 0 → 1 = 7 >= 3.5, median is node 1.
# 			1
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i] == [ui, vi, wi]
# 	0 <= ui, vi < n
# 	1 <= wi <= 109
# 	1 <= queries.length <= 105
# 	queries[j] == [uj, vj]
# 	0 <= uj, vj < n
# 	The input is generated such that edges represents a valid tree.
#
# Helpful references (internal KB):
# - Lowest Common Ancestor - Binary Lifting (tree, array, binary-lifting, dfs)
#   • When to use: Use binary lifting when you need to answer multiple Lowest Common Ancestor (LCA) queries or ancestor relationship checks efficiently on a static tree.
#   • Idea: Binary lifting precomputes ancestor pointers using DFS to answer Lowest Common Ancestor (LCA) queries and ancestor checks in O(log N) time per query, after O(N log N) preprocessing.
#   • Invariants: For any node `u` and power `k`, `up[u][k]` is the 2^k-th ancestor of `u`.; `depth[u]` correctly represents the distance from the root to node `u`.
#   • Tips: Precompute `up[u][k]` as the 2^k-th ancestor of `u`.; Use DFS to fill the `up` array and node depths.
#   • Pitfalls: Incorrectly calculating `log N` for array dimensions.; Failing to handle the root node's ancestors (e.g., `up[root][k]` should be itself or an invalid node).
# - Minimum spanning tree - Prim's algorithm (graph, mst-prim, greedy)
#   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, undirected, weighted graph. It is often preferred for dense graphs due to its O(V^2) or O(E log V) complexity.
#   • Idea: Prim's algorithm is a greedy algorithm that builds a minimum spanning tree by iteratively adding the cheapest edge connecting a vertex in the growing tree to one outside it. It typically runs in O(E log V) time with a binary heap or O(V^2) with an adjacency matrix.
#   • Invariants: The set of vertices already included in the MST forms a connected component.; For any vertex not yet in the MST, its associated key/distance stores the minimum weight of an edge connecting it to a vertex already in the MST.
#   • Tips: Use a priority queue to efficiently retrieve the minimum weight edge connecting to the MST.; Initialize distances for all vertices to infinity, except the starting vertex (0).
#   • Pitfalls: Not suitable for disconnected graphs; it will only find an MST for the component of the starting vertex.; Forgetting to handle edge cases like graphs with no edges or a single vertex.
# - Lowest Common Ancestor (tree, segment-tree)
#   • When to use: Use this approach to efficiently answer multiple Lowest Common Ancestor queries on a static tree. It is suitable when precomputation time is acceptable for faster subsequent queries.
#   • Idea: This method transforms the LCA problem into a Range Minimum Query (RMQ) problem by constructing an Euler tour of the tree. It achieves O(N log N) precomputation and O(log N) query time by building a segment tree over the depths of nodes in the Euler tour.
#   • Invariants: The Euler tour array correctly records nodes in DFS entry and exit order.; The depth array stores the depth of each node as it appears in the Euler tour.
#   • Tips: Perform a DFS to generate an Euler tour of the tree, recording nodes and their depths.; Store the first occurrence index of each node in the Euler tour array.
#   • Pitfalls: Incorrectly constructing the Euler tour or depth array, leading to wrong ranges for RMQ.; Off-by-one errors when mapping node indices to Euler tour indices or defining segment tree query ranges.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findMedian(self, n, edges, queries):
        """
        :type n: int
        :type edges: List[List[int]]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque
        import math

        # Build the tree as an adjacency list
        tree = defaultdict(list)
        for u, v, w in edges:
            tree[u].append((v, w))
            tree[v].append((u, w))

        # Precompute depth and parent for each node using BFS
        parent = [-1] * n
        depth = [0] * n
        weight_to_parent = [0] * n
        queue = deque([0])
        while queue:
            node = queue.popleft()
            for neighbor, weight in tree[node]:
                if neighbor == parent[node]:
                    continue
                parent[neighbor] = node
                depth[neighbor] = depth[node] + 1
                weight_to_parent[neighbor] = weight
                queue.append(neighbor)

        # Function to find the path and total weight between two nodes
        def find_path_and_weight(u, v):
            path_u = []
            path_v = []
            total_weight = 0

            while u != -1:
                path_u.append(u)
                if parent[u] != -1:
                    total_weight += weight_to_parent[u]
                u = parent[u]

            while v != -1:
                path_v.append(v)
                if parent[v] != -1:
                    total_weight += weight_to_parent[v]
                v = parent[v]

            return path_u[::-1], path_v[::-1], total_weight

        # Process each query to find the weighted median node
        result = []
        for u, v in queries:
            path_u, path_v, total_weight = find_path_and_weight(u, v)
            half_weight = total_weight / 2

            current_weight = 0
            median_node = None

            # Traverse the path from u to v and find the weighted median node
            for node in path_u:
                if current_weight >= half_weight:
                    median_node = node
                    break
                if parent[node] != -1:
                    current_weight += weight_to_parent[node]

            if median_node is None:  # If not found in path_u, check path_v
                for node in path_v:
                    if current_weight >= half_weight:
                        median_node = node
                        break
                    if parent[node] != -1:
                        current_weight += weight_to_parent[node]

            result.append(median_node)

        return result