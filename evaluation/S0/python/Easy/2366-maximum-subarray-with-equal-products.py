# Source: https://leetcode.com/problems/maximum-subarray-with-equal-products/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of positive integers nums.
#
# An array arr is called product equivalent if prod(arr) == lcm(arr) * gcd(arr), where:
#
#
# 	prod(arr) is the product of all elements of arr.
# 	gcd(arr) is the GCD of all elements of arr.
# 	lcm(arr) is the LCM of all elements of arr.
#
#
# Return the length of the longest product equivalent subarray of nums.
#
# Example:
# Input: nums = [1,2,1,2,1,1,1]
#
# Output: 5
#
# Explanation: 
#
# The longest product equivalent subarray is [1, 2, 1, 1, 1], where prod([1, 2, 1, 1, 1]) = 2, gcd([1, 2, 1, 1, 1]) = 1, and lcm([1, 2, 1, 1, 1]) = 2.
#
# Constraints:
# 2 <= nums.length <= 100
# 	1 <= nums[i] <= 10
#

class Solution(object):
    def maxLength(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_len = 1
        n = len(nums)
        
        for i in range(n):
            prod = 1
            gcd_val = nums[i]
            lcm_val = nums[i]
            
            for j in range(i, n):
                prod *= nums[j]
                gcd_val = self.gcd(gcd_val, nums[j])
                lcm_val = self.lcm(lcm_val, nums[j])
                
                if prod == gcd_val * lcm_val:
                    max_len = max(max_len, j - i + 1)
        
        return max_len