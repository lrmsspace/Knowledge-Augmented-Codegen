# Source: https://leetcode.com/problems/number-of-good-paths/   |   Difficulty: Hard
#
# Problem Description:
# There is a tree (i.e. a connected, undirected graph with no cycles) consisting of n nodes numbered from 0 to n - 1 and exactly n - 1 edges.
#
# You are given a 0-indexed integer array vals of length n where vals[i] denotes the value of the ith node. You are also given a 2D integer array edges where edges[i] = [ai, bi] denotes that there exists an undirected edge connecting nodes ai and bi.
#
# A good path is a simple path that satisfies the following conditions:
#
#
# 	The starting node and the ending node have the same value.
# 	All nodes between the starting node and the ending node have values less than or equal to the starting node (i.e. the starting node's value should be the maximum value along the path).
#
#
# Return the number of distinct good paths.
#
# Note that a path and its reverse are counted as the same path. For example, 0 -> 1 is considered to be the same as 1 -> 0. A single node is also considered as a valid path.
#
# Example:
# Input: vals = [1,3,2,1,3], edges = [[0,1],[0,2],[2,3],[2,4]]
# Output: 6
# Explanation: There are 5 good paths consisting of a single node.
# There is 1 additional good path: 1 -> 0 -> 2 -> 4.
# (The reverse path 4 -> 2 -> 0 -> 1 is treated as the same as 1 -> 0 -> 2 -> 4.)
# Note that 0 -> 2 -> 3 is not a good path because vals[2] > vals[0].
#
# Constraints:
# n == vals.length
# 	1 <= n <= 3 * 104
# 	0 <= vals[i] <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	edges represents a valid tree.
#
# Helpful references (internal KB):
# - Disjoint Set Union (ds, tree, array, union-find)
#   • When to use: Use when you need to maintain a collection of disjoint sets and efficiently perform union operations to merge sets or find the representative of an element's set.
#   • Idea: Disjoint Set Union (DSU) is a data structure that stores a collection of disjoint sets and supports two primary operations: finding the representative of an element's set and merging two sets. With path compression and union by rank/size, these operations achieve nearly constant amortized time complexity, O(alpha(N)).
#   • Invariants: Each element `v` is either a root (parent[v] == v) or has a parent pointer to another element in its set.; The `find_set` operation, after path compression, ensures that all nodes on the path from `v` to its root directly point to the root.
#   • Tips: Implement path compression in `find_set` for optimal performance.; Use union by rank or union by size to keep trees flat and balanced.
#   • Pitfalls: Forgetting path compression or union by rank/size leads to O(N) worst-case operations.; Incorrectly merging sets by only updating one root without considering the other's rank/size.
# - Minimum spanning tree - Kruskal with Disjoint Set Union (graph, ds, mst-kruskal, union-find)
#   • When to use: Use when you need to find a minimum spanning tree in a graph, especially when the graph is sparse or the number of edges is not excessively large compared to vertices.
#   • Idea: Sorts all graph edges by weight and iteratively adds the cheapest edge that connects two previously disconnected components using a Disjoint Set Union (DSU) data structure. This process builds an MST with O(M log M) or O(M log N) time complexity.
#   • Invariants: After processing k edges, the chosen edges form a forest where each tree is a component of the MST.; Any edge not yet processed has a weight greater than or equal to all processed edges.
#   • Tips: Sort edges by weight in non-decreasing order.; Initialize DSU such that each vertex is in its own set.
#   • Pitfalls: Forgetting to sort edges, leading to an incorrect MST.; Inefficient DSU implementation without path compression or union by rank/size.
# - Finding Bridges Online (graph, ds, union-find, counting)
#   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
#   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
#   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
#   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
#   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfGoodPaths(self, vals, edges):
        """
        :type vals: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        n = len(vals)
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        # Group nodes by their values
        value_to_nodes = defaultdict(list)
        for i, val in enumerate(vals):
            value_to_nodes[val].append(i)

        # Disjoint Set Union (DSU) implementation
        parent = list(range(n))
        size = [1] * n

        def find_set(v):
            if parent[v] != v:
                parent[v] = find_set(parent[v])  # Path compression
            return parent[v]

        def union_sets(a, b):
            a = find_set(a)
            b = find_set(b)
            if a != b:
                if size[a] < size[b]:
                    a, b = b, a
                parent[b] = a
                size[a] += size[b]

        good_paths_count = 0

        # Process nodes in order of their values
        for val in sorted(value_to_nodes.keys()):
            nodes = value_to_nodes[val]

            # For each node with the current value, union it with its neighbors if they have values <= current value
            for node in nodes:
                for neighbor in graph[node]:
                    if vals[neighbor] <= val:
                        union_sets(node, neighbor)

            # Count the number of nodes in each connected component that have the current value
            component_count = defaultdict(int)
            for node in nodes:
                root = find_set(node)
                component_count[root] += 1

            # For each component with k nodes of the current value, we can choose any two to form a good path
            for count in component_count.values():
                good_paths_count += count * (count - 1) // 2  # Combination of 2 from count

        return good_paths_count + n  # Add n for single-node paths