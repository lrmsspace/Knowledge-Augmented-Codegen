# Source: https://leetcode.com/problems/maximum-sum-of-edge-values-in-a-graph/   |   Difficulty: Hard
#
# Problem Description:
# You are given an undirected connected graph of n nodes, numbered from 0 to n - 1. Each node is connected to at most 2 other nodes.
#
# The graph consists of m edges, represented by a 2D array edges, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi.
#
# You have to assign a unique value from 1 to n to each node. The value of an edge will be the product of the values assigned to the two nodes it connects.
#
# Your score is the sum of the values of all edges in the graph.
#
# Return the maximum score you can achieve.
#
# Example:
# Input: n = 4, edges = [[0,1],[1,2],[2,3]]
#
# Output: 23
#
# Explanation:
#
# The diagram above illustrates an optimal assignment of values to nodes. The sum of the values of the edges is: (1 * 3) + (3 * 4) + (4 * 2) = 23.
#
# Constraints:
# 1 <= n <= 5 * 104
# 	m == edges.length
# 	1 <= m <= n
# 	edges[i].length == 2
# 	0 <= ai, bi < n
# 	ai != bi
# 	There are no repeated edges.
# 	The graph is connected.
# 	Each node is connected to at most 2 other nodes.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, array, stack, bfs, enumeration)
#   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
#   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
#   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
#   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
# - Finding faces of a planar graph (graph, array, dfs, enumeration)
#   • When to use: Used to identify and enumerate all faces (regions) of a given planar graph, typically when its geometric embedding is known or can be derived.
#   • Idea: This algorithm finds all faces of a planar graph by traversing edges in a specific angular order around each vertex. It achieves a time complexity of O(N log N) due to sorting, or O(N) if edges are pre-sorted.
#   • Invariants: Every directed edge is part of exactly one face boundary traversal.; At any vertex u, the next edge (u, w) is chosen such that it is immediately counter-clockwise to the incoming edge (v, u) in u's adjacency list.
#   • Tips: Sort adjacent edges by polar angle for each vertex.; Mark directed edges as visited to ensure each face is found once.
#   • Pitfalls: Errors in polar angle sorting, especially for collinear edges.; Failing to correctly mark directed edges as visited, leading to infinite loops or duplicate faces.
# - Counting labeled graphs (number, dp-2d, counting, recursion)
#   • When to use: When counting the total number of labeled graphs with a specific number of vertices and connected components. Useful for problems requiring enumeration of graph structures based on their connectivity properties.
#   • Idea: This technique uses dynamic programming to count labeled graphs with a given number of vertices and connected components by building up solutions from smaller subproblems. It leverages a recurrence relation that considers the component containing a specific vertex, leading to an O(N^2 * K) time complexity for N vertices and K components.
#   • Invariants: D[i][j] correctly stores the number of labeled graphs with i vertices and j components.; All C_s values for s < n are correctly precomputed before calculating D[n][k].
#   • Tips: Precompute binomial coefficients for efficiency.; Precompute the number of connected graphs (C_s) for all relevant s.
#   • Pitfalls: Incorrectly defining base cases for the dynamic programming table.; Off-by-one errors in binomial coefficient calculations or array indexing.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxScore(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        # Build the graph
        graph = defaultdict(list)
        degree = [0] * n
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
            degree[u] += 1
            degree[v] += 1

        # Initialize a queue for nodes with degree 1 (leaf nodes)
        queue = deque()
        for i in range(n):
            if degree[i] == 1:
                queue.append(i)

        # Assign values to nodes starting from leaf nodes
        value = [0] * n
        current_value = n
        while queue:
            node = queue.popleft()
            value[node] = current_value
            current_value -= 1

            for neighbor in graph[node]:
                degree[neighbor] -= 1
                if degree[neighbor] == 1:
                    queue.append(neighbor)

        # Calculate the score based on assigned values
        score = 0
        for u, v in edges:
            score += value[u] * value[v]

        return score