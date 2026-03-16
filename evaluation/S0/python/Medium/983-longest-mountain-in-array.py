# Source: https://leetcode.com/problems/longest-mountain-in-array/   |   Difficulty: Medium
#
# Problem Description:
# You may recall that an array arr is a mountain array if and only if:
#
#
# 	arr.length >= 3
# 	There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
# 	
# 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
# 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
# 	
# 	
#
#
# Given an integer array arr, return the length of the longest subarray, which is a mountain. Return 0 if there is no mountain subarray.
#
# Example:
# Input: arr = [2,1,4,7,3,2,5]
# Output: 5
# Explanation: The largest mountain is [1,4,7,3,2] which has length 5.
#
# Constraints:
# 1 <= arr.length <= 104
# 	0 <= arr[i] <= 104
#
#
#  
# Follow up:
#
#
# 	Can you solve it using only one pass?
# 	Can you solve it in O(1) space?
#

class Solution(object):
    def longestMountain(self, arr):
        """
        :type arr: List[int]
        :rtype: int
        """
        n = len(arr)
        longest = 0
        i = 1
        
        while i < n - 1:
            if arr[i] > arr[i - 1] and arr[i] > arr[i + 1]:
                left = i - 1
                right = i + 1
                
                while left > 0 and arr[left] > arr[left - 1]:
                    left -= 1
                
                while right < n - 1 and arr[right] > arr[right + 1]:
                    right += 1
                
                current_length = right - left + 1
                longest = max(longest, current_length)
                i = right
            else:
                i += 1
        
        return longest