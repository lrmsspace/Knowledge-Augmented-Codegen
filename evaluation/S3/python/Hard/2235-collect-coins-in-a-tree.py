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
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Breadth-first search (graph, deque, array, 01-bfs)
#   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
#   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
#   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
#   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
#   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
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

        # Step 1: Remove all leaf nodes without coins
        queue = deque()
        for i in range(n):
            if degree[i] == 1 and coins[i] == 0:
                queue.append(i)

        while queue:
            node = queue.popleft()
            degree[node] -= 1
            for neighbor in graph[node]:
                if degree[neighbor] > 0:
                    degree[neighbor] -= 1
                    if degree[neighbor] == 1 and coins[neighbor] == 0:
                        queue.append(neighbor)

        # Step 2: Remove up to two layers of leaf nodes
        for _ in range(2):
            new_queue = deque()
            for i in range(n):
                if degree[i] == 1:
                    new_queue.append(i)

            while new_queue:
                node = new_queue.popleft()
                degree[node] -= 1
                for neighbor in graph[node]:
                    if degree[neighbor] > 0:
                        degree[neighbor] -= 1

        # Count remaining edges
        remaining_edges = sum(degree) // 2
        return remaining_edges * 2