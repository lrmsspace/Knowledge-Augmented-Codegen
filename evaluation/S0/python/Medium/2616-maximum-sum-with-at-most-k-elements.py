# Source: https://leetcode.com/problems/maximum-sum-with-at-most-k-elements/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D integer matrix grid of size n x m, an integer array limits of length n, and an integer k. The task is to find the maximum sum of at most k elements from the matrix grid such that:
#
#
# 	
# 	The number of elements taken from the ith row of grid does not exceed limits[i].
# 	
#
#
# Return the maximum sum.
#
# Example:
# Input: grid = [[1,2],[3,4]], limits = [1,2], k = 2
#
# Output: 7
#
# Explanation:
#
#
# 	From the second row, we can take at most 2 elements. The elements taken are 4 and 3.
# 	The maximum possible sum of at most 2 selected elements is 4 + 3 = 7.
#
# Constraints:
# n == grid.length == limits.length
# 	m == grid[i].length
# 	1 <= n, m <= 500
# 	0 <= grid[i][j] <= 105
# 	0 <= limits[i] <= m
# 	0 <= k <= min(n * m, sum(limits))
#

class Solution(object):
    def maxSum(self, grid, limits, k):
        """
        :type grid: List[List[int]]
        :type limits: List[int]
        :type k: int
        :rtype: int
        """
        n = len(grid)
        m = len(grid[0])
        
        # Precompute prefix sums for each row
        prefix_sums = []
        for i in range(n):
            row = sorted(grid[i], reverse=True)
            limit = limits[i]
            prefix = [0]
            for j in range(min(limit, m)):
                prefix.append(prefix[-1] + row[j])
            prefix_sums.append(prefix)
        
        # DP array to store maximum sums
        dp = [0] * (k + 1)
        
        for i in range(n):
            limit = limits[i]
            new_dp = dp[:]
            for taken in range(1, min(limit, m) + 1):
                sum_taken = prefix_sums[i][taken]
                for j in range(k, taken - 1, -1):
                    new_dp[j] = max(new_dp[j], dp[j - taken] + sum_taken)
            dp = new_dp
        
        return dp[k]