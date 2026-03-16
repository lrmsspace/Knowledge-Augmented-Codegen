# Source: https://leetcode.com/problems/partition-array-for-maximum-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.
#
# Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.
#
# Example:
# Input: arr = [1,15,7,9,2,5,10], k = 3
# Output: 84
# Explanation: arr becomes [15,15,15,9,10,10,10]
#
# Constraints:
# 1 <= arr.length <= 500
# 	0 <= arr[i] <= 109
# 	1 <= k <= arr.length
#

class Solution(object):
    def maxSumAfterPartitioning(self, arr, k):
        """
        :type arr: List[int]
        :type k: int
        :rtype: int
        """
        n = len(arr)
        dp = [0] * (n + 1)

        for i in range(1, n + 1):
            max_val = 0
            for j in range(1, min(k, i) + 1):
                max_val = max(max_val, arr[i - j])
                dp[i] = max(dp[i], dp[i - j] + max_val * j)

        return dp[n]