# Source: https://leetcode.com/problems/shortest-path-with-alternating-colors/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n, the number of nodes in a directed graph where the nodes are labeled from 0 to n - 1. Each edge is red or blue in this graph, and there could be self-edges and parallel edges.
#
# You are given two arrays redEdges and blueEdges where:
#
#
# 	redEdges[i] = [ai, bi] indicates that there is a directed red edge from node ai to node bi in the graph, and
# 	blueEdges[j] = [uj, vj] indicates that there is a directed blue edge from node uj to node vj in the graph.
#
#
# Return an array answer of length n, where each answer[x] is the length of the shortest path from node 0 to node x such that the edge colors alternate along the path, or -1 if such a path does not exist.
#
# Example:
# Input: n = 3, redEdges = [[0,1],[1,2]], blueEdges = []
# Output: [0,1,-1]
#
# Constraints:
# 1 <= n <= 100
# 	0 <= redEdges.length, blueEdges.length <= 400
# 	redEdges[i].length == blueEdges[j].length == 2
# 	0 <= ai, bi, uj, vj < n
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
# - Check whether a graph is bipartite (graph, queue, bfs)
#   • When to use: Use this when you need to determine if an undirected graph can be divided into two independent sets such that all edges connect vertices from different sets, or if it is two-colorable.
#   • Idea: This algorithm determines if an undirected graph is bipartite by attempting to 2-color it using BFS. It assigns alternating colors (or sets) to adjacent vertices, detecting non-bipartite conditions if an edge connects two vertices of the same color.
#   • Invariants: All visited vertices within the current BFS component are correctly 2-colored.; All edges processed so far connect vertices of different colors.
#   • Tips: Use two distinct colors (e.g., 0 and 1) to represent the two sets.; Iterate through all vertices and start a new BFS from any unvisited vertex to handle disconnected components.
#   • Pitfalls: Forgetting to handle disconnected graphs by ensuring all vertices are visited.; Incorrectly assigning colors, leading to false positives or negatives.
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shortestAlternatingPaths(self, n, redEdges, blueEdges):
        """
        :type n: int
        :type redEdges: List[List[int]]
        :type blueEdges: List[List[int]]
        :rtype: List[int]
        """
        from collections import deque, defaultdict

        # Build the graph with color information
        graph = defaultdict(lambda: {'red': [], 'blue': []})
        for u, v in redEdges:
            graph[u]['red'].append(v)
        for u, v in blueEdges:
            graph[u]['blue'].append(v)

        # Initialize distances: dist[node][color] = distance
        dist = [[float('inf'), float('inf')] for _ in range(n)]
        dist[0] = [0, 0]  # Distance to node 0 is 0 for both colors

        # BFS queue: (node, color)
        queue = deque([(0, 'red'), (0, 'blue')])

        while queue:
            node, color = queue.popleft()
            next_color = 'blue' if color == 'red' else 'red'
            for neighbor in graph[node][next_color]:
                color_index = 0 if next_color == 'red' else 1
                if dist[neighbor][color_index] == float('inf'):
                    dist[neighbor][color_index] = dist[node][0 if color == 'red' else 1] + 1
                    queue.append((neighbor, next_color))

        # Prepare the result
        result = []
        for red_dist, blue_dist in dist:
            min_dist = min(red_dist, blue_dist)
            result.append(min_dist if min_dist != float('inf') else -1)

        return result