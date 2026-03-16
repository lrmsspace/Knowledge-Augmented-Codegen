# Source: https://leetcode.com/problems/n-repeated-element-in-size-2n-array/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums with the following properties:
#
#
# 	nums.length == 2 * n.
# 	nums contains n + 1 unique elements.
# 	Exactly one element of nums is repeated n times.
#
#
# Return the element that is repeated n times.
#
# Example:
# Input: nums = [1,2,3,3]
# Output: 3
#
# Constraints:
# 2 <= n <= 5000
# 	nums.length == 2 * n
# 	0 <= nums[i] <= 104
# 	nums contains n + 1 unique elements and one of them is repeated exactly n times.
#

class Solution(object):
    def repeatedNTimes(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = {}
        for num in nums:
            if num in count:
                return num
            count[num] = 1
        return -1