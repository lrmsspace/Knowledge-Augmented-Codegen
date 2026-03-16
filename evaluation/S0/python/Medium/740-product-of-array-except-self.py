# Source: https://leetcode.com/problems/product-of-array-except-self/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].
#
# The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.
#
# You must write an algorithm that runs in O(n) time and without using the division operation.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: [24,12,8,6]
#
# Constraints:
# 2 <= nums.length <= 105
# 	-30 <= nums[i] <= 30
# 	The input is generated such that answer[i] is guaranteed to fit in a 32-bit integer.
#
#
#  
# Follow up: Can you solve the problem in O(1) extra space complexity? (The output array does not count as extra space for space complexity analysis.)
#

class Solution(object):
    def productExceptSelf(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        answer = [0]*n
        
        # Calculate left products
        left_product = 1
        for i in range(n):
            answer[i] = left_product
            left_product *= nums[i]
        
        # Calculate right products and multiply with left products
        right_product = 1
        for i in range(n-1, -1, -1):
            answer[i] *= right_product
            right_product *= nums[i]
        
        return answer