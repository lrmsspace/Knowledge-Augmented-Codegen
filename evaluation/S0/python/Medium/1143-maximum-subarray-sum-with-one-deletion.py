# Source: https://leetcode.com/problems/maximum-subarray-sum-with-one-deletion/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers, return the maximum sum for a non-empty subarray (contiguous elements) with at most one element deletion. In other words, you want to choose a subarray and optionally delete one element from it so that there is still at least one element left and the sum of the remaining elements is maximum possible.
#
# Note that the subarray needs to be non-empty after deleting one element.
#
# Example:
# Input: arr = [1,-2,0,3]
# Output: 4
# Explanation: Because we can choose [1, -2, 0, 3] and drop -2, thus the subarray [1, 0, 3] becomes the maximum value.
#
# Constraints:
# 1 <= arr.length <= 105
# 	-104 <= arr[i] <= 104
#

class Solution(object):
    def maximumSum(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        if n == 1:
            return arr[0]
        
        # dp[i][0] means max sum subarray ending at i with no deletion
        # dp[i][1] means max sum subarray ending at i with one deletion
        dp = [[0]*2 for _ in range(n)]
        
        dp[0][0] = arr[0]
        dp[0][1] = float('-inf')
        
        max_sum = arr[0]
        
        for i in range(1, n):
            dp[i][0] = max(dp[i-1][0] + arr[i], arr[i])
            dp[i][1] = max(dp[i-1][1] + arr[i], dp[i-1][0])
            max_sum = max(max_sum, dp[i][0], dp[i][1])
        
        return max_sum