# Source: https://leetcode.com/problems/longest-strictly-increasing-or-strictly-decreasing-subarray/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of integers nums. Return the length of the longest subarray of nums which is either strictly increasing or strictly decreasing.
#
# Example:
# Input: nums = [1,4,3,3,2]
#
# Output: 2
#
# Explanation:
#
# The strictly increasing subarrays of nums are [1], [2], [3], [3], [4], and [1,4].
#
# The strictly decreasing subarrays of nums are [1], [2], [3], [3], [4], [3,2], and [4,3].
#
# Hence, we return 2.
#
# Constraints:
# 1 <= nums.length <= 50
# 	1 <= nums[i] <= 50
#

class Solution(object):
    def longestMonotonicSubarray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        if n == 0:
            return 0
        
        max_length = 1
        inc_length = 1
        dec_length = 1
        
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                inc_length += 1
                dec_length = 1
            elif nums[i] < nums[i - 1]:
                dec_length += 1
                inc_length = 1
            else:
                inc_length = 1
                dec_length = 1
            
            max_length = max(max_length, inc_length, dec_length)
        
        return max_length