# Source: https://leetcode.com/problems/largest-submatrix-with-rearrangements/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
#
# Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.
#
# Example:
# Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
# Output: 4
# Explanation: You can rearrange the columns as shown above.
# The largest submatrix of 1s, in bold, has an area of 4.
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	1 <= m * n <= 105
# 	matrix[i][j] is either 0 or 1.
#

class Solution(object):
    def largestSubmatrix(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        if not matrix or not matrix[0]:
            return 0
        
        m, n = len(matrix), len(matrix[0])
        height = [0] * n
        max_area = 0
        
        for i in range(m):
            for j in range(n):
                if matrix[i][j] == 1:
                    height[j] += 1
                else:
                    height[j] = 0
            
            sorted_height = sorted(height, reverse=True)
            for j in range(n):
                max_area = max(max_area, sorted_height[j] * (j + 1))
        
        return max_area