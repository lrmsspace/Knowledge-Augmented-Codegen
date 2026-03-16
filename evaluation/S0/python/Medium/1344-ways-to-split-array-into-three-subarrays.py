# Source: https://leetcode.com/problems/ways-to-split-array-into-three-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# A split of an integer array is good if:
#
#
# 	The array is split into three non-empty contiguous subarrays - named left, mid, right respectively from left to right.
# 	The sum of the elements in left is less than or equal to the sum of the elements in mid, and the sum of the elements in mid is less than or equal to the sum of the elements in right.
#
#
# Given nums, an array of non-negative integers, return the number of good ways to split nums. As the number may be too large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,1,1]
# Output: 1
# Explanation: The only good way to split nums is [1] [1] [1].
#
# Constraints:
# 3 <= nums.length <= 105
# 	0 <= nums[i] <= 104
#

class Solution(object):
    def waysToSplit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(nums)
        prefix_sum = [0] * (n + 1)
        
        for i in range(n):
            prefix_sum[i + 1] = prefix_sum[i] + nums[i]
        
        total_ways = 0
        
        for i in range(1, n - 1):
            left_sum = prefix_sum[i]
            
            # Binary search for the minimum j such that prefix_sum[j] >= 2 * left_sum
            low, high = i + 1, n - 1
            while low < high:
                mid = (low + high) // 2
                if prefix_sum[mid] >= 2 * left_sum:
                    high = mid
                else:
                    low = mid + 1
            min_j = low
            
            # Binary search for the maximum j such that prefix_sum[j] <= (total_sum + left_sum) / 2
            low, high = i + 1, n - 1
            while low < high:
                mid = (low + high + 1) // 2
                if prefix_sum[mid] <= (prefix_sum[n] + left_sum) // 2:
                    low = mid
                else:
                    high = mid - 1
            max_j = low
            
            if min_j <= max_j:
                total_ways += max_j - min_j + 1
                total_ways %= MOD
        
        return total_ways