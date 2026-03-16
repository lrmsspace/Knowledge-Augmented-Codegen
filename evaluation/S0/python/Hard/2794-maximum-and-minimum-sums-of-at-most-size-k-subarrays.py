# Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subarrays/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subarrays with at most k elements.
#
# Example:
# Input: nums = [1,2,3], k = 2
#
# Output: 20
#
# Explanation:
#
# The subarrays of nums with at most 2 elements are:
#
#
# 	
# 		
# 			Subarray
# 			Minimum
# 			Maximum
# 			Sum
# 		
# 		
# 			[1]
# 			1
# 			1
# 			2
# 		
# 		
# 			[2]
# 			2
# 			2
# 			4
# 		
# 		
# 			[3]
# 			3
# 			3
# 			6
# 		
# 		
# 			[1, 2]
# 			1
# 			2
# 			3
# 		
# 		
# 			[2, 3]
# 			2
# 			3
# 			5
# 		
# 		
# 			Final Total
# 			 
# 			 
# 			20
# 		
# 	
#
#
# The output would be 20.
#
# Constraints:
# 1 <= nums.length <= 80000
# 	1 <= k <= nums.length
# 	-106 <= nums[i] <= 106
#

class Solution(object):
    def minMaxSubarraySum(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        n = len(nums)
        total_sum = 0

        for size in range(1, k + 1):
            for i in range(n - size + 1):
                subarray = nums[i:i + size]
                total_sum += min(subarray) + max(subarray)

        return total_sum