# Source: https://leetcode.com/problems/minimum-moves-to-clean-the-classroom/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n grid classroom where a student volunteer is tasked with cleaning up litter scattered around the room. Each cell in the grid is one of the following:
#
#
# 	'S': Starting position of the student
# 	'L': Litter that must be collected (once collected, the cell becomes empty)
# 	'R': Reset area that restores the student's energy to full capacity, regardless of their current energy level (can be used multiple times)
# 	'X': Obstacle the student cannot pass through
# 	'.': Empty space
#
#
# You are also given an integer energy, representing the student's maximum energy capacity. The student starts with this energy from the starting position 'S'.
#
# Each move to an adjacent cell (up, down, left, or right) costs 1 unit of energy. If the energy reaches 0, the student can only continue if they are on a reset area 'R', which resets the energy to its maximum capacity energy.
#
# Return the minimum number of moves required to collect all litter items, or -1 if it's impossible.
#
# Example:
# Input: classroom = ["S.", "XL"], energy = 2
#
# Output: 2
#
# Explanation:
#
#
# 	The student starts at cell (0, 0) with 2 units of energy.
# 	Since cell (1, 0) contains an obstacle 'X', the student cannot move directly downward.
# 	A valid sequence of moves to collect all litter is as follows:
# 	
# 		Move 1: From (0, 0) → (0, 1) with 1 unit of energy and 1 unit remaining.
# 		Move 2: From (0, 1) → (1, 1) to collect the litter 'L'.
# 	
# 	
# 	The student collects all the litter using 2 moves. Thus, the output is 2.
#
# Constraints:
# 1 <= m == classroom.length <= 20
# 	1 <= n == classroom[i].length <= 20
# 	classroom[i][j] is one of 'S', 'L', 'R', 'X', or '.'
# 	1 <= energy <= 50
# 	There is exactly one 'S' in the grid.
# 	There are at most 10 'L' cells in the grid.
#
# Helpful references (internal KB):
# - Breadth-first search (graph, array, stack, bfs, enumeration)
#   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level. It is suitable for exploring all reachable nodes from a source in increasing order of distance.
#   • Idea: Breadth-First Search (BFS) is a graph traversal algorithm that explores all the neighbor nodes at the current depth level before moving on to nodes at the next depth level. It finds the shortest path in an unweighted graph in O(V + E) time.
#   • Invariants: All nodes currently in the queue are at the same or adjacent depth level.; All 'marked' nodes have been visited, and their 'distTo' values are the shortest path from the source.
#   • Tips: Use a queue to manage nodes to visit, ensuring level-by-level exploration.; Maintain a 'visited' array or set to prevent cycles and redundant processing.
#   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly using a stack instead of a queue will result in Depth-First Search behavior.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
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
    def minMoves(self, classroom, energy):
        """
        :type classroom: List[str]
        :type energy: int
        :rtype: int
        """
        from collections import deque
        m, n = len(classroom), len(classroom[0])
        litter_positions = []
        start = None

        for i in range(m):
            for j in range(n):
                if classroom[i][j] == 'S':
                    start = (i, j)
                elif classroom[i][j] == 'L':
                    litter_positions.append((i, j))

        litter_count = len(litter_positions)
        all_collected_mask = (1 << litter_count) - 1
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        def bfs(start_pos):
            dist = [[-1] * n for _ in range(m)]
            dist[start_pos[0]][start_pos[1]] = 0
            queue = deque([start_pos])

            while queue:
                x, y = queue.popleft()
                for dx, dy in directions:
                    nx, ny = x + dx, y + dy
                    if 0 <= nx < m and 0 <= ny < n and classroom[nx][ny] != 'X' and dist[nx][ny] == -1:
                        dist[nx][ny] = dist[x][y] + 1
                        queue.append((nx, ny))
            return dist

        dist_from_start = bfs(start)
        dist_from_litter = [bfs(pos) for pos in litter_positions]

        dp = [[[float('inf')] * (energy + 1) for _ in range(litter_count)] for _ in range(1 << litter_count)]

        for i in range(litter_count):
            d = dist_from_start[litter_positions[i][0]][litter_positions[i][1]]
            if d != -1 and d <= energy:
                dp[1 << i][i][energy - d] = d

        for mask in range(1 << litter_count):
            for last in range(litter_count):
                for e in range(energy + 1):
                    if dp[mask][last][e] == float('inf'):
                        continue
                    for next in range(litter_count):
                        if mask & (1 << next):
                            continue
                        d = dist_from_litter[last][litter_positions[next][0]][litter_positions[next][1]]
                        if d != -1 and d <= e:
                            new_mask = mask | (1 << next)
                            dp[new_mask][next][e - d] = min(dp[new_mask][next][e - d], dp[mask][last][e] + d)

        min_moves = float('inf')
        for last in range(litter_count):
            for e in range(energy + 1):
                min_moves = min(min_moves, dp[all_collected_mask][last][e])
        return min_moves if min_moves != float('inf') else -1