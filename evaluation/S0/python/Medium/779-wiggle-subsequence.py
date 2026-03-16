# Source: https://leetcode.com/problems/wiggle-subsequence/   |   Difficulty: Medium
#
# Problem Description:
# A wiggle sequence is a sequence where the differences between successive numbers strictly alternate between positive and negative. The first difference (if one exists) may be either positive or negative. A sequence with one element and a sequence with two non-equal elements are trivially wiggle sequences.
#
#
# 	For example, [1, 7, 4, 9, 2, 5] is a wiggle sequence because the differences (6, -3, 5, -7, 3) alternate between positive and negative.
# 	In contrast, [1, 4, 7, 2, 5] and [1, 7, 4, 5, 5] are not wiggle sequences. The first is not because its first two differences are positive, and the second is not because its last difference is zero.
#
#
# A subsequence is obtained by deleting some elements (possibly zero) from the original sequence, leaving the remaining elements in their original order.
#
# Given an integer array nums, return the length of the longest wiggle subsequence of nums.
#
# Example:
# Input: nums = [1,7,4,9,2,5]
# Output: 6
# Explanation: The entire sequence is a wiggle sequence with differences (6, -3, 5, -7, 3).
#
# Constraints:
# 1 <= nums.length <= 1000
# 	0 <= nums[i] <= 1000
#
#
#  
# Follow up: Could you solve this in O(n) time?
#

class Solution(object):
    def wiggleMaxLength(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        if not nums:
            return 0
        
        n = len(nums)
        up = [1] * n
        down = [1] * n
        
        for i in range(1, n):
            if nums[i] > nums[i - 1]:
                up[i] = down[i - 1] + 1
                down[i] = down[i - 1]
            elif nums[i] < nums[i - 1]:
                down[i] = up[i - 1] + 1
                up[i] = up[i - 1]
            else:
                up[i] = up[i - 1]
                down[i] = down[i - 1]
        
        return max(up[-1], down[-1])