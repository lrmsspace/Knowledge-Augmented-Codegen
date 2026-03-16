# Source: https://leetcode.com/problems/interleaving-string/   |   Difficulty: Medium
#
# Problem Description:
# Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.
#
# An interleaving of two strings s and t is a configuration where s and t are divided into n and m substrings respectively, such that:
#
#
# 	s = s1 + s2 + ... + sn
# 	t = t1 + t2 + ... + tm
# 	|n - m| <= 1
# 	The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
#
#
# Note: a + b is the concatenation of strings a and b.
#
# Example:
# Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
# Output: true
# Explanation: One way to obtain s3 is:
# Split s1 into s1 = "aa" + "bc" + "c", and s2 into s2 = "dbbc" + "a".
# Interleaving the two splits, we get "aa" + "dbbc" + "bc" + "a" + "c" = "aadbbcbcac".
# Since s3 can be obtained by interleaving s1 and s2, we return true.
#
# Constraints:
# 0 <= s1.length, s2.length <= 100
# 	0 <= s3.length <= 200
# 	s1, s2, and s3 consist of lowercase English letters.
#
#
#  
# Follow up: Could you solve it using only O(s2.length) additional memory space?
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
    def isInterleave(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """
        if len(s1) + len(s2) != len(s3):
            return False

        i, j = 0, 0
        for c in s3:
            if i < len(s1) and s1[i] == c:
                i += 1
            elif j < len(s2) and s2[j] == c:
                j += 1
            else:
                return False

        return True