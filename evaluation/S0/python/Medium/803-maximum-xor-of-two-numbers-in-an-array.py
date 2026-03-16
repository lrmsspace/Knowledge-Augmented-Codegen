# Source: https://leetcode.com/problems/maximum-xor-of-two-numbers-in-an-array/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer array nums, return the maximum result of nums[i] XOR nums[j], where 0 <= i <= j < n.
#
# Example:
# Input: nums = [3,10,5,25,2,8]
# Output: 28
# Explanation: The maximum result is 5 XOR 25 = 28.
#
# Constraints:
# 1 <= nums.length <= 2 * 105
# 	0 <= nums[i] <= 231 - 1
#

class Solution(object):
    def findMaximumXOR(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_xor = 0
        mask = 0
        for i in range(31, -1, -1):
            mask |= (1 << i)
            found_prefixes = {num & mask for num in nums}
            potential_max_xor = max_xor | (1 << i)
            for prefix in found_prefixes:
                if (prefix ^ potential_max_xor) in found_prefixes:
                    max_xor = potential_max_xor
                    break
        return max_xor