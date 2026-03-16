# Source: https://leetcode.com/problems/find-all-numbers-disappeared-in-an-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an array nums of n integers where nums[i] is in the range [1, n], return an array of all the integers in the range [1, n] that do not appear in nums.
#
# Example:
# Input: nums = [4,3,2,7,8,2,3,1]
# Output: [5,6]
#
# Constraints:
# n == nums.length
# 	1 <= n <= 105
# 	1 <= nums[i] <= n
#
#
#  
# Follow up: Could you do it without extra space and in O(n) runtime? You may assume the returned list does not count as extra space.
#

class Solution(object):
    def findDisappearedNumbers(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        n = len(nums)
        num_set = set(nums)
        result = []
        
        for i in range(1, n + 1):
            if i not in num_set:
                result.append(i)
        
        return result