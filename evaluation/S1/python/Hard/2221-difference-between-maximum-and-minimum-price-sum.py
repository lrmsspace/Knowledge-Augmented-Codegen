# Source: https://leetcode.com/problems/difference-between-maximum-and-minimum-price-sum/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected and initially unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
#
# The price sum of a given path is the sum of the prices of all nodes lying on that path.
#
# The tree can be rooted at any node root of your choice. The incurred cost after choosing root is the difference between the maximum and minimum price sum amongst all paths starting at root.
#
# Return the maximum possible cost amongst all possible root choices.
#
# Example:
# Input: n = 6, edges = [[0,1],[1,2],[1,3],[3,4],[3,5]], price = [9,8,7,6,10,5]
# Output: 24
# Explanation: The diagram above denotes the tree after rooting it at node 2. The first part (colored in red) shows the path with the maximum price sum. The second part (colored in blue) shows the path with the minimum price sum.
# - The first path contains nodes [2,1,3,4]: the prices are [7,8,6,10], and the sum of the prices is 31.
# - The second path contains the node [2] with the price [7].
# The difference between the maximum and minimum price sum is 24. It can be proved that 24 is the maximum cost.
#
# Constraints:
# 1 <= n <= 105
# 	edges.length == n - 1
# 	0 <= ai, bi <= n - 1
# 	edges represents a valid tree.
# 	price.length == n
# 	1 <= price[i] <= 105
#
# Helpful references (internal KB):
# - Depth First Search (tree, graph, dfs)
#   • When to use: Use DFS to explore all reachable nodes from a starting point, find paths, or traverse tree-like structures. It's suitable for problems requiring exhaustive search or connectivity checks.
#   • Idea: Depth First Search is a graph traversal algorithm that explores as far as possible along each branch before backtracking. It typically uses a stack (explicit or implicit via recursion) and has a time complexity of O(V + E) for graphs and O(V) for trees.
#   • Invariants: All nodes reachable from the starting node are eventually visited.; The visited set/array accurately tracks all nodes currently in the recursion stack or already fully explored.
#   • Tips: Use a visited set or array to prevent cycles and redundant work.; Recursion is often the most natural way to implement DFS.
#   • Pitfalls: Stack overflow can occur with deep recursion on very large graphs.; Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Minimum spanning tree - Prim's algorithm (graph, mst-prim, greedy)
#   • When to use: Use Prim's algorithm to find a minimum spanning tree in a connected, undirected, weighted graph. It is often preferred for dense graphs due to its O(V^2) or O(E log V) complexity.
#   • Idea: Prim's algorithm is a greedy algorithm that builds a minimum spanning tree by iteratively adding the cheapest edge connecting a vertex in the growing tree to one outside it. It typically runs in O(E log V) time with a binary heap or O(V^2) with an adjacency matrix.
#   • Invariants: The set of vertices already included in the MST forms a connected component.; For any vertex not yet in the MST, its associated key/distance stores the minimum weight of an edge connecting it to a vertex already in the MST.
#   • Tips: Use a priority queue to efficiently retrieve the minimum weight edge connecting to the MST.; Initialize distances for all vertices to infinity, except the starting vertex (0).
#   • Pitfalls: Not suitable for disconnected graphs; it will only find an MST for the component of the starting vertex.; Forgetting to handle edge cases like graphs with no edges or a single vertex.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def maxOutput(self, n, edges, price):
        """
        :type n: int
        :type edges: List[List[int]]
        :type price: List[int]
        :rtype: int
        """
        from collections import defaultdict

        graph = defaultdict(list)
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)

        max_cost = 0

        def dfs(node, parent):
            nonlocal max_cost
            max_path_sum = price[node]

            for neighbor in graph[node]:
                if neighbor == parent:
                    continue
                child_max_sum = dfs(neighbor, node)
                max_cost = max(max_cost, max_path_sum + child_max_sum - price[node])
                max_path_sum = max(max_path_sum, price[node] + child_max_sum)

            return max_path_sum

        dfs(0, -1)
        return max_cost