# Source: https://leetcode.com/problems/maximum-sum-of-two-non-overlapping-subarrays/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums and two integers firstLen and secondLen, return the maximum sum of elements in two non-overlapping subarrays with lengths firstLen and secondLen.
#
# The array with length firstLen could occur before or after the array with length secondLen, but they have to be non-overlapping.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [0,6,5,2,2,5,1,9,4], firstLen = 1, secondLen = 2
# Output: 20
# Explanation: One choice of subarrays is [9] with length 1, and [6,5] with length 2.
#
# Constraints:
# 1 <= firstLen, secondLen <= 1000
# 	2 <= firstLen + secondLen <= 1000
# 	firstLen + secondLen <= nums.length <= 1000
# 	0 <= nums[i] <= 1000
#

class Solution(object):
    def maxSumTwoNoOverlap(self, nums, firstLen, secondLen):
        """
        :type nums: List[int]
        :type firstLen: int
        :type secondLen: int
        :rtype: int
        """
        n = len(nums)
        
        def maxSum(firstLen, secondLen):
            max_first = sum(nums[:firstLen])
            current_first = max_first
            max_total = 0
            
            for i in range(firstLen, n - secondLen + 1):
                current_first += nums[i] - nums[i - firstLen]
                if i >= firstLen + secondLen - 1:
                    max_first = max(max_first, current_first)
                
                if i >= firstLen - 1:
                    current_second = sum(nums[i + 1:i + 1 + secondLen])
                    max_total = max(max_total, max_first + current_second)
            
            return max_total
        
        return max(maxSum(firstLen, secondLen), maxSum(secondLen, firstLen))