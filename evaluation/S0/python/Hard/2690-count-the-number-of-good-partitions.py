# Source: https://leetcode.com/problems/count-the-number-of-good-partitions/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed array nums consisting of positive integers.
#
# A partition of an array into one or more contiguous subarrays is called good if no two subarrays contain the same number.
#
# Return the total number of good partitions of nums.
#
# Since the answer may be large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: 8
# Explanation: The 8 possible good partitions are: ([1], [2], [3], [4]), ([1], [2], [3,4]), ([1], [2,3], [4]), ([1], [2,3,4]), ([1,2], [3], [4]), ([1,2], [3,4]), ([1,2,3], [4]), and ([1,2,3,4]).
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def numberOfGoodPartitions(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        unique_nums = set(nums)
        m = len(unique_nums)

        if m < 2:
            return 0

        dp = [0] * (m + 1)
        dp[0] = 1

        for i in range(1, m + 1):
            dp[i] = (dp[i - 1] * (n - (i - 1))) % MOD

        total_partitions = pow(2, m - 1, MOD)
        return (total_partitions * dp[m]) % MOD