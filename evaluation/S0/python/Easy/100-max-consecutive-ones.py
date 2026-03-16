# Source: https://leetcode.com/problems/max-consecutive-ones/   |   Difficulty: Easy
#
# Problem Description:
# Given a binary array nums, return the maximum number of consecutive 1's in the array.
#
# Example:
# Input: nums = [1,1,0,1,1,1]
# Output: 3
# Explanation: The first two digits or the last three digits are consecutive 1s. The maximum number of consecutive 1s is 3.
#
# Constraints:
# 1 <= nums.length <= 105
# 	nums[i] is either 0 or 1.
#

class Solution(object):
    def findMaxConsecutiveOnes(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_count = 0
        current_count = 0
        
        for num in nums:
            if num == 1:
                current_count += 1
                max_count = max(max_count, current_count)
            else:
                current_count = 0
                
        return max_count