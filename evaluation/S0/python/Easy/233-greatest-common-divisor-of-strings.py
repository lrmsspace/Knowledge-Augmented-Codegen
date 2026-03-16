# Source: https://leetcode.com/problems/greatest-common-divisor-of-strings/   |   Difficulty: Easy
#
# Problem Description:
# For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).
#
# Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.
#
# Example:
# Input: str1 = "ABCABC", str2 = "ABC"
# Output: "ABC"
#
# Constraints:
# 1 <= str1.length, str2.length <= 1000
# 	str1 and str2 consist of English uppercase letters.
#

class Solution(object):
    def gcdOfStrings(self, str1, str2):
        """
        :type str1: str
        :type str2: str
        :rtype: str
        """
        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a

        len1, len2 = len(str1), len(str2)
        gcd_len = gcd(len1, len2)

        candidate = str1[:gcd_len]
        if candidate * (len1 // gcd_len) == str1 and candidate * (len2 // gcd_len) == str2:
            return candidate
        else:
            return ""