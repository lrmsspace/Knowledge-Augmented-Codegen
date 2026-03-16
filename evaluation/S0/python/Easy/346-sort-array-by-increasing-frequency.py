# Source: https://leetcode.com/problems/sort-array-by-increasing-frequency/   |   Difficulty: Easy
#
# Problem Description:
# Given an array of integers nums, sort the array in increasing order based on the frequency of the values. If multiple values have the same frequency, sort them in decreasing order.
#
# Return the sorted array.
#
# Example:
# Input: nums = [1,1,2,2,2,3]
# Output: [3,1,1,2,2,2]
# Explanation: '3' has a frequency of 1, '1' has a frequency of 2, and '2' has a frequency of 3.
#
# Constraints:
# 1 <= nums.length <= 100
# 	-100 <= nums[i] <= 100
#

class Solution(object):
    def frequencySort(self, nums):
        """
        :type nums: List[int]
        :rtype: List[int]
        """
        from collections import Counter
        freq = Counter(nums)
        return sorted(nums, key=lambda x: (freq[x], -x))