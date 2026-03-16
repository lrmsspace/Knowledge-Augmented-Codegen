# Source: https://leetcode.com/problems/maximum-side-length-of-a-square-with-sum-less-than-or-equal-to-threshold/   |   Difficulty: Medium
#
# Problem Description:
# Given a m x n matrix mat and an integer threshold, return the maximum side-length of a square with a sum less than or equal to threshold or return 0 if there is no such square.
#
# Example:
# Input: mat = [[1,1,3,2,4,3,2],[1,1,3,2,4,3,2],[1,1,3,2,4,3,2]], threshold = 4
# Output: 2
# Explanation: The maximum side length of square with sum less than 4 is 2 as shown.
#
# Constraints:
# m == mat.length
# 	n == mat[i].length
# 	1 <= m, n <= 300
# 	0 <= mat[i][j] <= 104
# 	0 <= threshold <= 105
#

class Solution(object):
    def maxSideLength(self, mat, threshold):
        """
        :type mat: List[List[int]]
        :type threshold: int
        :rtype: int
        """
        m, n = len(mat), len(mat[0])
        prefix_sum = [[0] * (n + 1) for _ in range(m + 1)]
        
        for i in range(1, m + 1):
            for j in range(1, n + 1):
                prefix_sum[i][j] = mat[i - 1][j - 1] + prefix_sum[i - 1][j] + prefix_sum[i][j - 1] - prefix_sum[i - 1][j - 1]
        
        def can_find_square(side):
            for i in range(side, m + 1):
                for j in range(side, n + 1):
                    total = prefix_sum[i][j] - prefix_sum[i - side][j] - prefix_sum[i][j - side] + prefix_sum[i - side][j - side]
                    if total <= threshold:
                        return True
            return False
        
        left, right = 0, min(m, n)
        result = 0
        
        while left <= right:
            mid = (left + right) // 2
            if can_find_square(mid):
                result = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return result