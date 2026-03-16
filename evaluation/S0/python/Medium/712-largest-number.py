# Source: https://leetcode.com/problems/largest-number/   |   Difficulty: Medium
#
# Problem Description:
# Given a list of non-negative integers nums, arrange them such that they form the largest number and return it.
#
# Since the result may be very large, so you need to return a string instead of an integer.
#
# Example:
# Input: nums = [10,2]
# Output: "210"
#
# Constraints:
# 1 <= nums.length <= 100
# 	0 <= nums[i] <= 109
#

class Solution(object):
    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """
        from functools import cmp_to_key

        def compare(x, y):
            if x + y > y + x:
                return -1
            elif x + y < y + x:
                return 1
            else:
                return 0

        str_nums = list(map(str, nums))
        str_nums.sort(key=cmp_to_key(compare))
        largest_num = ''.join(str_nums)

        # Handle the case where the result is multiple leading zeros
        return '0' if largest_num[0] == '0' else largest_num