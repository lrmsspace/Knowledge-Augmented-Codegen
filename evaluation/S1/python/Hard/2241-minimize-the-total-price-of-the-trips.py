# Source: https://leetcode.com/problems/minimize-the-total-price-of-the-trips/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
#
# Each node has an associated price. You are given an integer array price, where price[i] is the price of the ith node.
#
# The price sum of a given path is the sum of the prices of all nodes lying on that path.
#
# Additionally, you are given a 2D integer array trips, where trips[i] = [starti, endi] indicates that you start the ith trip from the node starti and travel to the node endi by any path you like.
#
# Before performing your first trip, you can choose some non-adjacent nodes and halve the prices.
#
# Return the minimum total price sum to perform all the given trips.
#
# Example:
# Input: n = 4, edges = [[0,1],[1,2],[1,3]], price = [2,2,10,6], trips = [[0,3],[2,1],[2,3]]
# Output: 23
# Explanation: The diagram above denotes the tree after rooting it at node 2. The first part shows the initial tree and the second part shows the tree after choosing nodes 0, 2, and 3, and making their price half.
# For the 1st trip, we choose path [0,1,3]. The price sum of that path is 1 + 2 + 3 = 6.
# For the 2nd trip, we choose path [2,1]. The price sum of that path is 2 + 5 = 7.
# For the 3rd trip, we choose path [2,1,3]. The price sum of that path is 5 + 2 + 3 = 10.
# The total price sum of all trips is 6 + 7 + 10 = 23.
# It can be proven, that 23 is the minimum answer that we can achieve.
#
# Constraints:
# 1 <= n <= 50
# 	edges.length == n - 1
# 	0 <= ai, bi <= n - 1
# 	edges represents a valid tree.
# 	price.length == n
# 	price[i] is an even integer.
# 	1 <= price[i] <= 1000
# 	1 <= trips.length <= 100
# 	0 <= starti, endi <= n - 1
#
# Helpful references (internal KB):
# - Lowest Common Ancestor - Binary Lifting (tree, array, dfs, binary-lifting)
#   • When to use: When you need to find the lowest common ancestor of multiple pairs of nodes in a static tree efficiently. It's suitable for scenarios requiring fast query times after initial preprocessing.
#   • Idea: Binary lifting precomputes ancestors at powers of two distances for each node, enabling O(log N) LCA queries after O(N log N) preprocessing. It finds the LCA by lifting nodes to the same depth and then simultaneously upwards.
#   • Invariants: `up[u][j]` stores the `2^j`-th ancestor of node `u`.; For any node `u`, `depth[u]` is its distance from the root.
#   • Tips: Precompute depths of all nodes using DFS from the root.; Initialize `up[u][0]` as the direct parent of `u` for all nodes.
#   • Pitfalls: Incorrectly handling the root's parent or depth calculation.; Off-by-one errors in `logN` calculation for array dimensions.
# - interval-dp (array, interval-dp, prefix-sum)
#   • When to use: Use when finding an optimal value (min/max) for operations on contiguous subarrays or segments, especially when subproblems are defined by intervals and can be combined from smaller adjacent intervals. Useful for problems involving circular arrangements by duplicating the array.
#   • Idea: Interval DP is a dynamic programming technique that solves problems by breaking them into subproblems defined over contiguous intervals. It typically computes solutions for smaller intervals first, then uses these to build solutions for larger intervals, often with an O(N^3) time complexity.
#   • Invariants: For any `len`, `dp[l][r]` for `r - l + 1 < len` are already computed.; `dp[l][r]` represents the optimal cost for the operation on the range `[l, r]`.
#   • Tips: Define dp[i][j] as the optimal solution for the interval [i, j].; Iterate by interval length first, then by start index.
#   • Pitfalls: Incorrectly defining base cases for intervals of length 1.; Off-by-one errors in interval boundaries or split points.
# - Directed Graphs (graph, matrix, dfs)
#   • When to use: Use when needing to determine reachability between all pairs of vertices in a directed graph, especially for small or dense graphs where O(V*(V+E)) time is acceptable.
#   • Idea: This approach determines all-pairs reachability in a directed graph by performing a Depth-First Search starting from each vertex. It has a time complexity of O(V*(V+E)) and a space complexity of O(V^2).
#   • Invariants: For any vertex u, after its dedicated DFS completes, TC[u][v] is true for all v reachable from u.; The transitive closure matrix TC accurately reflects all-pairs reachability in the original graph.
#   • Tips: Initialize a boolean matrix to store reachability results.; For each vertex, perform a full DFS to mark all nodes reachable from it.
#   • Pitfalls: High time complexity O(V*(V+E)) makes it unsuitable for large sparse graphs.; High space complexity O(V^2) can be prohibitive for graphs with many vertices.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumTotalPrice(self, n, edges, price, trips):
        """
        :type n: int
        :type edges: List[List[int]]
        :type price: List[int]
        :type trips: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict

        # Build the tree as an adjacency list
        tree = defaultdict(list)
        for u, v in edges:
            tree[u].append(v)
            tree[v].append(u)

        # Count how many times each node is visited across all trips
        visit_count = [0] * n

        def dfs(node, parent, target):
            if node == target:
                visit_count[node] += 1
                return True
            for neighbor in tree[node]:
                if neighbor != parent:
                    if dfs(neighbor, node, target):
                        visit_count[node] += 1
                        return True
            return False

        # For each trip, perform a DFS to count visits
        for start, end in trips:
            dfs(start, -1, end)

        # Calculate the total price with and without halving
        total_price = 0
        for i in range(n):
            if visit_count[i] > 0:
                total_price += price[i] * visit_count[i]

        # Try halving the price of non-adjacent nodes to minimize total price
        def can_halve(node, parent):
            for neighbor in tree[node]:
                if neighbor != parent and visit_count[neighbor] > 0:
                    return False
            return True

        for i in range(n):
            if visit_count[i] > 0 and can_halve(i, -1):
                total_price -= (price[i] // 2) * visit_count[i]

        return total_price