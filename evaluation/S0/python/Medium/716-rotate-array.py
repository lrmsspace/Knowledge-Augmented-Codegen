# Source: https://leetcode.com/problems/rotate-array/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, rotate the array to the right by k steps, where k is non-negative.
#
# Example:
# Input: nums = [1,2,3,4,5,6,7], k = 3
# Output: [5,6,7,1,2,3,4]
# Explanation:
# rotate 1 steps to the right: [7,1,2,3,4,5,6]
# rotate 2 steps to the right: [6,7,1,2,3,4,5]
# rotate 3 steps to the right: [5,6,7,1,2,3,4]
#
# Constraints:
# 1 <= nums.length <= 105
# 	-231 <= nums[i] <= 231 - 1
# 	0 <= k <= 105
#
#
#  
# Follow up:
#
#
# 	Try to come up with as many solutions as you can. There are at least three different ways to solve this problem.
# 	Could you do it in-place with O(1) extra space?
#

class Solution(object):
    def rotate(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: None Do not return anything, modify nums in-place instead.
        """
        n = len(nums)
        k = k % n  # In case k is greater than n

        # Helper function to reverse a portion of the array
        def reverse(start, end):
            while start < end:
                nums[start], nums[end] = nums[end], nums[start]
                start += 1
                end -= 1

        # Step 1: Reverse the entire array
        reverse(0, n - 1)
        # Step 2: Reverse the first k elements
        reverse(0, k - 1)
        # Step 3: Reverse the remaining n-k elements
        reverse(k, n - 1)