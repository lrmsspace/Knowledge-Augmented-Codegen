# Source: https://leetcode.com/problems/minimum-adjacent-swaps-to-alternate-parity/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array nums of distinct integers.
#
# In one operation, you can swap any two adjacent elements in the array.
#
# An arrangement of the array is considered valid if the parity of adjacent elements alternates, meaning every pair of neighboring elements consists of one even and one odd number.
#
# Return the minimum number of adjacent swaps required to transform nums into any valid arrangement.
#
# If it is impossible to rearrange nums such that no two adjacent elements have the same parity, return -1.
#
# Example:
# Input: nums = [2,4,6,5,7]
#
# Output: 3
#
# Explanation:
#
# Swapping 5 and 6, the array becomes [2,4,5,6,7]
#
# Swapping 5 and 4, the array becomes [2,5,4,6,7]
#
# Swapping 6 and 7, the array becomes [2,5,4,7,6]. The array is now a valid arrangement. Thus, the answer is 3.
#
# Constraints:
# 1 <= nums.length <= 105
# 	1 <= nums[i] <= 109
# 	All elements in nums are distinct.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minSwaps(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        even_count = sum(1 for num in nums if num % 2 == 0)
        odd_count = len(nums) - even_count
        
        if abs(even_count - odd_count) > 1:
            return -1  # It's impossible to arrange
        
        # Determine the starting parity
        start_parity = 0 if even_count >= odd_count else 1
        
        swaps = 0
        even_index, odd_index = 0, 0
        
        for i in range(len(nums)):
            if nums[i] % 2 == start_parity:
                while even_index < len(nums) and nums[even_index] % 2 != start_parity:
                    even_index += 1
                if even_index < len(nums):
                    swaps += abs(i - even_index)
                    even_index += 1
            else:
                while odd_index < len(nums) and nums[odd_index] % 2 == start_parity:
                    odd_index += 1
                if odd_index < len(nums):
                    swaps += abs(i - odd_index)
                    odd_index += 1
        
        return swaps