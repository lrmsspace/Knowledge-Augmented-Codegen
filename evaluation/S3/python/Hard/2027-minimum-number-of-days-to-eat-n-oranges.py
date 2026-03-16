# Source: https://leetcode.com/problems/minimum-number-of-days-to-eat-n-oranges/   |   Difficulty: Hard
#
# Problem Description:
# There are n oranges in the kitchen and you decided to eat some of these oranges every day as follows:
#
#
# 	Eat one orange.
# 	If the number of remaining oranges n is divisible by 2 then you can eat n / 2 oranges.
# 	If the number of remaining oranges n is divisible by 3 then you can eat 2 * (n / 3) oranges.
#
#
# You can only choose one of the actions per day.
#
# Given the integer n, return the minimum number of days to eat n oranges.
#
# Example:
# Input: n = 10
# Output: 4
# Explanation: You have 10 oranges.
# Day 1: Eat 1 orange,  10 - 1 = 9.  
# Day 2: Eat 6 oranges, 9 - 2*(9/3) = 9 - 6 = 3. (Since 9 is divisible by 3)
# Day 3: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. 
# Day 4: Eat the last orange  1 - 1  = 0.
# You need at least 4 days to eat the 10 oranges.
#
# Constraints:
# 1 <= n <= 2 * 109
#
# Helpful references (internal KB):
# - Breadth-first search (graph, deque, array, 01-bfs)
#   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
#   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
#   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
#   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
#   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
# - Breadth-first search (graph, array, bfs, counting)
#   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
#   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
#   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
#   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minDays(self, n):
        """
        :type n: int
        :rtype: int
        """
        from collections import deque

        if n <= 1:
            return n

        queue = deque([(n, 0)])  # (current_oranges, days)
        visited = set([n])

        while queue:
            oranges, days = queue.popleft()

            if oranges == 0:
                return days

            # Eat one orange
            if oranges - 1 not in visited:
                visited.add(oranges - 1)
                queue.append((oranges - 1, days + 1))

            # Eat n/2 oranges if divisible by 2
            if oranges % 2 == 0 and oranges // 2 not in visited:
                visited.add(oranges // 2)
                queue.append((oranges // 2, days + 1))

            # Eat 2*(n/3) oranges if divisible by 3
            if oranges % 3 == 0 and oranges - (2 * (oranges // 3)) not in visited:
                visited.add(oranges - (2 * (oranges // 3)))
                queue.append((oranges - (2 * (oranges // 3)), days + 1))

        return -1