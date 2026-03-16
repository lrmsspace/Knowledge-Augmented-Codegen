# Source: https://leetcode.com/problems/number-of-unique-xor-triplets-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer array nums.
#
# A XOR triplet is defined as the XOR of three elements nums[i] XOR nums[j] XOR nums[k] where i <= j <= k.
#
# Return the number of unique XOR triplet values from all possible triplets (i, j, k).
#
# Example:
# Input: nums = [1,3]
#
# Output: 2
#
# Explanation:
#
# The possible XOR triplet values are:
#
#
# 	(0, 0, 0) → 1 XOR 1 XOR 1 = 1
# 	(0, 0, 1) → 1 XOR 1 XOR 3 = 3
# 	(0, 1, 1) → 1 XOR 3 XOR 3 = 1
# 	(1, 1, 1) → 3 XOR 3 XOR 3 = 3
#
#
# The unique XOR values are {1, 3}. Thus, the output is 2.
#
# Constraints:
# 1 <= nums.length <= 1500
# 	1 <= nums[i] <= 1500
#

class Solution(object):
    def uniqueXorTriplets(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        unique_xors = set()
        n = len(nums)
        
        for i in range(n):
            for j in range(i, n):
                for k in range(j, n):
                    xor_value = nums[i] ^ nums[j] ^ nums[k]
                    unique_xors.add(xor_value)
        
        return len(unique_xors)