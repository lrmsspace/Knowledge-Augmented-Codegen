# Source: https://leetcode.com/problems/longest-subsequence-with-decreasing-adjacent-difference/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of integers nums.
#
# Your task is to find the length of the longest subsequence seq of nums, such that the absolute differences between consecutive elements form a non-increasing sequence of integers. In other words, for a subsequence seq0, seq1, seq2, ..., seqm of nums, |seq1 - seq0| >= |seq2 - seq1| >= ... >= |seqm - seqm - 1|.
#
# Return the length of such a subsequence.
#
# Example:
# Input: nums = [16,6,3]
#
# Output: 3
#
# Explanation: 
#
# The longest subsequence is [16, 6, 3] with the absolute adjacent differences [10, 3].
#
# Constraints:
# 2 <= nums.length <= 104
# 	1 <= nums[i] <= 300
#

class Solution(object):
    def longestSubsequence(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        dp = [1] * n
        diff = [float('inf')] * n

        for i in range(n):
            for j in range(i):
                curr_diff = abs(nums[i] - nums[j])
                if curr_diff <= diff[j]:
                    if dp[j] + 1 > dp[i]:
                        dp[i] = dp[j] + 1
                        diff[i] = curr_diff
                    elif dp[j] + 1 == dp[i]:
                        diff[i] = min(diff[i], curr_diff)

        return max(dp)