# Source: https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of size n.
#
# Consider a non-empty subarray from nums that has the maximum possible bitwise AND.
#
#
# 	In other words, let k be the maximum value of the bitwise AND of any subarray of nums. Then, only subarrays with a bitwise AND equal to k should be considered.
#
#
# Return the length of the longest such subarray.
#
# The bitwise AND of an array is the bitwise AND of all the numbers in it.
#
# A subarray is a contiguous sequence of elements within an array.
#
# Example:
# Input: nums = [1,2,3,3,2,2]
# Output: 2
# Explanation:
# The maximum possible bitwise AND of a subarray is 3.
# The longest subarray with that value is [3,3], so we return 2.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 106
#

class Solution(object):
    def longestSubarray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_and = max(nums)
        max_length = 0
        current_length = 0
        
        for num in nums:
            if num == max_and:
                current_length += 1
                max_length = max(max_length, current_length)
            else:
                current_length = 0
                
        return max_length