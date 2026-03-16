# Source: https://leetcode.com/problems/maximum-and-minimum-sums-of-at-most-size-k-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums and a positive integer k. Return the sum of the maximum and minimum elements of all subsequences of nums with at most k elements.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3], k = 2
#
# Output: 24
#
# Explanation:
#
# The subsequences of nums with at most 2 elements are:
#
#
# 	
# 		
# 			Subsequence 
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
# 			[1, 3]
# 			1
# 			3
# 			4
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
# 			24
# 		
# 	
#
#
# The output would be 24.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 109
# 	1 <= k <= min(70, nums.length)
#

class Solution(object):
    def minMaxSums(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        nums.sort()
        
        # Precompute powers of 2 up to n
        pow2 = [1] * (n + 1)
        for i in range(1, n + 1):
            pow2[i] = (pow2[i - 1] * 2) % MOD
        
        total_sum = 0
        
        for i in range(n):
            max_count = min(i, k - 1)
            min_count = min(n - i - 1, k - 1)
            
            if max_count >= 0:
                total_sum += nums[i] * pow2[max_count]
                total_sum %= MOD
            
            if min_count >= 0:
                total_sum += nums[i] * pow2[min_count]
                total_sum %= MOD
        
        return total_sum % MOD