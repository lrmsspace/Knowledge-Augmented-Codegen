# Source: https://leetcode.com/problems/first-missing-positive/   |   Difficulty: Hard
#
# Problem Description:
# Given an unsorted integer array nums. Return the smallest positive integer that is not present in nums.
#
# You must implement an algorithm that runs in O(n) time and uses O(1) auxiliary space.
#
# Example:
# Input: nums = [1,2,0]
# Output: 3
# Explanation: The numbers in the range [1,2] are all in the array.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-231 <= nums[i] <= 231 - 1
#

class Solution(object):
    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        
        # Step 1: Place each number in its right place, i.e., nums[i] = i + 1
        for i in range(n):
            while 1 <= nums[i] <= n and nums[nums[i] - 1] != nums[i]:
                # Swap nums[i] with nums[nums[i] - 1]
                correct_index = nums[i] - 1
                nums[i], nums[correct_index] = nums[correct_index], nums[i]
        
        # Step 2: Find the first index where the number is not correct
        for i in range(n):
            if nums[i] != i + 1:
                return i + 1
        
        # If all numbers are in their correct places, return n + 1
        return n + 1