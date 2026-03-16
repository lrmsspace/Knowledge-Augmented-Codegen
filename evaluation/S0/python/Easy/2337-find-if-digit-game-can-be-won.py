# Source: https://leetcode.com/problems/find-if-digit-game-can-be-won/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of positive integers nums.
#
# Alice and Bob are playing a game. In the game, Alice can choose either all single-digit numbers or all double-digit numbers from nums, and the rest of the numbers are given to Bob. Alice wins if the sum of her numbers is strictly greater than the sum of Bob's numbers.
#
# Return true if Alice can win this game, otherwise, return false.
#
# Example:
# Input: nums = [1,2,3,4,10]
#
# Output: false
#
# Explanation:
#
# Alice cannot win by choosing either single-digit or double-digit numbers.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 99
#

class Solution(object):
    def canAliceWin(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """
        single_digit_sum = sum(num for num in nums if num < 10)
        double_digit_sum = sum(num for num in nums if num >= 10)
        
        return single_digit_sum > double_digit_sum or double_digit_sum > single_digit_sum