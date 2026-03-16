# Source: https://leetcode.com/problems/max-pair-sum-in-an-array/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums. You have to find the maximum sum of a pair of numbers from nums such that the largest digit in both numbers is equal.
#
# For example, 2373 is made up of three distinct digits: 2, 3, and 7, where 7 is the largest among them.
#
# Return the maximum sum or -1 if no such pair exists.
#
# Example:
# Input: nums = [112,131,411]
#
# Output: -1
#
# Explanation:
#
# Each numbers largest digit in order is [2,3,4].
#
# Constraints:
# 2 <= nums.length <= 100
# 	1 <= nums[i] <= 104
#

class Solution(object):
    def maxSum(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import defaultdict

        digit_map = defaultdict(list)

        for num in nums:
            largest_digit = max(int(d) for d in str(num))
            digit_map[largest_digit].append(num)

        max_sum = -1

        for numbers in digit_map.values():
            if len(numbers) >= 2:
                numbers.sort(reverse=True)
                current_sum = numbers[0] + numbers[1]
                max_sum = max(max_sum, current_sum)

        return max_sum