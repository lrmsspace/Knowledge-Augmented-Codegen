# Source: https://leetcode.com/problems/sum-of-unique-elements/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums. The unique elements of an array are the elements that appear exactly once in the array.
#
# Return the sum of all the unique elements of nums.
#
# Example:
# Input: nums = [1,2,3,2]
# Output: 4
# Explanation: The unique elements are [1,3], and the sum is 4.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def sumOfUnique(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count = {}
        for num in nums:
            count[num] = count.get(num, 0) + 1
        
        unique_sum = 0
        for num, freq in count.items():
            if freq == 1:
                unique_sum += num
        
        return unique_sum