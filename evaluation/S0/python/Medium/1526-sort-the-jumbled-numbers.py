# Source: https://leetcode.com/problems/sort-the-jumbled-numbers/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array mapping which represents the mapping rule of a shuffled decimal system. mapping[i] = j means digit i should be mapped to digit j in this system.
#
# The mapped value of an integer is the new integer obtained by replacing each occurrence of digit i in the integer with mapping[i] for all 0 <= i <= 9.
#
# You are also given another integer array nums. Return the array nums sorted in non-decreasing order based on the mapped values of its elements.
#
# Example:
# Input: mapping = [8,9,4,0,2,1,3,5,7,6], nums = [991,338,38]
# Output: [338,38,991]
# Explanation: 
# Map the number 991 as follows:
# 1. mapping[9] = 6, so all occurrences of the digit 9 will become 6.
# 2. mapping[1] = 9, so all occurrences of the digit 1 will become 9.
# Therefore, the mapped value of 991 is 669.
# 338 maps to 007, or 7 after removing the leading zeros.
# 38 maps to 07, which is also 7 after removing leading zeros.
# Since 338 and 38 share the same mapped value, they should remain in the same relative order, so 338 comes before 38.
# Thus, the sorted array is [338,38,991].
#
# Constraints:
# mapping.length == 10
# 	0 <= mapping[i] <= 9
# 	All the values of mapping[i] are unique.
# 	1 <= nums.length <= 3 * 104
# 	0 <= nums[i] < 109
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sortJumbled(self, mapping, nums):
        """
        :type mapping: List[int]
        :type nums: List[int]
        :rtype: List[int]
        """
        def get_mapped_value(num):
            if num == 0:
                return mapping[0]
            mapped_digits = []
            while num > 0:
                digit = num % 10
                mapped_digits.append(str(mapping[digit]))
                num //= 10
            mapped_digits.reverse()
            return int(''.join(mapped_digits))
        
        return sorted(nums, key=lambda x: get_mapped_value(x))