# Source: https://leetcode.com/problems/sum-of-good-subsequences/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums. A good subsequence is defined as a subsequence of nums where the absolute difference between any two consecutive elements in the subsequence is exactly 1.
#
# Return the sum of all possible good subsequences of nums.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Note that a subsequence of size 1 is considered good by definition.
#
# Example:
# Input: nums = [1,2,1]
#
# Output: 14
#
# Explanation:
#
#
# 	Good subsequences are: [1], [2], [1], [1,2], [2,1], [1,2,1].
# 	The sum of elements in these subsequences is 14.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 105
#

class Solution(object):
    def sumOfGoodSubsequences(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        max_num = max(nums)
        count = [0] * (max_num + 1)

        for num in nums:
            count[num] += 1

        dp = [0] * (max_num + 1)

        for i in range(max_num + 1):
            dp[i] = (count[i] * (pow(2, count[i] - 1, MOD) if count[i] > 0 else 1)) % MOD
            if i > 0:
                dp[i] = (dp[i] + dp[i - 1] * (pow(2, count[i], MOD) - 1)) % MOD
            if i < max_num:
                dp[i] = (dp[i] + dp[i + 1] * (pow(2, count[i], MOD) - 1)) % MOD

        return sum(dp) % MOD