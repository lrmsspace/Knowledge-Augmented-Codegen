# Source: https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of integers nums sorted in non-decreasing order, find the starting and ending position of a given target value.
#
# If target is not found in the array, return [-1, -1].
#
# You must write an algorithm with O(log n) runtime complexity.
#
# Example:
# Input: nums = [5,7,7,8,8,10], target = 8
# Output: [3,4]
#
# Constraints:
# 0 <= nums.length <= 105
# 	-109 <= nums[i] <= 109
# 	nums is a non-decreasing array.
# 	-109 <= target <= 109
#

class Solution(object):
    def searchRange(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        def findFirst(nums, target):
            left, right = 0, len(nums) - 1
            first = -1
            while left <= right:
                mid = left + (right - left) // 2
                if nums[mid] == target:
                    first = mid
                    right = mid - 1
                elif nums[mid] < target:
                    left = mid + 1
                else:
                    right = mid - 1
            return first

        def findLast(nums, target):
            left, right = 0, len(nums) - 1
            last = -1
            while left <= right:
                mid = left + (right - left) // 2
                if nums[mid] == target:
                    last = mid
                    left = mid + 1
                elif nums[mid] < target:
                    left = mid + 1
                else:
                    right = mid - 1
            return last

        return [findFirst(nums, target), findLast(nums, target)]