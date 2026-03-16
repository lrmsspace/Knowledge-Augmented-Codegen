# Source: https://leetcode.com/problems/maximum-subarray/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, find the subarray with the largest sum, and return its sum.
#
# Example:
# Input: nums = [-2,1,-3,4,-1,2,1,-5,4]
# Output: 6
# Explanation: The subarray [4,-1,2,1] has the largest sum 6.
#
# Constraints:
# 1 <= nums.length <= 105
# 	-104 <= nums[i] <= 104
#
#
#  
# Follow up: If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach, which is more subtle.
#

class Solution(object):
    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_sum = current_sum = nums[0]
        
        for num in nums[1:]:
            current_sum = max(num, current_sum + num)
            max_sum = max(max_sum, current_sum)
        
        return max_sum