# Source: https://leetcode.com/problems/partition-array-into-disjoint-intervals/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, partition it into two (contiguous) subarrays left and right so that:
#
#
# 	Every element in left is less than or equal to every element in right.
# 	left and right are non-empty.
# 	left has the smallest possible size.
#
#
# Return the length of left after such a partitioning.
#
# Test cases are generated such that partitioning exists.
#
# Example:
# Input: nums = [5,0,3,8,6]
# Output: 3
# Explanation: left = [5,0,3], right = [8,6]
#
# Constraints:
# 2 <= nums.length <= 105
# 	0 <= nums[i] <= 106
# 	There is at least one valid answer for the given input.
#

class Solution(object):
    def partitionDisjoint(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        left_max = [0] * n
        right_min = [0] * n
        
        left_max[0] = nums[0]
        for i in range(1, n):
            left_max[i] = max(left_max[i - 1], nums[i])
        
        right_min[n - 1] = nums[n - 1]
        for i in range(n - 2, -1, -1):
            right_min[i] = min(right_min[i + 1], nums[i])
        
        for i in range(n - 1):
            if left_max[i] <= right_min[i + 1]:
                return i + 1
        
        return None