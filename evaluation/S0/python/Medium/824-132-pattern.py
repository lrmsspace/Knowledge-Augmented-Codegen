# Source: https://leetcode.com/problems/132-pattern/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of n integers nums, a 132 pattern is a subsequence of three integers nums[i], nums[j] and nums[k] such that i < j < k and nums[i] < nums[k] < nums[j].
#
# Return true if there is a 132 pattern in nums, otherwise, return false.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: false
# Explanation: There is no 132 pattern in the sequence.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 2 * 105
# 	-109 <= nums[i] <= 109
#

class Solution(object):
    def find132pattern(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        n = len(nums)
        if n < 3:
            return False

        stack = []
        third = float('-inf')

        for i in range(n - 1, -1, -1):
            if nums[i] < third:
                return True
            while stack and nums[i] > stack[-1]:
                third = stack.pop()
            stack.append(nums[i])

        return False