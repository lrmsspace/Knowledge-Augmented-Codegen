# Source: https://leetcode.com/problems/most-frequent-even-element/   |   Difficulty: Easy
#
# Problem Description:
# Given an integer array nums, return the most frequent even element.
#
# If there is a tie, return the smallest one. If there is no such element, return -1.
#
# Example:
# Input: nums = [0,1,2,2,4,4,1]
# Output: 2
# Explanation:
# The even elements are 0, 2, and 4. Of these, 2 and 4 appear the most.
# We return the smallest one, which is 2.
#
# Constraints:
# 1 <= nums.length <= 2000
# 	0 <= nums[i] <= 105
#

class Solution(object):
    def mostFrequentEven(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        freq = {}
        for num in nums:
            if num % 2 == 0:
                freq[num] = freq.get(num, 0) + 1

        if not freq:
            return -1

        max_freq = max(freq.values())
        candidates = [num for num, count in freq.items() if count == max_freq]
        return min(candidates)