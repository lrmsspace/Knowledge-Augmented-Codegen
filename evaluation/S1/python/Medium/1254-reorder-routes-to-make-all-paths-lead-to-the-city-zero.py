# Source: https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/   |   Difficulty: Medium
#
# Problem Description:
# There are n cities numbered from 0 to n - 1 and n - 1 roads such that there is only one way to travel between two different cities (this network form a tree). Last year, The ministry of transport decided to orient the roads in one direction because they are too narrow.
#
# Roads are represented by connections where connections[i] = [ai, bi] represents a road from city ai to city bi.
#
# This year, there will be a big event in the capital (city 0), and many people want to travel to this city.
#
# Your task consists of reorienting some roads such that each city can visit the city 0. Return the minimum number of edges changed.
#
# It's guaranteed that each city can reach city 0 after reorder.
#
# Example:
# Input: n = 6, connections = [[0,1],[1,3],[2,3],[4,0],[4,5]]
# Output: 3
# Explanation: Change the direction of edges show in red such that each node can reach the node 0 (capital).
#
# Constraints:
# 2 <= n <= 5 * 104
# 	connections.length == n - 1
# 	connections[i].length == 2
# 	0 <= ai, bi <= n - 1
# 	ai != bi
#
# Helpful references (internal KB):
# - Depth First Search (graph, dfs)
#   • When to use: Use DFS to explore all reachable vertices from a source, find connected components, or detect cycles in a graph. It is suitable for problems requiring deep exploration before backtracking.
#   • Idea: Depth First Search systematically explores a graph by going as deep as possible along each branch before backtracking. It visits each vertex and edge at most once, resulting in an O(V + E) time complexity.
#   • Invariants: Before visiting a node 'u', it is marked as unvisited.; After visiting a node 'u', it is marked as visited, and all its reachable neighbors have been explored.
#   • Tips: Use a 'visited' set or array to prevent infinite loops in cyclic graphs.; Recursion is common, but an explicit stack can manage deep graphs or avoid recursion limits.
#   • Pitfalls: Can lead to stack overflow errors on very deep graphs if implemented recursively.; Does not guarantee shortest paths in general unweighted graphs (BFS does).
# - Finding bridges in a graph in O(N+M) (graph, array, dfs)
#   • When to use: Use this algorithm when you need to identify edges whose removal would increase the number of connected components in an undirected graph. It's suitable for analyzing network robustness or critical connections.
#   • Idea: This algorithm uses Depth First Search (DFS) to find bridges in an undirected graph by tracking discovery times and the lowest reachable discovery time from a node or its descendants. It operates in linear time, O(N+M), where N is the number of vertices and M is the number of edges.
#   • Invariants: For any node `u` currently in the DFS stack, `tin[u]` is its unique discovery time.; For any node `u` and its child `v` in the DFS tree, `low[v]` represents the earliest discovery time reachable from `v`'s subtree (including `v`) using at most one back-edge.
#   • Tips: Initialize discovery times (tin) and lowest reachable times (low) arrays, along with a visited array.; Pass the parent vertex to the DFS function to avoid treating the parent edge as a back-edge.
#   • Pitfalls: Forgetting to pass the parent node or incorrectly handling the parent edge, leading to false bridge detections.; Failing to initialize `low` values correctly, especially for leaf nodes or isolated components.
# - Finding faces of a planar graph (graph, array, dfs, enumeration)
#   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
#   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
#   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
#   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
#   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minReorder(self, n, connections):
        """
        :type n: int
        :type connections: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        graph = defaultdict(list)
        for a, b in connections:
            graph[a].append((b, 1))  # original direction
            graph[b].append((a, 0))  # reverse direction

        visited = [False] * n
        self.changes = 0

        def dfs(city):
            visited[city] = True
            for neighbor, needs_change in graph[city]:
                if not visited[neighbor]:
                    self.changes += needs_change
                    dfs(neighbor)

        dfs(0)
        return self.changes