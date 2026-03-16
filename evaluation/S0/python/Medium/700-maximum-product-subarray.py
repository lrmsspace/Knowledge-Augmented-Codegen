# Source: https://leetcode.com/problems/maximum-product-subarray/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, find a subarray that has the largest product, and return the product.
#
# The test cases are generated so that the answer will fit in a 32-bit integer.
#
# Example:
# Input: nums = [2,3,-2,4]
# Output: 6
# Explanation: [2,3] has the largest product 6.
#
# Constraints:
# 1 <= nums.length <= 2 * 104
# 	-10 <= nums[i] <= 10
# 	The product of any subarray of nums is guaranteed to fit in a 32-bit integer.
#

class Solution(object):
    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0
        
        max_prod = min_prod = result = nums[0]
        
        for num in nums[1:]:
            if num < 0:
                max_prod, min_prod = min_prod, max_prod
            
            max_prod = max(num, max_prod * num)
            min_prod = min(num, min_prod * num)
            
            result = max(result, max_prod)
        
        return result