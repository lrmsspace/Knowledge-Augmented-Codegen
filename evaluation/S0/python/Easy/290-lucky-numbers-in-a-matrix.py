# Source: https://leetcode.com/problems/lucky-numbers-in-a-matrix/   |   Difficulty: Easy
#
# Problem Description:
# Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
#
# A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
#
# Example:
# Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
# Output: [15]
# Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= n, m <= 50
# 	1 <= matrix[i][j] <= 105.
# 	All elements in the matrix are distinct.
#

class Solution(object):
    def luckyNumbers(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """
        lucky_numbers = []
        rows = len(matrix)
        cols = len(matrix[0]) if rows > 0 else 0

        for i in range(rows):
            # Find the minimum element in the current row
            min_row_value = min(matrix[i])
            min_col_index = matrix[i].index(min_row_value)

            # Check if this minimum element is the maximum in its column
            is_lucky = True
            for j in range(rows):
                if matrix[j][min_col_index] > min_row_value:
                    is_lucky = False
                    break

            if is_lucky:
                lucky_numbers.append(min_row_value)

        return lucky_numbers