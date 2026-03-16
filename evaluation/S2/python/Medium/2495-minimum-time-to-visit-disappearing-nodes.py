# Source: https://leetcode.com/problems/minimum-time-to-visit-disappearing-nodes/   |   Difficulty: Medium
#
# Problem Description:
# There is an undirected graph of n nodes. You are given a 2D array edges, where edges[i] = [ui, vi, lengthi] describes an edge between node ui and node vi with a traversal time of lengthi units.
#
# Additionally, you are given an array disappear, where disappear[i] denotes the time when the node i disappears from the graph and you won't be able to visit it.
#
# Note that the graph might be disconnected and might contain multiple edges.
#
# Return the array answer, with answer[i] denoting the minimum units of time required to reach node i from node 0. If node i is unreachable from node 0 then answer[i] is -1.
#
# Example:
# Input: n = 3, edges = [[0,1,2],[1,2,1],[0,2,4]], disappear = [1,1,5]
#
# Output: [0,-1,4]
#
# Explanation:
#
#
#
# We are starting our journey from node 0, and our goal is to find the minimum time required to reach each node before it disappears.
#
#
# 	For node 0, we don't need any time as it is our starting point.
# 	For node 1, we need at least 2 units of time to traverse edges[0]. Unfortunately, it disappears at that moment, so we won't be able to visit it.
# 	For node 2, we need at least 4 units of time to traverse edges[2].
#
# Constraints:
# 1 <= n <= 5 * 104
# 	0 <= edges.length <= 105
# 	edges[i] == [ui, vi, lengthi]
# 	0 <= ui, vi <= n - 1
# 	1 <= lengthi <= 105
# 	disappear.length == n
# 	1 <= disappear[i] <= 105
#
# Helpful references (internal KB):
# - Bellman-Ford Algorithm (graph, array, bellman-ford, dp-1d)
#   • When to use: Finds single-source shortest paths in a weighted directed graph, especially when negative edge weights are present. It can also detect negative cycles reachable from the source.
#   • Idea: Bellman-Ford iteratively relaxes all edges n-1 times to find single-source shortest paths in a weighted directed graph. It runs in O(VE) time and can detect negative cycles.
#   • Invariants: After k phases, dist[u] holds the shortest path length from source to u using at most k edges.; For any edge (u, v) with weight w, dist[v] <= dist[u] + w if dist[u] is finite and v is reachable.
#   • Tips: Initialize source distance to 0 and all other distances to infinity.; Perform exactly n-1 full passes, relaxing all edges in each pass.
#   • Pitfalls: Incorrectly handling unreachable vertices (distances remaining infinity).; Not detecting negative cycles when they exist, leading to incorrect path lengths.
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
# - Games on arbitrary graphs (graph, array, dfs, game-theory)
#   • When to use: Use this algorithm to determine the outcome (win, lose, or draw) for every possible starting position in a two-player game played on a directed graph, assuming both players play optimally.
#   • Idea: This algorithm classifies each vertex in a directed graph as a winning, losing, or draw state for a two-player game. It iteratively applies rules based on neighbor states, optimized by a Depth-First Search on the reversed graph, achieving an O(M) time complexity.
#   • Invariants: A vertex `u` is a winning state if and only if it has at least one successor `v` that is a losing state.; A vertex `u` is a losing state if and only if all its successors `v` are winning states.
#   • Tips: Construct the reversed graph to efficiently propagate state classifications from successors to predecessors.; Initialize states for terminal vertices (those with no outgoing edges) as losing states.
#   • Pitfalls: Forgetting to account for draw states, which occur when neither winning nor losing conditions are met.; Incorrectly classifying terminal nodes; they are typically losing states in normal play games.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumTime(self, n, edges, disappear):
        """
        :type n: int
        :type edges: List[List[int]]
        :type disappear: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict
        import heapq

        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))

        dist = [float('inf')] * n
        dist[0] = 0
        min_heap = [(0, 0)]  # (time, node)

        while min_heap:
            time, node = heapq.heappop(min_heap)

            if time > dist[node]:
                continue

            for neighbor, weight in graph[node]:
                new_time = time + weight
                if new_time < dist[neighbor] and new_time < disappear[neighbor]:
                    dist[neighbor] = new_time
                    heapq.heappush(min_heap, (new_time, neighbor))

        return [d if d != float('inf') else -1 for d in dist]