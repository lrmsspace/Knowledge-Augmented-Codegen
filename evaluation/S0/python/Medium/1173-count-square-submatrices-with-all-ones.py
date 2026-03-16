# Source: https://leetcode.com/problems/count-square-submatrices-with-all-ones/   |   Difficulty: Medium
#
# Problem Description:
# Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
#
# Example:
# Input: matrix =
# [
#   [0,1,1,1],
#   [1,1,1,1],
#   [0,1,1,1]
# ]
# Output: 15
# Explanation: 
# There are 10 squares of side 1.
# There are 4 squares of side 2.
# There is  1 square of side 3.
# Total number of squares = 10 + 4 + 1 = 15.
#
# Constraints:
# 1 <= arr.length <= 300
# 	1 <= arr[0].length <= 300
# 	0 <= arr[i][j] <= 1
#

class Solution(object):
    def countSquares(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        if not matrix or not matrix[0]:
            return 0
        
        rows, cols = len(matrix), len(matrix[0])
        dp = [[0] * cols for _ in range(rows)]
        total_squares = 0
        
        for i in range(rows):
            for j in range(cols):
                if matrix[i][j] == 1:
                    if i == 0 or j == 0:
                        dp[i][j] = 1
                    else:
                        dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1
                    total_squares += dp[i][j]
        
        return total_squares