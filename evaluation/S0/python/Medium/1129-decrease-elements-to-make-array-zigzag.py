# Source: https://leetcode.com/problems/decrease-elements-to-make-array-zigzag/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums of integers, a move consists of choosing any element and decreasing it by 1.
#
# An array A is a zigzag array if either:
#
#
#  Every even-indexed element is greater than adjacent elements, ie. A[0] > A[1] < A[2] > A[3] < A[4] > ...
#  OR, every odd-indexed element is greater than adjacent elements, ie. A[0] < A[1] > A[2] < A[3] > A[4] < ...
#
#
# Return the minimum number of moves to transform the given array nums into a zigzag array.
#
# Example:
# Input: nums = [1,2,3]
# Output: 2
# Explanation: We can decrease 2 to 0 or 3 to 1.
#
# Constraints:
# 1 <= nums.length <= 1000
#  1 <= nums[i] <= 1000
#

class Solution(object):
    def movesToMakeZigzag(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def calculate_moves(start_high):
            moves = 0
            for i in range(len(nums)):
                left = nums[i - 1] if i - 1 >= 0 else float('inf')
                right = nums[i + 1] if i + 1 < len(nums) else float('inf')
                
                if (i % 2 == 0) == start_high:
                    target = min(left, right) - 1
                    if nums[i] >= target:
                        moves += nums[i] - target
            return moves
        
        return min(calculate_moves(True), calculate_moves(False))