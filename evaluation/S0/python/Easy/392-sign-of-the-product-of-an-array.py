# Source: https://leetcode.com/problems/sign-of-the-product-of-an-array/   |   Difficulty: Easy
#
# Problem Description:
# Implement a function signFunc(x) that returns:
#
#
# 	1 if x is positive.
# 	-1 if x is negative.
# 	0 if x is equal to 0.
#
#
# You are given an integer array nums. Let product be the product of all values in the array nums.
#
# Return signFunc(product).
#
# Example:
# Input: nums = [-1,-2,-3,-4,3,2,1]
# Output: 1
# Explanation: The product of all values in the array is 144, and signFunc(144) = 1
#
# Constraints:
# 1 <= nums.length <= 1000
# 	-100 <= nums[i] <= 100
#

class Solution(object):
    def arraySign(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        negative_count = 0
        for num in nums:
            if num == 0:
                return 0
            elif num < 0:
                negative_count += 1
        return 1 if negative_count % 2 == 0 else -1