# Source: https://leetcode.com/problems/number-of-good-pairs/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of integers nums, return the number of good pairs.
#
# A pair (i, j) is called good if nums[i] == nums[j] and i < j.
#
# Example:
# Input: nums = [1,2,3,1,1,3]
# Output: 4
# Explanation: There are 4 good pairs (0,3), (0,4), (3,4), (2,5) 0-indexed.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def numIdenticalPairs(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = 0
        freq = {}
        
        for num in nums:
            if num in freq:
                count += freq[num]
                freq[num] += 1
            else:
                freq[num] = 1
        
        return count