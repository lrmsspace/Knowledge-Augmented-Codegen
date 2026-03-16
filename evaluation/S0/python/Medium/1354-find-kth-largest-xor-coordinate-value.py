# Source: https://leetcode.com/problems/find-kth-largest-xor-coordinate-value/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D matrix of size m x n, consisting of non-negative integers. You are also given an integer k.
#
# The value of coordinate (a, b) of the matrix is the XOR of all matrix[i][j] where 0 <= i <= a < m and 0 <= j <= b < n (0-indexed).
#
# Find the kth largest value (1-indexed) of all the coordinates of matrix.
#
# Example:
# Input: matrix = [[5,2],[1,6]], k = 1
# Output: 7
# Explanation: The value of coordinate (0,1) is 5 XOR 2 = 7, which is the largest value.
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	1 <= m, n <= 1000
# 	0 <= matrix[i][j] <= 106
# 	1 <= k <= m * n
#

class Solution(object):
    def kthLargestValue(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        m, n = len(matrix), len(matrix[0])
        xor_matrix = [[0] * n for _ in range(m)]
        xor_values = []

        for i in range(m):
            for j in range(n):
                top = xor_matrix[i-1][j] if i > 0 else 0
                left = xor_matrix[i][j-1] if j > 0 else 0
                top_left = xor_matrix[i-1][j-1] if i > 0 and j > 0 else 0

                xor_matrix[i][j] = matrix[i][j] ^ top ^ left ^ top_left
                xor_values.append(xor_matrix[i][j])

        xor_values.sort(reverse=True)
        return xor_values[k-1]