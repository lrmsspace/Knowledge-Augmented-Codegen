# Source: https://leetcode.com/problems/maximal-rectangle/   |   Difficulty: Hard
#
# Problem Description:
# Given a rows x cols binary matrix filled with 0's and 1's, find the largest rectangle containing only 1's and return its area.
#
# Example:
# Input: matrix = [["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]
# Output: 6
# Explanation: The maximal rectangle is shown in the above picture.
#
# Constraints:
# rows == matrix.length
# 	cols == matrix[i].length
# 	1 <= row, cols <= 200
# 	matrix[i][j] is '0' or '1'.
#

class Solution(object):
    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """
        if not matrix:
            return 0
        max_area = 0
        dp = [0] * len(matrix[0])
        
        for row in matrix:
            for j in range(len(row)):
                if row[j] == '1':
                    dp[j] += 1
                else:
                    dp[j] = 0
            
            stack = []
            for j in range(len(dp) + 1):
                height = dp[j] if j < len(dp) else 0
                while stack and height < dp[stack[-1]]:
                    h = dp[stack.pop()]
                    w = j if not stack else j - stack[-1] - 1
                    max_area = max(max_area, h * w)
                stack.append(j)
        
        return max_area