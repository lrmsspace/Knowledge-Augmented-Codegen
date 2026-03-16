# Source: https://leetcode.com/problems/max-sum-of-rectangle-no-larger-than-k/   |   Difficulty: Hard
#
# Problem Description:
# Given an m x n matrix matrix and an integer k, return the max sum of a rectangle in the matrix such that its sum is no larger than k.
#
# It is guaranteed that there will be a rectangle with a sum no larger than k.
#
# Example:
# Input: matrix = [[1,0,1],[0,-2,3]], k = 2
# Output: 2
# Explanation: Because the sum of the blue rectangle [[0, 1], [-2, 3]] is 2, and 2 is the max number no larger than k (k = 2).
#
# Constraints:
# m == matrix.length
# 	n == matrix[i].length
# 	1 <= m, n <= 100
# 	-100 <= matrix[i][j] <= 100
# 	-105 <= k <= 105
#
#
#  
# Follow up: What if the number of rows is much larger than the number of columns?
#

class Solution(object):
    def maxSumSubmatrix(self, matrix, k):
        """
        :type matrix: List[List[int]]
        :type k: int
        :rtype: int
        """
        import bisect
        m, n = len(matrix), len(matrix[0])
        res = float('-inf')
        
        for left in range(n):
            row_sums = [0] * m
            for right in range(left, n):
                for i in range(m):
                    row_sums[i] += matrix[i][right]
                
                cum_set = [0]
                cum_sum = 0
                for sum_ in row_sums:
                    cum_sum += sum_
                    target = cum_sum - k
                    idx = bisect.bisect_left(cum_set, target)
                    if idx < len(cum_set):
                        res = max(res, cum_sum - cum_set[idx])
                    bisect.insort(cum_set, cum_sum)
        
        return res