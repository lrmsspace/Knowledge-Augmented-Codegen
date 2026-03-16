# Source: https://leetcode.com/problems/largest-sum-of-averages/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and an integer k. You can partition the array into at most k non-empty adjacent subarrays. The score of a partition is the sum of the averages of each subarray.
#
# Note that the partition must use every integer in nums, and that the score is not necessarily an integer.
#
# Return the maximum score you can achieve of all the possible partitions. Answers within 10-6 of the actual answer will be accepted.
#
# Example:
# Input: nums = [9,1,2,3,9], k = 3
# Output: 20.00000
# Explanation: 
# The best choice is to partition nums into [9], [1, 2, 3], [9]. The answer is 9 + (1 + 2 + 3) / 3 + 9 = 20.
# We could have also partitioned nums into [9, 1], [2], [3, 9], for example.
# That partition would lead to a score of 5 + 2 + 6 = 13, which is worse.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 104
# 	1 <= k <= nums.length
#

class Solution(object):
    def largestSumOfAverages(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: float
        """
        n = len(nums)
        prefix_sum = [0] * (n + 1)
        
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        dp = [[0] * (k + 1) for _ in range(n + 1)]
        
        for i in range(1, n + 1):
            dp[i][1] = prefix_sum[i] / i
        
        for j in range(2, k + 1):
            for i in range(j, n + 1):
                for p in range(j - 1, i):
                    dp[i][j] = max(dp[i][j], dp[p][j - 1] + (prefix_sum[i] - prefix_sum[p]) / (i - p))
        
        return dp[n][k]