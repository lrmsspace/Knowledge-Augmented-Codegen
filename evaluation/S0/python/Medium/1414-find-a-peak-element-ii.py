# Source: https://leetcode.com/problems/find-a-peak-element-ii/   |   Difficulty: Medium
#
# Problem Description:
# A peak element in a 2D grid is an element that is strictly greater than all of its adjacent neighbors to the left, right, top, and bottom.
#
# Given a 0-indexed m x n matrix mat where no two adjacent cells are equal, find any peak element mat[i][j] and return the length 2 array [i,j].
#
# You may assume that the entire matrix is surrounded by an outer perimeter with the value -1 in each cell.
#
# You must write an algorithm that runs in O(m log(n)) or O(n log(m)) time.
#
# Example:
# Input: mat = [[1,4],[3,2]]
# Output: [0,1]
# Explanation: Both 3 and 4 are peak elements so [1,0] and [0,1] are both acceptable answers.
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 500
# 	1 <= mat[i][j] <= 105
# 	No two adjacent cells are equal.
#

class Solution(object):
    def findPeakGrid(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: List[int]
        """
        rows = len(mat)
        cols = len(mat[0])
        
        def findPeakInColumn(col):
            max_row = 0
            for row in range(rows):
                if mat[row][col] > mat[max_row][col]:
                    max_row = row
            return max_row
        
        left, right = 0, cols - 1
        
        while left <= right:
            mid_col = (left + right) // 2
            max_row = findPeakInColumn(mid_col)
            
            left_is_bigger = mid_col > 0 and mat[max_row][mid_col - 1] > mat[max_row][mid_col]
            right_is_bigger = mid_col < cols - 1 and mat[max_row][mid_col + 1] > mat[max_row][mid_col]
            
            if not left_is_bigger and not right_is_bigger:
                return [max_row, mid_col]
            elif right_is_bigger:
                left = mid_col + 1
            else:
                right = mid_col - 1
        
        return [-1, -1]  # This line should never be reached