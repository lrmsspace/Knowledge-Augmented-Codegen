# Source: https://leetcode.com/problems/number-of-unique-xor-triplets-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums of length n, where nums is a permutation of the numbers in the range [1, n].
#
# A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
#
# Return the number of unique XOR triplet values from all possible triplets (i, j, k).
#
# Example:
# Input: nums = [1,2]
#
# Output: 2
#
# Explanation:
#
# The possible XOR triplet values are:
#
#
# 	(0, 0, 0) → 1 XOR 1 XOR 1 = 1
# 	(0, 0, 1) → 1 XOR 1 XOR 2 = 2
# 	(0, 1, 1) → 1 XOR 2 XOR 2 = 1
# 	(1, 1, 1) → 2 XOR 2 XOR 2 = 2
#
#
# The unique XOR values are {1, 2}, so the output is 2.
#
# Constraints:
# 1 <= n == nums.length <= 105
# 	1 <= nums[i] <= n
# 	nums is a permutation of integers from 1 to n.
#

class Solution(object):
    def uniqueXorTriplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        xor_set = set()

        for i in range(n):
            xor_value = 0
            for j in range(i, n):
                xor_value ^= nums[j]
                xor_set.add(xor_value)

        return len(xor_set)