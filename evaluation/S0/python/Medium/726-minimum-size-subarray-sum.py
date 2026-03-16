# Source: https://leetcode.com/problems/minimum-size-subarray-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of positive integers nums and a positive integer target, return the minimal length of a subarray whose sum is greater than or equal to target. If there is no such subarray, return 0 instead.
#
# Example:
# Input: target = 7, nums = [2,3,1,2,4,3]
# Output: 2
# Explanation: The subarray [4,3] has the minimal length under the problem constraint.
#
# Constraints:
# 1 <= target <= 109
# 	1 <= nums.length <= 105
# 	1 <= nums[i] <= 104
#
#
#  
# Follow up: If you have figured out the O(n) solution, try coding another solution of which the time complexity is O(n log(n)).
#

class Solution(object):
    def minSubArrayLen(self, target, nums):
        """
        :type target: int
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        left = 0
        current_sum = 0
        min_length = float('inf')

        for right in range(n):
            current_sum += nums[right]

            while current_sum >= target:
                min_length = min(min_length, right - left + 1)
                current_sum -= nums[left]
                left += 1

        return min_length if min_length != float('inf') else 0