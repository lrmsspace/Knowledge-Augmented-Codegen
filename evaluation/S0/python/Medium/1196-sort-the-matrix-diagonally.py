# Source: https://leetcode.com/problems/sort-the-matrix-diagonally/   |   Difficulty: Medium
#
# Problem Description:
# A matrix diagonal is a diagonal line of cells starting from some cell in either the topmost row or leftmost column and going in the bottom-right direction until reaching the matrix's end. For example, the matrix diagonal starting from mat[2][0], where mat is a 6 x 3 matrix, includes cells mat[2][0], mat[3][1], and mat[4][2].
#
# Given an m x n matrix mat of integers, sort each matrix diagonal in ascending order and return the resulting matrix.
#
# Example:
# Input: mat = [[3,3,1,1],[2,2,1,2],[1,1,1,2]]
# Output: [[1,1,1,1],[1,2,2,2],[1,2,3,3]]
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 100
# 	1 <= mat[i][j] <= 100
#

class Solution(object):
    def diagonalSort(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: List[List[int]]
        """
        from collections import defaultdict
        import heapq

        diagonals = defaultdict(list)
        rows, cols = len(mat), len(mat[0])

        # Collect elements of each diagonal
        for r in range(rows):
            for c in range(cols):
                diagonals[r - c].append(mat[r][c])

        # Sort each diagonal
        for key in diagonals:
            heapq.heapify(diagonals[key])

        # Place sorted elements back into the matrix
        for r in range(rows):
            for c in range(cols):
                mat[r][c] = heapq.heappop(diagonals[r - c])

        return mat