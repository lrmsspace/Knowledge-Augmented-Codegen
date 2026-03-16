# Source: https://leetcode.com/problems/nearest-exit-from-entrance-in-maze/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix maze (0-indexed) with empty cells (represented as '.') and walls (represented as '+'). You are also given the entrance of the maze, where entrance = [entrancerow, entrancecol] denotes the row and column of the cell you are initially standing at.
#
# In one step, you can move one cell up, down, left, or right. You cannot step into a cell with a wall, and you cannot step outside the maze. Your goal is to find the nearest exit from the entrance. An exit is defined as an empty cell that is at the border of the maze. The entrance does not count as an exit.
#
# Return the number of steps in the shortest path from the entrance to the nearest exit, or -1 if no such path exists.
#
# Example:
# Input: maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
# Output: 1
# Explanation: There are 3 exits in this maze at [1,0], [0,2], and [2,3].
# Initially, you are at the entrance cell [1,2].
# - You can reach [1,0] by moving 2 steps left.
# - You can reach [0,2] by moving 1 step up.
# It is impossible to reach [2,3] from the entrance.
# Thus, the nearest exit is [0,2], which is 1 step away.
#
# Constraints:
# maze.length == m
# 	maze[i].length == n
# 	1 <= m, n <= 100
# 	maze[i][j] is either '.' or '+'.
# 	entrance.length == 2
# 	0 <= entrancerow < m
# 	0 <= entrancecol < n
# 	entrance will always be an empty cell.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
# - Hungarian algorithm for solving the assignment problem (matrix, graph, greedy, bfs)
#   • When to use: Finds shortest paths in unweighted graphs or uniform-cost state-space searches. Explores states layer by layer.
#   • Idea: Explores all reachable nodes in a graph layer by layer, finding the shortest path in unweighted graphs. It operates in O(V + E) time complexity.
#   • Invariants: All nodes currently in the queue are at the same distance from the source.; All nodes visited so far have their shortest distance from the source determined.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops.; Incorrectly handling disconnected components.
# - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
#   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
#   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
#   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
#   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
#   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def nearestExit(self, maze, entrance):
        """
        :type maze: List[List[str]]
        :type entrance: List[int]
        :rtype: int
        """
        from collections import deque

        rows, cols = len(maze), len(maze[0])
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        queue = deque()
        queue.append((entrance[0], entrance[1], 0))  # (row, col, steps)
        visited = set()
        visited.add((entrance[0], entrance[1]))

        while queue:
            r, c, steps = queue.popleft()

            # Check if we are at an exit (not the entrance)
            if (r == 0 or r == rows - 1 or c == 0 or c == cols - 1) and (r, c) != (entrance[0], entrance[1]):
                return steps

            # Explore neighbors
            for dr, dc in directions:
                nr, nc = r + dr, c + dc
                if 0 <= nr < rows and 0 <= nc < cols and maze[nr][nc] == '.' and (nr, nc) not in visited:
                    visited.add((nr, nc))
                    queue.append((nr, nc, steps + 1))

        return -1