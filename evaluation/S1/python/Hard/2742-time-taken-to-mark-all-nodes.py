# Source: https://leetcode.com/problems/time-taken-to-mark-all-nodes/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected tree with n nodes numbered 0 to n - 1. You are given a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
#
# Initially, all nodes are unmarked. For each node i:
#
#
# 	If i is odd, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 1.
# 	If i is even, the node will get marked at time x if there is at least one node adjacent to it which was marked at time x - 2.
#
#
# Return an array times where times[i] is the time when all nodes get marked in the tree, if you mark node i at time t = 0.
#
# Note that the answer for each times[i] is independent, i.e. when you mark node i all other nodes are unmarked.
#
# Example:
# Input: edges = [[0,1],[0,2]]
#
# Output: [2,4,3]
#
# Explanation:
#
#
#
#
# 	For i = 0:
#
# 	
# 		Node 1 is marked at t = 1, and Node 2 at t = 2.
# 	
# 	
# 	For i = 1:
# 	
# 		Node 0 is marked at t = 2, and Node 2 at t = 4.
# 	
# 	
# 	For i = 2:
# 	
# 		Node 0 is marked at t = 2, and Node 1 at t = 3.
#
# Constraints:
# 2 <= n <= 105
# 	edges.length == n - 1
# 	edges[i].length == 2
# 	0 <= edges[i][0], edges[i][1] <= n - 1
# 	The input is generated such that edges represents a valid tree.
#
# Helpful references (internal KB):
# - Finding bridges in a graph in O(N+M) (graph, dfs)
#   • When to use: Use this algorithm to identify critical edges in an undirected graph whose removal would increase the number of connected components, effectively disconnecting parts of the graph.
#   • Idea: This algorithm finds all bridges in an undirected graph by performing a Depth First Search and tracking discovery times and lowest reachable ancestors. It operates with an optimal time complexity of O(N+M).
#   • Invariants: For any visited vertex u, disc[u] stores its discovery time in the DFS tree.; For any visited vertex u, low[u] stores the minimum discovery time reachable from u (including u) through u's subtree and at most one back-edge.
#   • Tips: Maintain discovery times (disc) and low-link values (low) for each vertex during DFS.; Initialize low[u] = disc[u] when first visiting vertex u.
#   • Pitfalls: Forgetting to mark visited nodes can lead to infinite loops or incorrect low-link values.; Incorrectly handling the parent edge during DFS, treating it as a back-edge.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
#   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
#   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
#   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
#   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
#   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def timeTaken(self, edges):
        """
        :type edges: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict, deque

        n = len(edges) + 1
        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        def bfs(start):
            visited = [False] * n
            queue = deque([(start, 0)])  # (node, time)
            visited[start] = True
            max_time = 0

            while queue:
                node, time = queue.popleft()
                max_time = max(max_time, time)

                for neighbor in graph[node]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        if neighbor % 2 == 0:  # even
                            queue.append((neighbor, time + 2))
                        else:  # odd
                            queue.append((neighbor, time + 1))

            return max_time

        result = []
        for i in range(n):
            result.append(bfs(i))

        return result