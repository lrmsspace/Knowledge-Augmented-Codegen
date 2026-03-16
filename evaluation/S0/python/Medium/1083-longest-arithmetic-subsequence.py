# Source: https://leetcode.com/problems/longest-arithmetic-subsequence/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums of integers, return the length of the longest arithmetic subsequence in nums.
#
# Note that:
#
#
# 	A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
# 	A sequence seq is arithmetic if seq[i + 1] - seq[i] are all the same value (for 0 <= i < seq.length - 1).
#
# Example:
# Input: nums = [3,6,9,12]
# Output: 4
# Explanation:  The whole array is an arithmetic sequence with steps of length = 3.
#
# Constraints:
# 2 <= nums.length <= 1000
# 	0 <= nums[i] <= 500
#

class Solution(object):
    def longestArithSeqLength(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n <= 2:
            return n

        dp = [{} for _ in range(n)]
        max_length = 2

        for i in range(n):
            for j in range(i):
                diff = nums[i] - nums[j]
                if diff in dp[j]:
                    dp[i][diff] = dp[j][diff] + 1
                else:
                    dp[i][diff] = 2
                max_length = max(max_length, dp[i][diff])

        return max_length