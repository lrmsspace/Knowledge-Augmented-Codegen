# Source: https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed m x n integer matrix grid. The width of a column is the maximum length of its integers.
#
#
# 	For example, if grid = [[-10], [3], [12]], the width of the only column is 3 since -10 is of length 3.
#
#
# Return an integer array ans of size n where ans[i] is the width of the ith column.
#
# The length of an integer x with len digits is equal to len if x is non-negative, and len + 1 otherwise.
#
# Example:
# Input: grid = [[1],[22],[333]]
# Output: [3]
# Explanation: In the 0th column, 333 is of length 3.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 100 
# 	-109 <= grid[r][c] <= 109
#

class Solution(object):
    def findColumnWidth(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: List[int]
        """
        if not grid or not grid[0]:
            return []

        m, n = len(grid), len(grid[0])
        result = [0] * n

        for j in range(n):
            max_width = 0
            for i in range(m):
                num_length = len(str(grid[i][j]))
                max_width = max(max_width, num_length)
            result[j] = max_width

        return result