# Source: https://leetcode.com/problems/minimum-score-of-a-path-between-two-cities/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer n representing n cities numbered from 1 to n. You are also given a 2D array roads where roads[i] = [ai, bi, distancei] indicates that there is a bidirectional road between cities ai and bi with a distance equal to distancei. The cities graph is not necessarily connected.
#
# The score of a path between two cities is defined as the minimum distance of a road in this path.
#
# Return the minimum possible score of a path between cities 1 and n.
#
# Note:
#
#
# 	A path is a sequence of roads between two cities.
# 	It is allowed for a path to contain the same road multiple times, and you can visit cities 1 and n multiple times along the path.
# 	The test cases are generated such that there is at least one path between 1 and n.
#
# Example:
# Input: n = 4, roads = [[1,2,9],[2,3,6],[2,4,5],[1,4,7]]
# Output: 5
# Explanation: The path from city 1 to 4 with the minimum score is: 1 -> 2 -> 4. The score of this path is min(9,5) = 5.
# It can be shown that no other path has less score.
#
# Constraints:
# 2 <= n <= 105
# 	1 <= roads.length <= 105
# 	roads[i].length == 3
# 	1 <= ai, bi <= n
# 	ai != bi
# 	1 <= distancei <= 104
# 	There are no repeated edges.
# 	There is at least one path between 1 and n.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, multi-source-bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
#   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
#   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
#   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when you need to find the shortest path (in terms of number of edges) from a source node to all other reachable nodes in an unweighted graph. It is also suitable for exploring a graph layer by layer.
#   • Idea: BFS systematically explores a graph level by level, starting from a source node, ensuring all nodes at a given distance are visited before moving to the next distance level. It operates in O(N + M) time for N vertices and M edges.
#   • Invariants: All nodes currently in the queue are at the same or adjacent distance level from the source.; The 'used' array accurately reflects all nodes that have been added to the queue for processing.
#   • Tips: Always use a queue to maintain the order of nodes to visit.; Utilize a 'visited' array or set to prevent revisiting nodes and infinite loops.
#   • Pitfalls: Does not find shortest paths in weighted graphs unless weights are 0 or 1 (use Dijkstra for general weighted graphs).; Forgetting to mark nodes as visited can lead to incorrect results or TLE.
# - Breadth-first search (graph, array, bfs, counting)
#   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
#   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
#   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
#   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minScore(self, n, roads):
        """
        :type n: int
        :type roads: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict, deque

        graph = defaultdict(list)
        for a, b, d in roads:
            graph[a].append((b, d))
            graph[b].append((a, d))

        min_score = float('inf')
        visited = [False] * (n + 1)
        queue = deque([1])
        visited[1] = True

        while queue:
            city = queue.popleft()
            for neighbor, dist in graph[city]:
                min_score = min(min_score, dist)
                if not visited[neighbor]:
                    visited[neighbor] = True
                    queue.append(neighbor)

        return min_score