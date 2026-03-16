# Source: https://leetcode.com/problems/partition-equal-subset-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
#
# Example:
# Input: nums = [1,5,11,5]
# Output: true
# Explanation: The array can be partitioned as [1, 5, 5] and [11].
#
# Constraints:
# 1 <= nums.length <= 200
# 	1 <= nums[i] <= 100
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def canPartition(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        total_sum = sum(nums)
        if total_sum % 2 != 0:
            return False
        
        target = total_sum // 2
        n = len(nums)
        
        # Create a DP table where dp[i][j] indicates whether we can achieve sum j using the first i numbers
        dp = [[False] * (target + 1) for _ in range(n + 1)]
        
        # Base case: We can always achieve sum 0 with an empty subset
        for i in range(n + 1):
            dp[i][0] = True
        
        for i in range(1, n + 1):
            for j in range(1, target + 1):
                if nums[i - 1] > j:
                    dp[i][j] = dp[i - 1][j]
                else:
                    dp[i][j] = dp[i - 1][j] or dp[i - 1][j - nums[i - 1]]
        
        return dp[n][target]