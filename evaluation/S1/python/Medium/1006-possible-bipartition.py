# Source: https://leetcode.com/problems/possible-bipartition/   |   Difficulty: Medium
#
# Problem Description:
# We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.
#
# Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.
#
# Example:
# Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
# Output: true
# Explanation: The first group has [1,4], and the second group has [2,3].
#
# Constraints:
# 1 <= n <= 2000
# 	0 <= dislikes.length <= 104
# 	dislikes[i].length == 2
# 	1 <= ai < bi <= n
# 	All the pairs of dislikes are unique.
#
# Helpful references (internal KB):
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Finding articulation points in a graph in O(N+M) (graph, array, dfs)
#   • When to use: Use when identifying critical nodes whose removal would increase the number of connected components in an undirected graph. It's essential for analyzing network robustness and vulnerability.
#   • Idea: This algorithm finds all articulation points (cut vertices) in an undirected graph using a single Depth First Search traversal. It operates in linear time, O(N+M), where N is vertices and M is edges.
#   • Invariants: For any node `u`, `tin[u]` is its discovery time, and `low[u]` is initialized to `tin[u]`.; After visiting all children `v` of `u` (and their subtrees), `low[u]` will hold the minimum `tin` value reachable from `u` or its descendants via tree edges and at most one back-edge.
#   • Tips: Initialize `tin` (discovery time) and `low` (lowest reachable ancestor) arrays for all vertices.; The root of the DFS tree is an articulation point if it has more than one child in the DFS tree.
#   • Pitfalls: Forgetting to initialize `low[u]` with `tin[u]` before processing children.; Incorrectly applying the `tin[u] <= low[v]` condition to the root node of the DFS tree.
# - 2-SAT (graph, scc, topo)
#   • When to use: Use when solving problems involving boolean variables constrained by implications of the form (A OR B). It determines if a satisfying assignment exists and can construct one if it does.
#   • Idea: 2-SAT solves boolean satisfiability problems where each clause has exactly two literals, by transforming them into an implication graph. It checks for contradictions using Strongly Connected Components (SCCs) and finds a valid assignment in O(N+M) time.
#   • Invariants: For any variable X, X and its negation NOT X must belong to different SCCs for a solution to exist.; If an implication A => B is present, then the contrapositive NOT B => NOT A must also be present in the graph.
#   • Tips: Construct an implication graph where A => B means NOT A OR B.; For each clause (A OR B), add edges (NOT A => B) and (NOT B => A).
#   • Pitfalls: Forgetting to add both implication edges for each clause.; Incorrectly handling the negation of variables in graph construction.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def possibleBipartition(self, n, dislikes):
        """
        :type n: int
        :type dislikes: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for a, b in dislikes:
            graph[a].append(b)
            graph[b].append(a)

        color = {}

        def bfs(start):
            queue = deque([start])
            color[start] = 0

            while queue:
                node = queue.popleft()
                for neighbor in graph[node]:
                    if neighbor not in color:
                        color[neighbor] = 1 - color[node]
                        queue.append(neighbor)
                    elif color[neighbor] == color[node]:
                        return False
            return True

        for person in range(1, n + 1):
            if person not in color:
                if not bfs(person):
                    return False

        return True