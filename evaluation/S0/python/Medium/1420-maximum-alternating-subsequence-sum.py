# Source: https://leetcode.com/problems/maximum-alternating-subsequence-sum/   |   Difficulty: Medium
#
# Problem Description:
# The alternating sum of a 0-indexed array is defined as the sum of the elements at even indices minus the sum of the elements at odd indices.
#
#
# 	For example, the alternating sum of [4,2,5,3] is (4 + 5) - (2 + 3) = 4.
#
#
# Given an array nums, return the maximum alternating sum of any subsequence of nums (after reindexing the elements of the subsequence).
#
#
#
#
# A subsequence of an array is a new array generated from the original array by deleting some elements (possibly none) without changing the remaining elements' relative order. For example, [2,7,4] is a subsequence of [4,2,3,7,2,1,4] (the underlined elements), while [2,4,2] is not.
#
# Example:
# Input: nums = [4,2,5,3]
# Output: 7
# Explanation: It is optimal to choose the subsequence [4,2,5] with alternating sum (4 + 5) - 2 = 7.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 105
#

class Solution(object):

    def maxAlternatingSum(self, nums):

        """

        :type nums: List[int]

        :rtype: int

        """
        even_sum = nums[0]
        odd_sum = 0

        for i in range(1, len(nums)):
            even_sum, odd_sum = max(even_sum, odd_sum + nums[i]), max(odd_sum, even_sum - nums[i])

        return even_sum