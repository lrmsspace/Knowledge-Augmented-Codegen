# Source: https://leetcode.com/problems/smallest-substring-with-identical-characters-i/   |   Difficulty: Hard
#
# Problem Description:
# You are given a binary string s of length n and an integer numOps.
#
# You are allowed to perform the following operation on s at most numOps times:
#
#
# 	Select any index i (where 0 <= i < n) and flip s[i]. If s[i] == '1', change s[i] to '0' and vice versa.
#
#
# You need to minimize the length of the longest substring of s such that all the characters in the substring are identical.
#
# Return the minimum length after the operations.
#
# Example:
# Input: s = "000001", numOps = 1
#
# Output: 2
#
# Explanation: 
#
# By changing s[2] to '1', s becomes "001001". The longest substrings with identical characters are s[0..1] and s[3..4].
#
# Constraints:
# 1 <= n == s.length <= 1000
# 	s consists only of '0' and '1'.
# 	0 <= numOps <= n
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
    def minLength(self, s, numOps):
        """
        :type s: str
        :type numOps: int
        :rtype: int
        """
        n = len(s)
        
        # Count the number of '0's and '1's in the string
        count_0 = s.count('0')
        count_1 = n - count_0
        
        # If we can flip all characters to '0' or all to '1', the answer is 1
        if numOps >= min(count_0, count_1):
            return 1
        
        # Otherwise, we can only flip numOps characters, so the longest substring of identical characters will be:
        # max(count_0 - numOps, count_1 - numOps)
        return max(count_0 - numOps, count_1 - numOps)