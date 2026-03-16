# Source: https://leetcode.com/problems/minimum-falling-path-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
#
# A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
#
# Example:
# Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
# Output: 13
# Explanation: There are two falling paths with a minimum sum as shown.
#
# Constraints:
# n == matrix.length == matrix[i].length
# 	1 <= n <= 100
# 	-100 <= matrix[i][j] <= 100
#

class Solution(object):
    def minFallingPathSum(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        n = len(matrix)
        dp = [[0] * n for _ in range(n)]
        
        # Initialize the first row of dp with the first row of matrix
        for j in range(n):
            dp[0][j] = matrix[0][j]
        
        # Fill the dp table
        for i in range(1, n):
            for j in range(n):
                # Get the minimum path sum from the previous row
                min_above = dp[i-1][j]
                if j > 0:
                    min_above = min(min_above, dp[i-1][j-1])
                if j < n - 1:
                    min_above = min(min_above, dp[i-1][j+1])
                
                dp[i][j] = matrix[i][j] + min_above
        
        # The answer is the minimum value in the last row of dp
        return min(dp[n-1])