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
# - N/A
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

        while queue:
            x, y, keys_collected, steps = queue.popleft()

            # Check if we have collected all keys
            if keys_collected == all_keys:
                return steps

            # Explore the four directions
            for dx, dy in [(-1, 0), (1, 0), (0, -1), (0, 1)]:
                new_x, new_y = x + dx, y + dy

                if 0 <= new_x < m and 0 <= new_y < n and grid[new_x][new_y] != '#':
                    cell = grid[new_x][new_y]
                    new_keys_collected = keys_collected

                    # If it's a key, collect it
                    if 'a' <= cell <= 'f':
                        new_keys_collected |= (1 << (ord(cell) - ord('a')))

                    # If it's a lock, check if we have the corresponding key
                    if 'A' <= cell <= 'F' and not (keys_collected & (1 << (ord(cell) - ord('A')))):
                        continue

                    # If we haven't visited this state before
                    if (new_x, new_y, new_keys_collected) not in visited:
                        visited.add((new_x, new_y, new_keys_collected))
                        queue.append((new_x, new_y, new_keys_collected, steps + 1))

        return -1