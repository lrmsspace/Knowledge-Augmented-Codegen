# Source: https://leetcode.com/problems/find-the-k-or-of-an-array/   |   Difficulty: Easy
#
# Problem Description:
# You are given an integer array nums, and an integer k. Let's introduce K-or operation by extending the standard bitwise OR. In K-or, a bit position in the result is set to 1 if at least k numbers in nums have a 1 in that position.
#
# Return the K-or of nums.
#
# Example:
# Input: nums = [7,12,9,8,9,15], k = 4 
#
# Output: 9 
#
# Explanation: 
#
# Represent numbers in binary:
#
#
# 	
# 		
# 			Number
# 			Bit 3
# 			Bit 2
# 			Bit 1
# 			Bit 0
# 		
# 		
# 			7
# 			0
# 			1
# 			1
# 			1
# 		
# 		
# 			12
# 			1
# 			1
# 			0
# 			0
# 		
# 		
# 			9
# 			1
# 			0
# 			0
# 			1
# 		
# 		
# 			8
# 			1
# 			0
# 			0
# 			0
# 		
# 		
# 			9
# 			1
# 			0
# 			0
# 			1
# 		
# 		
# 			15
# 			1
# 			1
# 			1
# 			1
# 		
# 		
# 			Result = 9
# 			1
# 			0
# 			0
# 			1
# 		
# 	
#
#
# Bit 0 is set in 7, 9, 9, and 15. Bit 3 is set in 12, 9, 8, 9, and 15.
# Only bits 0 and 3 qualify. The result is (1001)2 = 9.
#
# Constraints:
# 1 <= nums.length <= 50
# 	0 <= nums[i] < 231
# 	1 <= k <= nums.length
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
    def findKOr(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: int
        """
        bit_counts = [0] * 31  # Since nums[i] < 2^31

        for num in nums:
            for i in range(31):
                if num & (1 << i):
                    bit_counts[i] += 1

        result = 0
        for i in range(31):
            if bit_counts[i] >= k:
                result |= (1 << i)

        return result