# Source: https://leetcode.com/problems/permutations/   |   Difficulty: Medium
#
# Problem Description:
# Given an array nums of distinct integers, return all the possible permutations. You can return the answer in any order.
#
# Example:
# Input: nums = [1,2,3]
# Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]
#
# Constraints:
# 1 <= nums.length <= 6
# 	-10 <= nums[i] <= 10
# 	All the integers of nums are unique.
#

class Solution(object):
    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        result = []
        
        def backtrack(start=0):
            if start == len(nums):
                result.append(nums[:])
                return
            
            for i in range(start, len(nums)):
                nums[start], nums[i] = nums[i], nums[start]  # Swap
                backtrack(start + 1)
                nums[start], nums[i] = nums[i], nums[start]  # Backtrack
        
        backtrack()
        return result