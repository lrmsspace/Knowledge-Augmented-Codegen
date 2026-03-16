# Source: https://leetcode.com/problems/maximum-product-of-two-elements-in-an-array/   |   Difficulty: Easy
#
# Problem Description:
# Given the array of integers nums, you will choose two different indices i and j of that array. Return the maximum value of (nums[i]-1)*(nums[j]-1).
#
# Example:
# Input: nums = [3,4,5,2]
# Output: 12 
# Explanation: If you choose the indices i=1 and j=2 (indexed from 0), you will get the maximum value, that is, (nums[1]-1)*(nums[2]-1) = (4-1)*(5-1) = 3*4 = 12.
#
# Constraints:
# 2 <= nums.length <= 500
# 	1 <= nums[i] <= 10^3
#

class Solution(object):
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max1 = max2 = 0
        for n in nums:
            if n > max1:
                max2 = max1
                max1 = n
            elif n > max2:
                max2 = n
        return (max1 - 1) * (max2 - 1)