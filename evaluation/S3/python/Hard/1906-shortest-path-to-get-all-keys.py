# Source: https://leetcode.com/problems/shortest-path-to-get-all-keys/   |   Difficulty: Hard
#
# Problem Description:
# You are given an m x n grid grid where:
#
#
# 	'.' is an empty cell.
# 	'#' is a wall.
# 	'@' is the starting point.
# 	Lowercase letters represent keys.
# 	Uppercase letters represent locks.
#
#
# You start at the starting point and one move consists of walking one space in one of the four cardinal directions. You cannot walk outside the grid, or walk into a wall.
#
# If you walk over a key, you can pick it up and you cannot walk over a lock unless you have its corresponding key.
#
# For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of the first k letters of the English alphabet in the grid. This means that there is exactly one key for each lock, and one lock for each key; and also that the letters used to represent the keys and locks were chosen in the same order as the English alphabet.
#
# Return the lowest number of moves to acquire all keys. If it is impossible, return -1.
#
# Example:
# Input: grid = ["@.a..","###.#","b.A.B"]
# Output: 8
# Explanation: Note that the goal is to obtain all the keys not to open all the locks.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 30
# 	grid[i][j] is either an English letter, '.', '#', or '@'. 
# 	There is exactly one '@' in the grid.
# 	The number of keys in the grid is in the range [1, 6].
# 	Each key in the grid is unique.
# 	Each key in the grid has a matching lock.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, multi-source-bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
#   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
#   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
#   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
# - Breadth-first search (graph, deque, array, 01-bfs)
#   • When to use: When finding the shortest path in a graph where edge weights are restricted to 0 or 1, or when minimizing operations where some operations are 'free' (cost 0) and others have a unit cost (cost 1).
#   • Idea: A graph traversal algorithm that finds the shortest path from a source to all reachable nodes in a graph where edge weights are either 0 or 1. It uses a deque to prioritize 0-cost edges, achieving an optimal O(V + E) time complexity.
#   • Invariants: Nodes are added to the front of the deque if the edge weight is 0, and to the back if 1.; The distance `dist[u]` for any node `u` in the deque is either `k` or `k+1` for some integer `k`.
#   • Tips: Use a deque: push 0-cost edges to the front, 1-cost edges to the back.; Mark nodes visited to avoid cycles and redundant processing.
#   • Pitfalls: Incorrectly handling visited states can lead to infinite loops or incorrect paths.; Forgetting to initialize distances properly before starting the traversal.
# - Hungarian algorithm for solving the assignment problem (matrix, graph, greedy, bfs)
#   • When to use: Finds shortest paths in unweighted graphs or uniform-cost state-space searches. Explores states layer by layer.
#   • Idea: Explores all reachable nodes in a graph layer by layer, finding the shortest path in unweighted graphs. It operates in O(V + E) time complexity.
#   • Invariants: All nodes currently in the queue are at the same distance from the source.; All nodes visited so far have their shortest distance from the source determined.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops.; Incorrectly handling disconnected components.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shortestPathAllKeys(self, grid):
        """
        :type grid: List[str]
        :rtype: int
        """
        from collections import deque

        m, n = len(grid), len(grid[0])
        all_keys = 0
        start_x = start_y = 0

        # Find the starting point and count the total number of keys
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '@':
                    start_x, start_y = i, j
                elif 'a' <= grid[i][j] <= 'f':
                    all_keys |= (1 << (ord(grid[i][j]) - ord('a')))

        # BFS initialization
        queue = deque([(start_x, start_y, 0, 0)])  # (x, y, keys_collected, steps)
        visited = set((start_x, start_y, 0))  # (x, y, keys_collected)

        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        while queue:
            x, y, keys_collected, steps = queue.popleft()

            # Check if we have collected all keys
            if keys_collected == all_keys:
                return steps

            for dx, dy in directions:
                nx, ny = x + dx, y + dy

                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] != '#':
                    cell = grid[nx][ny]
                    new_keys_collected = keys_collected

                    if 'a' <= cell <= 'f':  # If it's a key
                        new_keys_collected |= (1 << (ord(cell) - ord('a')))
                    elif 'A' <= cell <= 'F':  # If it's a lock
                        if not (keys_collected & (1 << (ord(cell) - ord('A')))):
                            continue  # Skip if we don't have the key

                    if (nx, ny, new_keys_collected) not in visited:
                        visited.add((nx, ny, new_keys_collected))
                        queue.append((nx, ny, new_keys_collected, steps + 1))

        return -1