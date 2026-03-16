# Source: https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/   |   Difficulty: Hard
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
# Given an integer array nums​​​, return the minimum number of elements to remove to make nums​​​ a mountain array.
#
# Example:
# Input: nums = [1,3,1]
# Output: 0
# Explanation: The array itself is a mountain array so we do not need to remove any elements.
#
# Constraints:
# 3 <= nums.length <= 1000
# 	1 <= nums[i] <= 109
# 	It is guaranteed that you can make a mountain array out of nums.
#

class Solution(object):
    def minimumMountainRemovals(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        
        # Calculate LIS from the left
        lis_left = [1] * n
        for i in range(n):
            for j in range(i):
                if nums[j] < nums[i]:
                    lis_left[i] = max(lis_left[i], lis_left[j] + 1)
        
        # Calculate LIS from the right
        lis_right = [1] * n
        for i in range(n - 1, -1, -1):
            for j in range(n - 1, i, -1):
                if nums[j] < nums[i]:
                    lis_right[i] = max(lis_right[i], lis_right[j] + 1)
        
        # Find the maximum length of mountain array
        max_mountain_len = 0
        for i in range(1, n - 1):
            if lis_left[i] > 1 and lis_right[i] > 1:
                max_mountain_len = max(max_mountain_len, lis_left[i] + lis_right[i] - 1)
        
        return n - max_mountain_len