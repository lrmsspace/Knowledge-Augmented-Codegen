# Source: https://leetcode.com/problems/arithmetic-slices-ii-subsequence/   |   Difficulty: Hard
#
# Problem Description:
# Given an integer array nums, return the number of all the arithmetic subsequences of nums.
#
# A sequence of numbers is called arithmetic if it consists of at least three elements and if the difference between any two consecutive elements is the same.
#
#
# 	For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are arithmetic sequences.
# 	For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.
#
#
# A subsequence of an array is a sequence that can be formed by removing some elements (possibly none) of the array.
#
#
# 	For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].
#
#
# The test cases are generated so that the answer fits in 32-bit integer.
#
# Example:
# Input: nums = [2,4,6,8,10]
# Output: 7
# Explanation: All arithmetic subsequence slices are:
# [2,4,6]
# [4,6,8]
# [6,8,10]
# [2,4,6,8]
# [4,6,8,10]
# [2,4,6,8,10]
# [2,6,10]
#
# Constraints:
# 1  <= nums.length <= 1000
# 	-231 <= nums[i] <= 231 - 1
#

class Solution(object):
    def numberOfArithmeticSlices(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict

        n = len(nums)
        dp = [defaultdict(int) for _ in range(n)]
        total_count = 0

        for i in range(n):
            for j in range(i):
                diff = nums[i] - nums[j]
                count_at_j = dp[j][diff]
                dp[i][diff] += count_at_j + 1
                total_count += count_at_j

        return total_count