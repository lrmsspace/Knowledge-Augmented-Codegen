# Source: https://leetcode.com/problems/count-number-of-pairs-with-absolute-difference-k/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums and an integer k, return the number of pairs (i, j) where i < j such that |nums[i] - nums[j]| == k.
#
# The value of |x| is defined as:
#
#
# 	x if x >= 0.
# 	-x if x < 0.
#
# Example:
# Input: nums = [1,2,2,1], k = 1
# Output: 4
# Explanation: The pairs with an absolute difference of 1 are:
# - [1,2,2,1]
# - [1,2,2,1]
# - [1,2,2,1]
# - [1,2,2,1]
#
# Constraints:
# 1 <= nums.length <= 200
# 	1 <= nums[i] <= 100
# 	1 <= k <= 99
#

class Solution(object):
    def countKDifference(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        count = 0
        n = len(nums)
        
        for i in range(n):
            for j in range(i + 1, n):
                if abs(nums[i] - nums[j]) == k:
                    count += 1
        
        return count