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
# - Breadth-first search (graph, array, bfs)
#   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
#   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
#   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
#   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
#   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Submask Enumeration
#  (number, bitset, enumeration, bitmask-dp)
#   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
#   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
#   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
#   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
#   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
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
        
        # Find the starting point and the total number of keys
        for i in range(m):
            for j in range(n):
                if grid[i][j] == '@':
                    start_x, start_y = i, j
                elif 'a' <= grid[i][j] <= 'f':
                    all_keys |= (1 << (ord(grid[i][j]) - ord('a')))
        
        # BFS initialization
        queue = deque([(start_x, start_y, 0, 0)])  # (x, y, keys_collected, steps)
        visited = set((start_x, start_y, 0))
        
        while queue:
            x, y, keys_collected, steps = queue.popleft()
            
            # Check if we have collected all keys
            if keys_collected == all_keys:
                return steps
            
            # Explore neighbors
            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                nx, ny = x + dx, y + dy
                
                if 0 <= nx < m and 0 <= ny < n and grid[nx][ny] != '#':
                    cell = grid[nx][ny]
                    new_keys_collected = keys_collected
                    
                    if 'a' <= cell <= 'f':  # Collect key
                        new_keys_collected |= (1 << (ord(cell) - ord('a')))
                    elif 'A' <= cell <= 'F':  # Check lock
                        if not (keys_collected & (1 << (ord(cell) - ord('A')))):
                            continue
                    
                    if (nx, ny, new_keys_collected) not in visited:
                        visited.add((nx, ny, new_keys_collected))
                        queue.append((nx, ny, new_keys_collected, steps + 1))
        
        return -1  # If it's impossible to collect all keys