# Source: https://leetcode.com/problems/minimum-score-by-changing-two-elements/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
#
# 	The low score of nums is the minimum absolute difference between any two integers.
# 	The high score of nums is the maximum absolute difference between any two integers.
# 	The score of nums is the sum of the high and low scores.
#
#
# Return the minimum score after changing two elements of nums.
#
# Example:
# Input: nums = [1,4,7,8,5]
#
# Output: 3
#
# Explanation:
#
#
# 	Change nums[0] and nums[1] to be 6 so that nums becomes [6,6,7,8,5].
# 	The low score is the minimum absolute difference: |6 - 6| = 0.
# 	The high score is the maximum absolute difference: |8 - 5| = 3.
# 	The sum of high and low score is 3.
#
# Constraints:
# 3 <= nums.length <= 105
# 	1 <= nums[i] <= 109
#

class Solution(object):
    def minimizeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        nums.sort()
        n = len(nums)
        return min(nums[n-1]-nums[2], nums[n-3]-nums[0], nums[n-2]-nums[1], nums[n-4]-nums[0])