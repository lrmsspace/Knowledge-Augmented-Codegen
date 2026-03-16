# Source: https://leetcode.com/problems/length-of-the-longest-subsequence-that-sums-to-target/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of integers nums, and an integer target.
#
# Return the length of the longest subsequence of nums that sums up to target. If no such subsequence exists, return -1.
#
# A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
#
# Example:
# Input: nums = [1,2,3,4,5], target = 9
# Output: 3
# Explanation: There are 3 subsequences with a sum equal to 9: [4,5], [1,3,5], and [2,3,4]. The longest subsequences are [1,3,5], and [2,3,4]. Hence, the answer is 3.
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i] <= 1000
# 	1 <= target <= 1000
#

class Solution(object):
    def lengthOfLongestSubsequence(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        n = len(nums)
        dp = [[-1] * (target + 1) for _ in range(n + 1)]
        dp[0][0] = 0

        for i in range(1, n + 1):
            for j in range(target + 1):
                dp[i][j] = dp[i - 1][j]
                if j >= nums[i - 1] and dp[i - 1][j - nums[i - 1]] != -1:
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - nums[i - 1]] + 1)

        return dp[n][target]