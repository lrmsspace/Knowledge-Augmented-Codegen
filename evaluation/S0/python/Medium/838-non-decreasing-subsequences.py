# Source: https://leetcode.com/problems/non-decreasing-subsequences/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return all the different possible non-decreasing subsequences of the given array with at least two elements. You may return the answer in any order.
#
# Example:
# Input: nums = [4,6,7,7]
# Output: [[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]
#
# Constraints:
# 1 <= nums.length <= 15
# 	-100 <= nums[i] <= 100
#

class Solution(object):
    def findSubsequences(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """
        res = set()
        
        def backtrack(start, path):
            if len(path) >= 2:
                res.add(tuple(path))
            
            for i in range(start, len(nums)):
                if not path or nums[i] >= path[-1]:
                    backtrack(i + 1, path + [nums[i]])
        
        backtrack(0, [])
        return [list(seq) for seq in res]