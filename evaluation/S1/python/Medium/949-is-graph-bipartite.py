# Source: https://leetcode.com/problems/is-graph-bipartite/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected graph with n nodes, where each node is numbered between 0 and n - 1. You are given a 2D array graph, where graph[u] is an array of nodes that node u is adjacent to. More formally, for each v in graph[u], there is an undirected edge between node u and node v. The graph has the following properties:
#
#
# 	There are no self-edges (graph[u] does not contain u).
# 	There are no parallel edges (graph[u] does not contain duplicate values).
# 	If v is in graph[u], then u is in graph[v] (the graph is undirected).
# 	The graph may not be connected, meaning there may be two nodes u and v such that there is no path between them.
#
#
# A graph is bipartite if the nodes can be partitioned into two independent sets A and B such that every edge in the graph connects a node in set A and a node in set B.
#
# Return true if and only if it is bipartite.
#
# Example:
# Input: graph = [[1,2,3],[0,2],[0,1,3],[0,2]]
# Output: false
# Explanation: There is no way to partition the nodes into two independent sets such that every edge connects a node in one and a node in the other.
#
# Constraints:
# graph.length == n
# 	1 <= n <= 100
# 	0 <= graph[u].length < n
# 	0 <= graph[u][i] <= n - 1
# 	graph[u] does not contain u.
# 	All the values of graph[u] are unique.
# 	If graph[u] contains v, then graph[v] contains u.
#
# Helpful references (internal KB):
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Search for connected components in a graph (graph, dfs, bfs, enumeration)
#   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
#   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
#   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
#   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
#   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
# - 0-1 BFS (graph, deque, 01-bfs, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
#   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
#   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
#   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
#   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isBipartite(self, graph):
        """
        :type graph: List[List[int]]
        :rtype: bool
        """
        n = len(graph)
        color = [-1] * n  # -1: uncolored, 0: color A, 1: color B

        for start in range(n):
            if color[start] == -1:  # Not yet colored
                queue = [start]
                color[start] = 0  # Start coloring with color A

                while queue:
                    node = queue.pop(0)
                    for neighbor in graph[node]:
                        if color[neighbor] == -1:  # If uncolored, color with opposite color
                            color[neighbor] = 1 - color[node]
                            queue.append(neighbor)
                        elif color[neighbor] == color[node]:  # Conflict in coloring
                            return False
        return True