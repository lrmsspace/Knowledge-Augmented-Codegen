# Source: https://leetcode.com/problems/find-the-maximum-factor-score-of-array/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# The factor score of an array is defined as the product of the LCM and GCD of all elements of that array.
#
# Return the maximum factor score of nums after removing at most one element from it.
#
# Note that both the LCM and GCD of a single number are the number itself, and the factor score of an empty array is 0.
#
# Example:
# Input: nums = [2,4,8,16]
#
# Output: 64
#
# Explanation:
#
# On removing 2, the GCD of the rest of the elements is 4 while the LCM is 16, which gives a maximum factor score of 4 * 16 = 64.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 30
#

class Solution(object):
    def maxScore(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        return None