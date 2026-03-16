# Source: https://leetcode.com/problems/largest-combination-with-bitwise-and-greater-than-zero/   |   Difficulty: Medium
#
# Problem Description:
# The bitwise AND of an array nums is the bitwise AND of all integers in nums.
#
#
# 	For example, for nums = [1, 5, 3], the bitwise AND is equal to 1 & 5 & 3 = 1.
# 	Also, for nums = [7], the bitwise AND is 7.
#
#
# You are given an array of positive integers candidates. Compute the bitwise AND for all possible combinations of elements in the candidates array.
#
# Return the size of the largest combination of candidates with a bitwise AND greater than 0.
#
# Example:
# Input: candidates = [16,17,71,62,12,24,14]
# Output: 4
# Explanation: The combination [16,17,62,24] has a bitwise AND of 16 & 17 & 62 & 24 = 16 > 0.
# The size of the combination is 4.
# It can be shown that no combination with a size greater than 4 has a bitwise AND greater than 0.
# Note that more than one combination may have the largest size.
# For example, the combination [62,12,24,14] has a bitwise AND of 62 & 12 & 24 & 14 = 8 > 0.
#
# Constraints:
# 1 <= candidates.length <= 105
# 	1 <= candidates[i] <= 107
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
    def largestCombination(self, candidates):
        """
        :type candidates: List[int]
        :rtype: int
        """
        bit_count = [0] * 32  # Assuming 32-bit integers

        for num in candidates:
            for i in range(32):
                if num & (1 << i):
                    bit_count[i] += 1

        return max(bit_count)