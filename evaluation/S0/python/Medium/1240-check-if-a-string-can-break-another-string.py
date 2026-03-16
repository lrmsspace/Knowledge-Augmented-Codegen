# Source: https://leetcode.com/problems/check-if-a-string-can-break-another-string/   |   Difficulty: Medium
#
# Problem Description:
# Given two strings: s1 and s2 with the same size, check if some permutation of string s1 can break some permutation of string s2 or vice-versa. In other words s2 can break s1 or vice-versa.
#
# A string x can break string y (both of size n) if x[i] >= y[i] (in alphabetical order) for all i between 0 and n-1.
#
# Example:
# Input: s1 = "abc", s2 = "xya"
# Output: true
# Explanation: "ayx" is a permutation of s2="xya" which can break to string "abc" which is a permutation of s1="abc".
#
# Constraints:
# s1.length == n
# 	s2.length == n
# 	1 <= n <= 10^5
# 	All strings consist of lowercase English letters.
#

class Solution(object):
    def checkIfCanBreak(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """
        s1 = sorted(s1)
        s2 = sorted(s2)
        
        s1_breaks_s2 = all(c1 >= c2 for c1, c2 in zip(s1, s2))
        s2_breaks_s1 = all(c2 >= c1 for c1, c2 in zip(s1, s2))
        
        return s1_breaks_s2 or s2_breaks_s1