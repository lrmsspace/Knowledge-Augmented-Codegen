# Source: https://leetcode.com/problems/number-of-subarrays-with-gcd-equal-to-k/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and an integer k, return the number of subarrays of nums where the greatest common divisor of the subarray's elements is k.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# The greatest common divisor of an array is the largest integer that evenly divides all the array elements.
#
# Example:
# Input: nums = [9,3,1,2,6,3], k = 3
# Output: 4
# Explanation: The subarrays of nums where 3 is the greatest common divisor of all the subarray's elements are:
# - [9,3,1,2,6,3]
# - [9,3,1,2,6,3]
# - [9,3,1,2,6,3]
# - [9,3,1,2,6,3]
#
# Constraints:
# 1 <= nums.length <= 1000
# 	1 <= nums[i], k <= 109
#

class Solution(object):
    def subarrayGCD(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        from math import gcd
        count = 0
        n = len(nums)
        
        for i in range(n):
            current_gcd = 0
            for j in range(i, n):
                current_gcd = gcd(current_gcd, nums[j])
                if current_gcd == k:
                    count += 1
                elif current_gcd < k:
                    break
        
        return count