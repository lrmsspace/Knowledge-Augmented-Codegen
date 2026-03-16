# Source: https://leetcode.com/problems/longest-cycle-in-a-graph/   |   Difficulty: Hard
#
# Problem Description:
# You are given a directed graph of n nodes numbered from 0 to n - 1, where each node has at most one outgoing edge.
#
# The graph is represented with a given 0-indexed array edges of size n, indicating that there is a directed edge from node i to node edges[i]. If there is no outgoing edge from node i, then edges[i] == -1.
#
# Return the length of the longest cycle in the graph. If no cycle exists, return -1.
#
# A cycle is a path that starts and ends at the same node.
#
# Example:
# Input: edges = [3,3,4,2,3]
# Output: 3
# Explanation: The longest cycle in the graph is the cycle: 2 -> 4 -> 3 -> 2.
# The length of this cycle is 3, so 3 is returned.
#
# Constraints:
# n == edges.length
# 	2 <= n <= 105
# 	-1 <= edges[i] < n
# 	edges[i] != i
#
# Helpful references (internal KB):
# - Checking a graph for acyclicity and finding a cycle in O(M) (graph, array, dfs)
#   • When to use: Use when needing to determine if a graph contains any cycles or to identify one such cycle. It is applicable to both directed and undirected graphs.
#   • Idea: This algorithm uses Depth First Search to detect cycles in a graph by tracking visited states of nodes during traversal. It runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
#   • Invariants: All nodes currently on the DFS recursion stack are marked as 'gray' (or equivalent).; All nodes fully explored and not part of the current path are marked as 'black' (or equivalent).
#   • Tips: For directed graphs, use a three-color scheme (white, gray, black) to distinguish states.; For undirected graphs, a simple visited array and checking against the immediate parent is sufficient.
#   • Pitfalls: Incorrectly handling the parent edge in undirected graphs can lead to false cycle detections.; Failing to distinguish between nodes currently in the recursion stack (gray) and fully processed nodes (black) in directed graphs.
# - Longest increasing subsequence (array, dp-1d)
#   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
#   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
#   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
#   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
#   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
# - Finding a negative cycle in the graph (graph, matrix, floyd-warshall)
#   • When to use: Use when you need to find if a negative cycle exists in a graph, especially when dealing with all-pairs shortest paths or when edge weights can be negative. It is suitable for dense graphs.
#   • Idea: The Floyd-Warshall algorithm can detect negative cycles by checking if any vertex has a negative distance to itself after all iterations. It computes all-pairs shortest paths in O(V^3) time.
#   • Invariants: After k iterations, dist[i][j] stores the shortest path from i to j using only intermediate vertices from 0 to k-1.; For any i, dist[i][i] remains 0 unless a negative cycle involving i is found.
#   • Tips: Initialize distance matrix with edge weights or infinity for non-existent edges.; Set dist[i][i] to 0 for all i initially.
#   • Pitfalls: Incorrect initialization of the distance matrix, especially dist[i][i].; Forgetting to check the main diagonal for negative values after computation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def longestCycle(self, edges):
        """
        :type edges: List[int]
        :rtype: int
        """
        n = len(edges)
        visited = [0] * n  # 0: unvisited, 1: visiting, 2: visited
        longest = -1

        for i in range(n):
            if visited[i] == 0:
                stack = []
                current = i

                while current != -1:
                    if visited[current] == 1:  # Found a cycle
                        cycle_length = len(stack) - stack.index(current)
                        longest = max(longest, cycle_length)
                        break
                    if visited[current] == 2:  # Already fully processed
                        break

                    visited[current] = 1
                    stack.append(current)
                    current = edges[current]

                for node in stack:
                    visited[node] = 2

        return longest