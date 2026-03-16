# Source: https://leetcode.com/problems/count-submatrices-with-all-ones/   |   Difficulty: Medium
#
# Problem Description:
# Given an m x n binary matrix mat, return the number of submatrices that have all ones.
#
# Example:
# Input: mat = [[1,0,1],[1,1,0],[1,1,0]]
# Output: 13
# Explanation: 
# There are 6 rectangles of side 1x1.
# There are 2 rectangles of side 1x2.
# There are 3 rectangles of side 2x1.
# There is 1 rectangle of side 2x2. 
# There is 1 rectangle of side 3x1.
# Total number of rectangles = 6 + 2 + 3 + 1 + 1 = 13.
#
# Constraints:
# 1 <= m, n <= 150
# 	mat[i][j] is either 0 or 1.
#

class Solution(object):
    def numSubmat(self, mat):
        """
        :type mat: List[List[int]]
        :rtype: int
        """
        m, n = len(mat), len(mat[0])
        height = [0] * n
        result = 0

        for i in range(m):
            for j in range(n):
                if mat[i][j] == 1:
                    height[j] += 1
                else:
                    height[j] = 0

            for j in range(n):
                min_height = height[j]
                for k in range(j, -1, -1):
                    if height[k] == 0:
                        break
                    min_height = min(min_height, height[k])
                    result += min_height

        return result