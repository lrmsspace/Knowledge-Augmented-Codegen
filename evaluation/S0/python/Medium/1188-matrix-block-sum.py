# Source: https://leetcode.com/problems/matrix-block-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given a m x n matrix mat and an integer k, return a matrix answer where each answer[i][j] is the sum of all elements mat[r][c] for:
#
#
# 	i - k <= r <= i + k,
# 	j - k <= c <= j + k, and
# 	(r, c) is a valid position in the matrix.
#
# Example:
# Input: mat = [[1,2,3],[4,5,6],[7,8,9]], k = 1
# Output: [[12,21,16],[27,45,33],[24,39,28]]
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n, k <= 100
# 	1 <= mat[i][j] <= 100
#

class Solution(object):
    def matrixBlockSum(self, mat, k):
        """
        :type mat: List[List[int]]
        :type k: int
        :rtype: List[List[int]]
        """
        m, n = len(mat), len(mat[0])
        # Create prefix sum matrix
        prefix_sum = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                prefix_sum[i][j] = mat[i - 1][j - 1] + prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1]
        
        # Create the answer matrix
        answer = [[0] * n for _ in range(m)]
        
        for i in range(m):
            for j in range(n):
                r1 = max(0, i - k)
                c1 = max(0, j - k)
                r2 = min(m - 1, i + k)
                c2 = min(n - 1, j + k)
                
                answer[i][j] = prefix_sum[r2 + 1][c2 + 1] - prefix_sum[r1][c2 + 1] - prefix_sum[r2 + 1][c1] + prefix_sum[r1][c1]
        
        return answer