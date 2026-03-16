# Source: https://leetcode.com/problems/running-sum-of-1d-array/   |   Difficulty: Easy
#
# Problem Description:
# Given an array nums. We define a running sum of an array as runningSum[i] = sum(nums[0]…nums[i]).
#
# Return the running sum of nums.
#
# Example:
# Input: nums = [1,2,3,4]
# Output: [1,3,6,10]
# Explanation: Running sum is obtained as follows: [1, 1+2, 1+2+3, 1+2+3+4].
#
# Constraints:
# 1 <= nums.length <= 1000
# 	-10^6 <= nums[i] <= 10^6
#

class Solution(object):
    def runningSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        for i in range(1, len(nums)):
            nums[i] += nums[i - 1]
        return nums