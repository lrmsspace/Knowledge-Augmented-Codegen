# Source: https://leetcode.com/problems/collect-coins-in-a-tree/   |   Difficulty: Hard
#
# Problem Description:
# There exists an undirected and unrooted tree with n nodes indexed from 0 to n - 1. You are given an integer n and a 2D integer array edges of length n - 1, where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree. You are also given an array coins of size n where coins[i] can be either 0 or 1, where 1 indicates the presence of a coin in the vertex i.
#
# Initially, you choose to start at any vertex in the tree. Then, you can perform the following operations any number of times: 
#
#
#  Collect all the coins that are at a distance of at most 2 from the current vertex, or
#  Move to any adjacent vertex in the tree.
#
#
# Find the minimum number of edges you need to go through to collect all the coins and go back to the initial vertex.
#
# Note that if you pass an edge several times, you need to count it into the answer several times.
#
# Example:
# Input: coins = [1,0,0,0,0,1], edges = [[0,1],[1,2],[2,3],[3,4],[4,5]]
# Output: 2
# Explanation: Start at vertex 2, collect the coin at vertex 0, move to vertex 3, collect the coin at vertex 5 then move back to vertex 2.
#
# Constraints:
# n == coins.length
#  1 <= n <= 3 * 104
#  0 <= coins[i] <= 1
#  edges.length == n - 1
#  edges[i].length == 2
#  0 <= ai, bi < n
#  ai != bi
#  edges represents a valid tree.
#
# Helpful references (internal KB):
# - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
#   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
#   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
#   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
#   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
#   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
# - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
#   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
#   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
#   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
#   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
#   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def collectTheCoins(self, coins, edges):
        """
        :type coins: List[int]
        :type edges: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        n = len(coins)
        graph = defaultdict(list)
        degree = [0] * n

        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
            degree[u] += 1
            degree[v] += 1

        # Step 1: Remove leaf nodes without coins
        queue = deque()
        for i in range(n):
            if degree[i] == 1 and coins[i] == 0:
                queue.append(i)

        while queue:
            node = queue.popleft()
            degree[node] -= 1
            for neighbor in graph[node]:
                degree[neighbor] -= 1
                if degree[neighbor] == 1 and coins[neighbor] == 0:
                    queue.append(neighbor)

        # Step 2: Remove leaf nodes with coins (up to 2 layers)
        for _ in range(2):
            new_queue = deque()
            for i in range(n):
                if degree[i] == 1 and coins[i] == 1:
                    new_queue.append(i)

            while new_queue:
                node = new_queue.popleft()
                degree[node] -= 1
                for neighbor in graph[node]:
                    degree[neighbor] -= 1

        # Step 3: Count remaining edges
        remaining_edges = sum(degree) // 2
        return remaining_edges * 2