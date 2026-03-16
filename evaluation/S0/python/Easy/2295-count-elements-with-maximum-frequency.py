# Source: https://leetcode.com/problems/count-elements-with-maximum-frequency/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array nums consisting of positive integers.
#
# Return the total frequencies of elements in nums such that those elements all have the maximum frequency.
#
# The frequency of an element is the number of occurrences of that element in the array.
#
# Example:
# Input: nums = [1,2,2,3,1,4]
# Output: 4
# Explanation: The elements 1 and 2 have a frequency of 2 which is the maximum frequency in the array.
# So the number of elements in the array with maximum frequency is 4.
#
# Constraints:
# 1 <= nums.length <= 100
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def maxFrequencyElements(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from collections import Counter
        freq = Counter(nums)
        max_freq = max(freq.values())
        return sum(count for count in freq.values() if count == max_freq)