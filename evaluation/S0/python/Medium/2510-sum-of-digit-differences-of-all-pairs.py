# Source: https://leetcode.com/problems/sum-of-digit-differences-of-all-pairs/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums consisting of positive integers where all integers have the same number of digits.
#
# The digit difference between two integers is the count of different digits that are in the same position in the two integers.
#
# Return the sum of the digit differences between all pairs of integers in nums.
#
# Example:
# Input: nums = [13,23,12]
#
# Output: 4
#
# Explanation:
# We have the following:
# - The digit difference between 13 and 23 is 1.
# - The digit difference between 13 and 12 is 1.
# - The digit difference between 23 and 12 is 2.
# So the total sum of digit differences between all pairs of integers is 1 + 1 + 2 = 4.
#
# Constraints:
# 2 <= nums.length <= 105
# 	1 <= nums[i] < 109
# 	All integers in nums have the same number of digits.
#

class Solution(object):
    def sumDigitDifferences(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        m = len(str(nums[0]))
        total_diff = 0
        
        for i in range(m):
            digit_count = [0] * 10
            
            for num in nums:
                digit = (num // (10 ** (m - i - 1))) % 10
                digit_count[digit] += 1
            
            for count in digit_count:
                total_diff += count * (n - count)
        
        return total_diff