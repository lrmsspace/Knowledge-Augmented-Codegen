# Source: https://leetcode.com/problems/minimum-moves-to-move-a-box-to-their-target-location/   |   Difficulty: Hard
#
# Problem Description:
# A storekeeper is a game in which the player pushes boxes around in a warehouse trying to get them to target locations.
#
# The game is represented by an m x n grid of characters grid where each element is a wall, floor, or box.
#
# Your task is to move the box 'B' to the target position 'T' under the following rules:
#
#
# 	The character 'S' represents the player. The player can move up, down, left, right in grid if it is a floor (empty cell).
# 	The character '.' represents the floor which means a free cell to walk.
# 	The character '#' represents the wall which means an obstacle (impossible to walk there).
# 	There is only one box 'B' and one target cell 'T' in the grid.
# 	The box can be moved to an adjacent free cell by standing next to the box and then moving in the direction of the box. This is a push.
# 	The player cannot walk through the box.
#
#
# Return the minimum number of pushes to move the box to the target. If there is no way to reach the target, return -1.
#
# Example:
# Input: grid = [["#","#","#","#","#","#"],
#                ["#","T","#","#","#","#"],
#                ["#",".",".","B",".","#"],
#                ["#",".","#","#",".","#"],
#                ["#",".",".",".","S","#"],
#                ["#","#","#","#","#","#"]]
# Output: 3
# Explanation: We return only the number of times the box is pushed.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 20
# 	grid contains only characters '.', '#', 'S', 'T', or 'B'.
# 	There is only one character 'S', 'B', and 'T' in the grid.
#
# Helpful references (internal KB):
# - 0-1 BFS (graph, deque, 01-bfs, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently computes single-source shortest paths, outperforming Dijkstra's for this specific weight constraint.
#   • Idea: 0-1 BFS is a graph traversal algorithm that finds the single-source shortest paths in a graph where all edge weights are restricted to 0 or 1. It uses a deque to process nodes, achieving an optimal time complexity of O(V + E).
#   • Invariants: When a node 'u' is extracted from the front of the deque, 'dist[u]' is its shortest path from the source.; The deque always contains nodes whose distances are either 'D' or 'D+1', where 'D' is the distance of the last node extracted.
#   • Tips: Always push 0-weight edges to the front of the deque.; Push 1-weight edges to the back of the deque.
#   • Pitfalls: Pushing 0-weight edges to the back or 1-weight edges to the front of the deque.; Not correctly initializing distances or the source node.
# - Breadth-first search (graph, queue, array, bfs)
#   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
#   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
#   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
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
    def minPushBox(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """
        from collections import deque

        m, n = len(grid), len(grid[0])
        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]

        # Find initial positions of the box, target, and player
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 'B':
                    box_start = (i, j)
                elif grid[i][j] == 'T':
                    target = (i, j)
                elif grid[i][j] == 'S':
                    player_start = (i, j)

        # BFS to find minimum pushes
        queue = deque([(box_start, player_start, 0)])  # (box_position, player_position, pushes)
        visited = set((box_start, player_start))

        while queue:
            box_pos, player_pos, pushes = queue.popleft()

            if box_pos == target:
                return pushes

            for dx, dy in directions:
                new_box_pos = (box_pos[0] + dx, box_pos[1] + dy)
                new_player_pos = (box_pos[0] - dx, box_pos[1] - dy)

                # Check if new box position is valid
                if 0 <= new_box_pos[0] < m and 0 <= new_box_pos[1] < n and grid[new_box_pos[0]][new_box_pos[1]] != '#':
                    # Check if player can reach the position to push the box
                    if self.can_reach(grid, player_pos, new_player_pos, box_pos):
                        state = (new_box_pos, box_pos)
                        if state not in visited:
                            visited.add(state)
                            queue.append((new_box_pos, box_pos, pushes + 1))
        return -1   