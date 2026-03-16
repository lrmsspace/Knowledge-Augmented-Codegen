# Source: https://leetcode.com/problems/maximum-strictly-increasing-cells-in-a-matrix/   |   Difficulty: Hard
#
# Problem Description:
# Given a 1-indexed m x n integer matrix mat, you can select any cell in the matrix as your starting cell.
#
# From the starting cell, you can move to any other cell in the same row or column, but only if the value of the destination cell is strictly greater than the value of the current cell. You can repeat this process as many times as possible, moving from cell to cell until you can no longer make any moves.
#
# Your task is to find the maximum number of cells that you can visit in the matrix by starting from some cell.
#
# Return an integer denoting the maximum number of cells that can be visited.
#
# Example:
# Input: mat = [[3,1],[3,4]]
# Output: 2
# Explanation: The image shows how we can visit 2 cells starting from row 1, column 2. It can be shown that we cannot visit more than 2 cells no matter where we start from, so the answer is 2.
#
# Constraints:
# m == mat.length 
# 	n == mat[i].length 
# 	1 <= m, n <= 105
# 	1 <= m * n <= 105
# 	-105 <= mat[i][j] <= 105
#

class Solution(object):
    def maxIncreasingCells(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: int
        """
        from collections import defaultdict
        import bisect

        m, n = len(mat), len(mat[0])
        value_cells = defaultdict(list)
        for i in range(m):
            for j in range(n):
                value_cells[mat[i][j]].append((i, j))

        row_max = [0] * m
        col_max = [0] * n
        result = 0

        for value in sorted(value_cells.keys()):
            updates = []
            for i, j in value_cells[value]:
                length = max(row_max[i], col_max[j]) + 1
                updates.append((i, j, length))
                result = max(result, length)

            for i, j, length in updates:
                row_max[i] = max(row_max[i], length)
                col_max[j] = max(col_max[j], length)

        return result