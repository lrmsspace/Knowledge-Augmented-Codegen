# Source: https://leetcode.com/problems/squares-of-a-sorted-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums sorted in non-decreasing order, return an array of the squares of each number sorted in non-decreasing order.
#
# Example:
# Input: nums = [-4,-1,0,3,10]
# Output: [0,1,9,16,100]
# Explanation: After squaring, the array becomes [16,1,0,9,100].
# After sorting, it becomes [0,1,9,16,100].
#
# Constraints:
# 1 <= nums.length <= 104
# 	-104 <= nums[i] <= 104
# 	nums is sorted in non-decreasing order.
#
#
#  
# Follow up: Squaring each element and sorting the new array is very trivial, could you find an O(n) solution using a different approach?
#

class Solution(object):
    def sortedSquares(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        result = [0] * n
        left, right = 0, n - 1
        position = n - 1

        while left <= right:
            left_square = nums[left] * nums[left]
            right_square = nums[right] * nums[right]

            if left_square > right_square:
                result[position] = left_square
                left += 1
            else:
                result[position] = right_square
                right -= 1

            position -= 1

        return result