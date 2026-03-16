# Source: https://leetcode.com/problems/contiguous-array/   |   Difficulty: Medium
#
# Problem Description:
# Given a binary array nums, return the maximum length of a contiguous subarray with an equal number of 0 and 1.
#
# Example:
# Input: nums = [0,1]
# Output: 2
# Explanation: [0, 1] is the longest contiguous subarray with an equal number of 0 and 1.
#
# Constraints:
# 1 <= nums.length <= 105
# 	nums[i] is either 0 or 1.
#

class Solution(object):
    def findMaxLength(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        count_index_map = {0: -1}
        max_length = 0
        count = 0
        
        for i in range(len(nums)):
            if nums[i] == 0:
                count -= 1
            else:
                count += 1
            
            if count in count_index_map:
                max_length = max(max_length, i - count_index_map[count])
            else:
                count_index_map[count] = i
        
        return max_length