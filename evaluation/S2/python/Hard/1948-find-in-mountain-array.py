# Source: https://leetcode.com/problems/find-in-mountain-array/   |   Difficulty: Hard
#
# Problem Description:
# (This problem is an interactive problem.)
#
# You may recall that an array arr is a mountain array if and only if:
#
#
# 	arr.length >= 3
# 	There exists some i with 0 < i < arr.length - 1 such that:
# 	
# 		arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
# 		arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
# 	
# 	
#
#
# Given a mountain array mountainArr, return the minimum index such that mountainArr.get(index) == target. If such an index does not exist, return -1.
#
# You cannot access the mountain array directly. You may only access the array using a MountainArray interface:
#
#
# 	MountainArray.get(k) returns the element of the array at index k (0-indexed).
# 	MountainArray.length() returns the length of the array.
#
#
# Submissions making more than 100 calls to MountainArray.get will be judged Wrong Answer. Also, any solutions that attempt to circumvent the judge will result in disqualification.
#
# Example:
# Input: mountainArr = [1,2,3,4,5,3,1], target = 3
# Output: 2
# Explanation: 3 exists in the array, at index=2 and index=5. Return the minimum index, which is 2.
#
# Constraints:
# 3 <= mountainArr.length() <= 104
# 	0 <= target <= 109
# 	0 <= mountainArr.get(index) <= 109
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

# """
# This is MountainArray's API interface.
# You should not implement it, or speculate about its implementation
# """
            #class MountainArray(object):
#    def get(self, index):
#        """
#        :type index: int
#        :rtype int
#        """
#
#    def length(self):
#        """
#        :rtype int
#        """

class Solution(object):
    def findInMountainArray(self, target, mountainArr):
        """
        :type target: integer
        :type mountain_arr: MountainArray
        :rtype: integer
        """
        n = mountainArr.length()
        
        # Step 1: Find the peak index
        left, right = 0, n - 1
        while left < right:
            mid = (left + right) // 2
            if mountainArr.get(mid) < mountainArr.get(mid + 1):
                left = mid + 1
            else:
                right = mid
        
        peak_index = left
        
        # Step 2: Binary search in the ascending part
        left, right = 0, peak_index
        while left <= right:
            mid = (left + right) // 2
            value = mountainArr.get(mid)
            if value == target:
                return mid
            elif value < target:
                left = mid + 1
            else:
                right = mid - 1
        
        # Step 3: Binary search in the descending part
        left, right = peak_index, n - 1
        while left <= right:
            mid = (left + right) // 2
            value = mountainArr.get(mid)
            if value == target:
                return mid
            elif value > target:
                left = mid + 1
            else:
                right = mid - 1
        
        return -1