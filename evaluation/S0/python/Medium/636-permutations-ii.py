# Source: https://leetcode.com/problems/permutations-ii/   |   Difficulty: Medium
#
# Problem Description:
# Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.
#
# Example:
# Input: nums = [1,1,2]
# Output:
# [[1,1,2],
#  [1,2,1],
#  [2,1,1]]
#
# Constraints:
# 1 <= nums.length <= 8
# 	-10 <= nums[i] <= 10
#

class Solution(object):
    def permuteUnique(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        def backtrack(start):
            if start == len(nums):
                res.append(nums[:])
                return

            for i in range(start, len(nums)):
                if i != start and nums[i] == nums[start]:
                    continue

                nums[start], nums[i] = nums[i], nums[start]
                backtrack(start + 1)
                nums[start], nums[i] = nums[i], nums[start]

        res = []
        nums.sort()
        backtrack(0)
        return res
        
        