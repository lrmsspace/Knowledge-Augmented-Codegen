# Source: https://leetcode.com/problems/number-of-great-partitions/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array nums consisting of positive integers and an integer k.
#
# Partition the array into two ordered groups such that each element is in exactly one group. A partition is called great if the sum of elements of each group is greater than or equal to k.
#
# Return the number of distinct great partitions. Since the answer may be too large, return it modulo 109 + 7.
#
# Two partitions are considered distinct if some element nums[i] is in different groups in the two partitions.
#
# Example:
# Input: nums = [1,2,3,4], k = 4
# Output: 6
# Explanation: The great partitions are: ([1,2,3], [4]), ([1,3], [2,4]), ([1,4], [2,3]), ([2,3], [1,4]), ([2,4], [1,3]) and ([4], [1,2,3]).
#
# Constraints:
# 1 <= nums.length, k <= 1000
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def countPartitions(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        total_sum = sum(nums)

        if total_sum < 2 * k:
            return 0

        dp = [0] * (total_sum + 1)
        dp[0] = 1

        for num in nums:
            for j in range(total_sum, num - 1, -1):
                dp[j] = (dp[j] + dp[j - num]) % MOD

        invalid_partitions = sum(dp[:k]) % MOD
        valid_partitions = (pow(2, n, MOD) - 2 * invalid_partitions) % MOD

        return valid_partitions