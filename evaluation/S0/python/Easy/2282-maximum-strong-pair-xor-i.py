# Source: https://leetcode.com/problems/maximum-strong-pair-xor-i/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed integer array nums. A pair of integers x and y is called a strong pair if it satisfies the condition:
#
#
# 	|x - y| <= min(x, y)
#
#
# You need to select two integers from nums such that they form a strong pair and their bitwise XOR is the maximum among all strong pairs in the array.
#
# Return the maximum XOR value out of all possible strong pairs in the array nums.
#
# Note that you can pick the same integer twice to form a pair.
#
# Example:
# Input: nums = [1,2,3,4,5]
# Output: 7
# Explanation: There are 11 strong pairs in the array nums: (1, 1), (1, 2), (2, 2), (2, 3), (2, 4), (3, 3), (3, 4), (3, 5), (4, 4), (4, 5) and (5, 5).
# The maximum XOR possible from these pairs is 3 XOR 4 = 7.
#
# Constraints:
# 1 <= nums.length <= 50
# 	1 <= nums[i] <= 100
#

class Solution(object):
    def maximumStrongPairXor(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        max_xor = 0
        n = len(nums)
        
        for i in range(n):
            for j in range(n):
                if abs(nums[i] - nums[j]) <= min(nums[i], nums[j]):
                    max_xor = max(max_xor, nums[i] ^ nums[j])
        
        return max_xor