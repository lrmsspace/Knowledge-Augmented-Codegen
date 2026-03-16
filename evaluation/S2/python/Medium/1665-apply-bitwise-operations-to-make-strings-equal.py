# Source: https://leetcode.com/problems/apply-bitwise-operations-to-make-strings-equal/   |   Difficulty: Medium
#
# Problem Description:
# You are given two 0-indexed binary strings s and target of the same length n. You can do the following operation on s any number of times:
#
#
# 	Choose two different indices i and j where 0 <= i, j < n.
# 	Simultaneously, replace s[i] with (s[i] OR s[j]) and s[j] with (s[i] XOR s[j]).
#
#
# For example, if s = "0110", you can choose i = 0 and j = 2, then simultaneously replace s[0] with (s[0] OR s[2] = 0 OR 1 = 1), and s[2] with (s[0] XOR s[2] = 0 XOR 1 = 1), so we will have s = "1110".
#
# Return true if you can make the string s equal to target, or false otherwise.
#
# Example:
# Input: s = "1010", target = "0110"
# Output: true
# Explanation: We can do the following operations:
# - Choose i = 2 and j = 0. We have now s = "0010".
# - Choose i = 2 and j = 1. We have now s = "0110".
# Since we can make s equal to target, we return true.
#
# Constraints:
# n == s.length == target.length
# 	2 <= n <= 105
# 	s and target consist of only the digits 0 and 1.
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
    def makeStringsEqual(self, s, target):
        """
        :type s: str
        :type target: str
        :rtype: bool
        """
        # If target contains '1', s must also contain '1' to be able to transform into target.
        if '1' in target and '1' not in s:
            return False
        return True