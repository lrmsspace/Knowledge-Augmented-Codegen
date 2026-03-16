# Source: https://leetcode.com/problems/equal-row-and-column-pairs/   |   Difficulty: Medium
#
# Problem Description:
# Given a 0-indexed n x n integer matrix grid, return the number of pairs (ri, cj) such that row ri and column cj are equal.
#
# A row and column pair is considered equal if they contain the same elements in the same order (i.e., an equal array).
#
# Example:
# Input: grid = [[3,2,1],[1,7,6],[2,7,7]]
# Output: 1
# Explanation: There is 1 equal row and column pair:
# - (Row 2, Column 1): [2,7,7]
#
# Constraints:
# n == grid.length == grid[i].length
# 	1 <= n <= 200
# 	1 <= grid[i][j] <= 105
#

class Solution(object):
    def equalPairs(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        n = len(grid)
        count = 0
        
        # Create a dictionary to store the frequency of each row
        row_map = {}
        for row in grid:
            row_tuple = tuple(row)
            if row_tuple in row_map:
                row_map[row_tuple] += 1
            else:
                row_map[row_tuple] = 1
        
        # Check each column against the rows
        for col in range(n):
            col_tuple = tuple(grid[row][col] for row in range(n))
            if col_tuple in row_map:
                count += row_map[col_tuple]
        
        return count