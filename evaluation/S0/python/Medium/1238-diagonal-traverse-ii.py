# Source: https://leetcode.com/problems/diagonal-traverse-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given a 2D integer array nums, return all elements of nums in diagonal order as shown in the below images.
#
# Example:
# Input: nums = [[1,2,3],[4,5,6],[7,8,9]]
# Output: [1,4,2,7,5,3,8,6,9]
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i].length <= 105
# 	1 <= sum(nums[i].length) <= 105
# 	1 <= nums[i][j] <= 105
#

class Solution(object):
    def findDiagonalOrder(self, nums):
        """
        :type nums: List[List[int]]
        :rtype: List[int]
        """
        from collections import defaultdict
        diagonals = defaultdict(list)
        
        for r in range(len(nums)):
            for c in range(len(nums[r])):
                diagonals[r + c].append(nums[r][c])
        
        result = []
        for d in range(len(diagonals)):
            result.extend(reversed(diagonals[d]))
        
        return result