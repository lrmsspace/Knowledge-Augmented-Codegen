# Source: https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.
#
# A subarray of an array is a consecutive sequence of zero or more values taken out of that array.
#
# Return the maximum length of a subarray with positive product.
#
# Example:
# Input: nums = [1,-2,-3,4]
# Output: 4
# Explanation: The array nums already has a positive product of 24.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
#

class Solution(object):
    def getMaxLen(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_length = 0
        positive_length = 0
        negative_length = 0

        for num in nums:
            if num > 0:
                positive_length += 1
                negative_length = negative_length + 1 if negative_length > 0 else 0
            elif num < 0:
                new_positive_length = negative_length + 1 if negative_length > 0 else 0
                new_negative_length = positive_length + 1
                positive_length, negative_length = new_positive_length, new_negative_length
            else:
                positive_length = 0
                negative_length = 0

            max_length = max(max_length, positive_length)

        return max_length