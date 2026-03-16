# Source: https://leetcode.com/problems/grid-teleportation-traversal/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D character grid matrix of size m x n, represented as an array of strings, where matrix[i][j] represents the cell at the intersection of the ith row and jth column. Each cell is one of the following:
#
#
# 	'.' representing an empty cell.
# 	'#' representing an obstacle.
# 	An uppercase letter ('A'-'Z') representing a teleportation portal.
#
#
# You start at the top-left cell (0, 0), and your goal is to reach the bottom-right cell (m - 1, n - 1). You can move from the current cell to any adjacent cell (up, down, left, right) as long as the destination cell is within the grid bounds and is not an obstacle.
#
# If you step on a cell containing a portal letter and you haven't used that portal letter before, you may instantly teleport to any other cell in the grid with the same letter. This teleportation does not count as a move, but each portal letter can be used at most once during your journey.
#
# Return the minimum number of moves required to reach the bottom-right cell. If it is not possible to reach the destination, return -1.
#
# Example:
# Input: matrix = ["A..",".A.","..."]
#
# Output: 2
#
# Explanation:
#
#
#
#
# 	Before the first move, teleport from (0, 0) to (1, 1).
# 	In the first move, move from (1, 1) to (1, 2).
# 	In the second move, move from (1, 2) to (2, 2).
#
# Constraints:
# 1 <= m == matrix.length <= 103
# 	1 <= n == matrix[i].length <= 103
# 	matrix[i][j] is either '#', '.', or an uppercase English letter.
# 	matrix[0][0] is not an obstacle.
#
# Helpful references (internal KB):
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
# - 0-1 BFS (graph, queue, 01-bfs, bfs)
#   • When to use: Use when finding shortest paths in a graph where edge weights are restricted to only 0 or 1. It efficiently determines minimum distances from a source to all reachable nodes, outperforming Dijkstra's for this specific weight constraint.
#   • Idea: 0-1 BFS is a graph traversal algorithm that finds shortest paths from a single source in a graph where all edge weights are either 0 or 1. It achieves this in O(V + E) time complexity by using a deque to prioritize 0-weight edges.
#   • Invariants: All nodes in the deque have a distance value less than or equal to any node not yet processed.; Nodes added to the front of the deque (0-weight edges) always have a distance equal to the node they came from.
#   • Tips: Use a deque to maintain order: 0-weight edges go to front, 1-weight edges to back.; Initialize distances to infinity and source distance to 0.
#   • Pitfalls: Forgetting to update distances for 0-weight edges before adding to deque front.; Incorrectly handling visited states, leading to TLE or incorrect paths.
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
    def minMoves(self, matrix):
        """
        :type matrix: List[str]
        :rtype: int
        """
        from collections import deque, defaultdict

        m, n = len(matrix), len(matrix[0])
        portals = defaultdict(list)

        for i in range(m):
            for j in range(n):
                if matrix[i][j].isalpha():
                    portals[matrix[i][j]].append((i, j))

        directions = [(0, 1), (0, -1), (1, 0), (-1, 0)]
        visited = [[False] * n for _ in range(m)]
        visited[0][0] = True
        queue = deque([(0, 0, 0)])  # (x, y, moves)
        used_portals = set()

        while queue:
            x, y, moves = queue.popleft()

            if (x, y) == (m - 1, n - 1):
                return moves

            # Move to adjacent cells
            for dx, dy in directions:
                nx, ny = x + dx, y + dy
                if 0 <= nx < m and 0 <= ny < n and not visited[nx][ny] and matrix[nx][ny] != '#':
                    visited[nx][ny] = True
                    queue.append((nx, ny, moves + 1))

            # Teleportation
            if matrix[x][y].isalpha() and matrix[x][y] not in used_portals:
                used_portals.add(matrix[x][y])
                for px, py in portals[matrix[x][y]]:
                    if not visited[px][py]:
                        visited[px][py] = True
                        queue.append((px, py, moves))  # Teleportation does not count as a move

        return -1