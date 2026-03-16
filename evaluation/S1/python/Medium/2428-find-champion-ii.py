# Source: https://leetcode.com/problems/find-champion-ii/   |   Difficulty: Medium
#
# Problem Description:
# There are n teams numbered from 0 to n - 1 in a tournament; each team is also a node in a DAG.
#
# You are given the integer n and a 0-indexed 2D integer array edges of length m representing the DAG, where edges[i] = [ui, vi] indicates that there is a directed edge from team ui to team vi in the graph.
#
# A directed edge from a to b in the graph means that team a is stronger than team b and team b is weaker than team a.
#
# Team a will be the champion of the tournament if there is no team b that is stronger than team a.
#
# Return the team that will be the champion of the tournament if there is a unique champion, otherwise, return -1.
#
# Notes
#
#
# 	A cycle is a series of nodes a1, a2, ..., an, an+1 such that node a1 is the same node as node an+1, the nodes a1, a2, ..., an are distinct, and there is a directed edge from the node ai to node ai+1 for every i in the range [1, n].
# 	A DAG is a directed graph that does not have any cycle.
#
# Example:
# Input: n = 3, edges = [[0,1],[1,2]]
# Output: 0
# Explanation: Team 1 is weaker than team 0. Team 2 is weaker than team 1. So the champion is team 0.
#
# Constraints:
# 1 <= n <= 100
# 	m == edges.length
# 	0 <= m <= n * (n - 1) / 2
# 	edges[i].length == 2
# 	0 <= edge[i][j] <= n - 1
# 	edges[i][0] != edges[i][1]
# 	The input is generated such that if team a is stronger than team b, team b is not stronger than team a.
# 	The input is generated such that if team a is stronger than team b and team b is stronger than team c, then team a is stronger than team c.
#
# Helpful references (internal KB):
# - Counting labeled graphs (number, recursion, counting, dp-1d)
#   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
#   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
#   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
#   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
#   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findChampion(self, n, edges):
        """
        :type n: int
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        # Build the graph and compute in-degrees
        graph = defaultdict(list)
        in_degree = [0] * n

        for u, v in edges:
            graph[u].append(v)
            in_degree[v] += 1

        # Find all nodes with in-degree 0
        zero_in_degree = [i for i in range(n) if in_degree[i] == 0]

        # If there's not exactly one node with in-degree 0, return -1
        if len(zero_in_degree) != 1:
            return -1

        champion = zero_in_degree[0]

        # Perform BFS/DFS to check reachability from the champion
        visited = [False] * n
        queue = deque([champion])
        visited[champion] = True
        reachable_count = 1

        while queue:
            node = queue.popleft()
            for neighbor in graph[node]:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    reachable_count += 1
                    queue.append(neighbor)

        # If the champion can reach all other nodes, return it; otherwise, return -1
        return champion if reachable_count == n else -1