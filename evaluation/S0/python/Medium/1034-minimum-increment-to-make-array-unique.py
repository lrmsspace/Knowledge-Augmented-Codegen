# Source: https://leetcode.com/problems/minimum-increment-to-make-array-unique/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums. In one move, you can pick an index i where 0 <= i < nums.length and increment nums[i] by 1.
#
# Return the minimum number of moves to make every value in nums unique.
#
# The test cases are generated so that the answer fits in a 32-bit integer.
#
# Example:
# Input: nums = [1,2,2]
# Output: 1
# Explanation: After 1 move, the array could be [1, 2, 3].
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] <= 105
#

class Solution(object):
    def minIncrementForUnique(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        moves = 0
        for i in range(1, len(nums)):
            if nums[i] <= nums[i - 1]:
                needed = nums[i - 1] + 1 - nums[i]
                moves += needed
                nums[i] += needed
        return moves