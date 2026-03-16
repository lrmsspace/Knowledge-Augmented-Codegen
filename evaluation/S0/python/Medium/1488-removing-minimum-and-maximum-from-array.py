# Source: https://leetcode.com/problems/removing-minimum-and-maximum-from-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of distinct integers nums.
#
# There is an element in nums that has the lowest value and an element that has the highest value. We call them the minimum and maximum respectively. Your goal is to remove both these elements from the array.
#
# A deletion is defined as either removing an element from the front of the array or removing an element from the back of the array.
#
# Return the minimum number of deletions it would take to remove both the minimum and maximum element from the array.
#
# Example:
# Input: nums = [2,10,7,5,4,1,8,6]
# Output: 5
# Explanation: 
# The minimum element in the array is nums[5], which is 1.
# The maximum element in the array is nums[1], which is 10.
# We can remove both the minimum and maximum by removing 2 elements from the front and 3 elements from the back.
# This results in 2 + 3 = 5 deletions, which is the minimum number possible.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-105 <= nums[i] <= 105
# 	The integers in nums are distinct.
#

class Solution(object):
    def minimumDeletions(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        min_index = nums.index(min(nums))
        max_index = nums.index(max(nums))
        
        left = min(min_index, max_index) + 1
        right = len(nums) - max(min_index, max_index)
        middle = abs(max_index - min_index) + 1
        
        return min(left + right, left + middle, right + middle)