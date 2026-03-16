# Source: https://leetcode.com/problems/evaluate-division/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of variable pairs equations and an array of real numbers values, where equations[i] = [Ai, Bi] and values[i] represent the equation Ai / Bi = values[i]. Each Ai or Bi is a string that represents a single variable.
#
# You are also given some queries, where queries[j] = [Cj, Dj] represents the jth query where you must find the answer for Cj / Dj = ?.
#
# Return the answers to all queries. If a single answer cannot be determined, return -1.0.
#
# Note: The input is always valid. You may assume that evaluating the queries will not result in division by zero and that there is no contradiction.
#
# Note: The variables that do not occur in the list of equations are undefined, so the answer cannot be determined for them.
#
# Example:
# Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
# Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
# Explanation: 
# Given: a / b = 2.0, b / c = 3.0
# queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ? 
# return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
# note: x is undefined => -1.0
#
# Constraints:
# 1 <= equations.length <= 20
# 	equations[i].length == 2
# 	1 <= Ai.length, Bi.length <= 5
# 	values.length == equations.length
# 	0.0 < values[i] <= 20.0
# 	1 <= queries.length <= 20
# 	queries[i].length == 2
# 	1 <= Cj.length, Dj.length <= 5
# 	Ai, Bi, Cj, Dj consist of lower case English letters and digits.
#
# Helpful references (internal KB):
# - Strongly connected components and the condensation graph (graph, enumeration)
#   • When to use: When you need to identify maximal subgraphs where all vertices are mutually reachable, or to simplify a directed graph into a Directed Acyclic Graph (DAG) of components for further processing.
#   • Idea: This concept defines SCCs as maximal vertex subsets in a directed graph where all pairs are mutually reachable. It also introduces the condensation graph, which represents SCCs as nodes and forms a DAG, typically found in O(V+E) time.
#   • Invariants: Every vertex belongs to exactly one strongly connected component.; Within any SCC, a path exists from any vertex u to any other vertex v, and vice-versa.
#   • Tips: Understand that SCCs partition the graph's vertices.; The condensation graph is always a Directed Acyclic Graph (DAG).
#   • Pitfalls: Confusing SCCs with simple cycles or connected components in undirected graphs.; Incorrectly assuming the condensation graph has cycles.
# - Strongly connected components and the condensation graph (graph, array, dfs, enumeration)
#   • When to use: Use this when systematically exploring all possible configurations, paths, or subsets within a graph or array. It's ideal for finding every solution or verifying properties across all potential states.
#   • Idea: Depth-First Search (DFS) is a graph traversal algorithm that explores as far as possible along each branch before backtracking. When combined with enumeration, it systematically generates all possible combinations or paths, typically with exponential time complexity O(V+E) for traversal or O(N!) / O(2^N) for enumeration.
#   • Invariants: The current path/subset being built is valid up to the current depth.; All previously explored branches from the current node have been fully processed.
#   • Tips: Define clear base cases for recursion termination.; Manage state changes carefully when entering and exiting recursive calls.
#   • Pitfalls: Infinite recursion due to missing or incorrect base cases.; Redundant computations if states are not properly managed or memoized.
# - Directed Graphs (graph, array, dfs, bfs)
#   • When to use: Use when modeling relationships with a specific flow direction between entities. It is ideal for determining reachability or finding paths from one or more sources.
#   • Idea: Directed graphs represent connections where edges have a specific direction, often implemented using adjacency lists. Depth-first search (DFS) and breadth-first search (BFS) are fundamental algorithms for traversing these graphs to find paths and determine reachability in O(V+E) time.
#   • Invariants: The 'visited' set accurately reflects all nodes for which traversal has been initiated.; For DFS, all nodes reachable from the current node via unvisited paths will eventually be explored.
#   • Tips: Always use a 'visited' set or array to prevent infinite loops in cycles and redundant processing.; Adjacency list representation is generally preferred for sparse graphs due to better space and time complexity for traversal.
#   • Pitfalls: Forgetting to handle cycles can lead to infinite loops or stack overflows in DFS.; Incorrectly applying algorithms designed for undirected graphs to directed graphs without modification.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def calcEquation(self, equations, values, queries):
        """
        :type equations: List[List[str]]
        :type values: List[float]
        :type queries: List[List[str]]
        :rtype: List[float]
        """
        from collections import defaultdict

        # Build the graph
        graph = defaultdict(list)
        for (A, B), value in zip(equations, values):
            graph[A].append((B, value))
            graph[B].append((A, 1 / value))

        def dfs(start, end, visited):
            if start not in graph or end not in graph:
                return -1.0
            if start == end:
                return 1.0

            visited.add(start)
            for neighbor, weight in graph[start]:
                if neighbor not in visited:
                    result = dfs(neighbor, end, visited)
                    if result != -1.0:
                        return weight * result
            visited.remove(start)
            return -1.0

        results = []
        for C, D in queries:
            visited = set()
            results.append(dfs(C, D, visited))

        return results