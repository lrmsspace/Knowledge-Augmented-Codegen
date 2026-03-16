# Source: https://leetcode.com/problems/adjacent-increasing-subarrays-detection-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums of n integers, your task is to find the maximum value of k for which there exist two adjacent subarrays of length k each, such that both subarrays are strictly increasing. Specifically, check if there are two subarrays of length k starting at indices a and b (a < b), where:
#
#
# 	Both subarrays nums[a..a + k - 1] and nums[b..b + k - 1] are strictly increasing.
# 	The subarrays must be adjacent, meaning b = a + k.
#
#
# Return the maximum possible value of k.
#
# A subarray is a contiguous non-empty sequence of elements within an array.
#
# Example:
# Input: nums = [2,5,7,8,9,2,3,4,3,1]
#
# Output: 3
#
# Explanation:
#
#
# 	The subarray starting at index 2 is [7, 8, 9], which is strictly increasing.
# 	The subarray starting at index 5 is [2, 3, 4], which is also strictly increasing.
# 	These two subarrays are adjacent, and 3 is the maximum possible value of k for which two such adjacent strictly increasing subarrays exist.
#
# Constraints:
# 2 <= nums.length <= 2 * 105
# 	-109 <= nums[i] <= 109
#

class Solution(object):
    def maxIncreasingSubarrays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        inc = [1] * n
        
        for i in range(n - 2, -1, -1):
            if nums[i] < nums[i + 1]:
                inc[i] = inc[i + 1] + 1
        
        max_k = 0
        for i in range(n - 1):
            k = min(inc[i], inc[i + 1])
            max_k = max(max_k, k)
        
        return max_k