# Source: https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n binary matrix matrix.
#
# You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from 0 to 1 or vice versa).
#
# Return the maximum number of rows that have all values equal after some number of flips.
#
# Example:
# Input: matrix = [[0,1],[1,1]]
# Output: 1
# Explanation: After flipping no values, 1 row has all values equal.
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	1 <= m, n <= 300
# 	matrix[i][j] is either 0 or 1.
#

class Solution(object):
    def maxEqualRowsAfterFlips(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        pattern_count = {}
        
        for row in matrix:
            # Create a pattern based on the first element of the row
            if row[0] == 0:
                pattern = tuple(row)
            else:
                pattern = tuple(1 - bit for bit in row)
            
            if pattern in pattern_count:
                pattern_count[pattern] += 1
            else:
                pattern_count[pattern] = 1
        
        return max(pattern_count.values())