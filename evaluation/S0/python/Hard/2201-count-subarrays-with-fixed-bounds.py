# Source: https://leetcode.com/problems/count-subarrays-with-fixed-bounds/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums and two integers minK and maxK.
#
# A fixed-bound subarray of nums is a subarray that satisfies the following conditions:
#
#
# 	The minimum value in the subarray is equal to minK.
# 	The maximum value in the subarray is equal to maxK.
#
#
# Return the number of fixed-bound subarrays.
#
# A subarray is a contiguous part of an array.
#
# Example:
# Input: nums = [1,3,5,2,7,5], minK = 1, maxK = 5
# Output: 2
# Explanation: The fixed-bound subarrays are [1,3,5] and [1,3,5,2].
#
# Constraints:
# 2 <= nums.length <= 105
# 	1 <= nums[i], minK, maxK <= 106
#

class Solution(object):
    def countSubarrays(self, nums, minK, maxK):
        """
        :type nums: List[int]
        :type minK: int
        :type maxK: int
        :rtype: int
        """
        n = len(nums)
        last_minK = -1
        last_maxK = -1
        last_invalid = -1
        count = 0
        
        for i in range(n):
            if nums[i] < minK or nums[i] > maxK:
                last_invalid = i
            if nums[i] == minK:
                last_minK = i
            if nums[i] == maxK:
                last_maxK = i
            
            valid_start = min(last_minK, last_maxK)
            if valid_start > last_invalid:
                count += valid_start - last_invalid
        
        return count