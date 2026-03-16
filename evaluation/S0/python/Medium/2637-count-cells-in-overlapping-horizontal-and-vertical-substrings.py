# Source: https://leetcode.com/problems/count-cells-in-overlapping-horizontal-and-vertical-substrings/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix grid consisting of characters and a string pattern.
#
# A horizontal substring is a contiguous sequence of characters read from left to right. If the end of a row is reached before the substring is complete, it wraps to the first column of the next row and continues as needed. You do not wrap from the bottom row back to the top.
#
# A vertical substring is a contiguous sequence of characters read from top to bottom. If the bottom of a column is reached before the substring is complete, it wraps to the first row of the next column and continues as needed. You do not wrap from the last column back to the first.
#
# Count the number of cells in the matrix that satisfy the following condition:
#
#
# 	The cell must be part of at least one horizontal substring and at least one vertical substring, where both substrings are equal to the given pattern.
#
#
# Return the count of these cells.
#
# Example:
# Input: grid = [["a","a","c","c"],["b","b","b","c"],["a","a","b","a"],["c","a","a","c"],["a","a","b","a"]], pattern = "abaca"
#
# Output: 1
#
# Explanation:
#
# The pattern "abaca" appears once as a horizontal substring (colored blue) and once as a vertical substring (colored red), intersecting at one cell (colored purple).
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 1000
# 	1 <= m * n <= 105
# 	1 <= pattern.length <= m * n
# 	grid and pattern consist of only lowercase English letters.
#

class Solution(object):
    def countCells(self, grid, pattern):
        """
        :type grid: List[List[str]]
        :type pattern: str
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        p_len = len(pattern)
        
        horizontal_positions = set()
        vertical_positions = set()
        
        # Check horizontal substrings
        for i in range(m):
            row_str = ''.join(grid[i])
            extended_row_str = row_str + row_str  # To handle wrapping
            for j in range(n):
                if extended_row_str[j:j+p_len] == pattern:
                    for k in range(p_len):
                        horizontal_positions.add((i, (j + k) % n))
        
        # Check vertical substrings
        for j in range(n):
            col_str = ''.join(grid[i][j] for i in range(m))
            extended_col_str = col_str + col_str  # To handle wrapping
            for i in range(m):
                if extended_col_str[i:i+p_len] == pattern:
                    for k in range(p_len):
                        vertical_positions.add(((i + k) % m, j))
        
        # Count overlapping positions
        count = 0
        for pos in horizontal_positions:
            if pos in vertical_positions:
                count += 1
        
        return count