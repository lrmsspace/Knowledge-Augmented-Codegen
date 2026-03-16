# Source: https://leetcode.com/problems/regions-cut-by-slashes/   |   Difficulty: Medium
#
# Problem Description:
# An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
#
# Given the grid grid represented as a string array, return the number of regions.
#
# Note that backslash characters are escaped, so a '\' is represented as '\\'.
#
# Example:
# Input: grid = [" /","/ "]
# Output: 2
#
# Constraints:
# n == grid.length == grid[i].length
# 	1 <= n <= 30
# 	grid[i][j] is either '/', '\', or ' '.
#

class Solution(object):
    def regionsBySlashes(self, grid):
        """
        :type grid: List[str]
        :rtype: int
        """
        n = len(grid)
        parent = [i for i in range(4 * n * n)]

        def find(x):
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            parent[find(x)] = find(y)

        for r in range(n):
            for c in range(n):
                root = 4 * (r * n + c)
                val = grid[r][c]
                if val == '/':
                    union(root + 0, root + 3)
                    union(root + 1, root + 2)
                elif val == '\\':
                    union(root + 0, root + 1)
                    union(root + 2, root + 3)
                else:
                    union(root + 0, root + 1)
                    union(root + 1, root + 2)
                    union(root + 2, root + 3)

                if c + 1 < n:
                    union(root + 1, 4 * (r * n + c + 1) + 3)
                if r + 1 < n:
                    union(root + 2, 4 * ((r + 1) * n + c) + 0)

        regions = sum(1 for i in range(4 * n * n) if find(i) == i)
        return regions