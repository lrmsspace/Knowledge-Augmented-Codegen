# Source: https://leetcode.com/problems/add-edges-to-make-degrees-of-all-nodes-even/   |   Difficulty: Hard
#
# Problem Description:
# There is an undirected graph consisting of n nodes numbered from 1 to n. You are given the integer n and a 2D array edges where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi. The graph can be disconnected.
#
# You can add at most two additional edges (possibly none) to this graph so that there are no repeated edges and no self-loops.
#
# Return true if it is possible to make the degree of each node in the graph even, otherwise return false.
#
# The degree of a node is the number of edges connected to it.
#
# Example:
# Input: n = 5, edges = [[1,2],[2,3],[3,4],[4,2],[1,4],[2,5]]
# Output: true
# Explanation: The above diagram shows a valid way of adding an edge.
# Every node in the resulting graph is connected to an even number of edges.
#
# Constraints:
# 3 <= n <= 105
# 	2 <= edges.length <= 105
# 	edges[i].length == 2
# 	1 <= ai, bi <= n
# 	ai != bi
# 	There are no repeated edges.
#
# Helpful references (internal KB):
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Finding Bridges Online (graph, ds, union-find, counting)
#   • When to use: Use when edges are added one by one to an initially empty graph and you need to efficiently track the number of bridges or 2-edge-connected components after each addition.
#   • Idea: This algorithm dynamically maintains the number of bridges in an undirected graph as edges are added incrementally. It leverages a Disjoint Set Union (DSU) data structure to achieve an amortized time complexity of O((N+M) log N).
#   • Invariants: Each DSU set represents a 2-edge-connected component or a collection of such components connected by bridges.; The total count of bridges accurately reflects edges whose removal increases connected components.
#   • Tips: Understand the properties of 2-edge-connected components and how they relate to bridges.; Carefully manage DSU operations, including path compression and union by rank/size, for optimal performance.
#   • Pitfalls: Incorrectly updating the bridge count after an edge addition, especially when cycles are formed.; Inefficient DSU operations leading to a higher than expected time complexity.
# - 2-SAT (graph, scc)
#   • When to use: When a problem can be modeled as finding a satisfying assignment for a Boolean formula where each clause contains exactly two literals. It is used to determine if such an assignment exists and to construct one if it does.
#   • Idea: 2-SAT solves the Boolean satisfiability problem for formulas in conjunctive normal form where each clause has exactly two literals. It converts the formula into an implication graph and uses Strongly Connected Components (SCCs) to find a satisfying assignment or determine unsatisfiability in O(N+M) time.
#   • Invariants: Each clause (A OR B) is correctly represented by two implications: (NOT A => B) and (NOT B => A).; The implication graph correctly reflects all logical implications derived from the 2-CNF formula.
#   • Tips: Convert each clause (A OR B) into two implications: (NOT A => B) and (NOT B => A).; Represent each variable X and its negation NOT X as distinct nodes in the implication graph.
#   • Pitfalls: Incorrectly converting clauses to implications, missing one of the two directions.; Failing to handle the critical case where a variable and its negation are in the same SCC.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isPossible(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: bool
        """
        from collections import defaultdict

        # Step 1: Build the graph and calculate degrees
        graph = defaultdict(set)
        degree = [0] * n

        for u, v in edges:
            graph[u - 1].add(v - 1)
            graph[v - 1].add(u - 1)
            degree[u - 1] += 1
            degree[v - 1] += 1

        # Step 2: Identify nodes with odd degree
        odd_degree_nodes = [i for i in range(n) if degree[i] % 2 != 0]

        # Step 3: Handle cases based on the number of odd degree nodes
        if len(odd_degree_nodes) == 0:
            return True
        elif len(odd_degree_nodes) == 2:
            u, v = odd_degree_nodes
            # Check if we can connect u and v directly or through an intermediate node
            if v not in graph[u]:  # Direct connection possible
                return True
            else:  # Check for an intermediate node w that can connect to both u and v
                for w in range(n):
                    if w != u and w != v and w not in graph[u] and w not in graph[v]:
                        return True
                return False
        elif len(odd_degree_nodes) == 4:
            # Check if we can pair the odd degree nodes without creating duplicates
            pairs = [(odd_degree_nodes[i], odd_degree_nodes[j]) for i in range(4) for j in range(i + 1, 4)]
            valid_pairs = []
            for u, v in pairs:
                if v not in graph[u]:  # Valid pair without duplicate edge
                    valid_pairs.append((u, v))
            # We need at least two valid pairs to connect all four odd nodes
            return len(valid_pairs) >= 2
        else:
            return False