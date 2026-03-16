# Source: https://leetcode.com/problems/count-sorted-vowel-strings/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the number of strings of length n that consist only of vowels (a, e, i, o, u) and are lexicographically sorted.
#
# A string s is lexicographically sorted if for all valid i, s[i] is the same as or comes before s[i+1] in the alphabet.
#
# Example:
# Input: n = 1
# Output: 5
# Explanation: The 5 sorted strings that consist of vowels only are ["a","e","i","o","u"].
#
# Constraints:
# 1 <= n <= 50
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
    def countVowelStrings(self, n):
        """
        :type n: int
        :rtype: int
        """
        # There are 5 vowels: a, e, i, o, u
        # We can use combinatorial mathematics to solve this problem.
        # The problem can be transformed into finding the number of ways to distribute n indistinguishable items (vowel positions)
        # into 5 distinguishable boxes (the vowels), allowing empty boxes.
        #
        # This is a classic "stars and bars" problem in combinatorics.
        # The formula for the number of ways to distribute n indistinguishable items into k distinguishable boxes is:
        # C(n + k - 1, k - 1)
        #
        # In our case, n is the length of the string and k is 5 (the number of vowels).
        #
        # Therefore, the number of lexicographically sorted vowel strings of length n is:
        # C(n + 5 - 1, 5 - 1) = C(n + 4, 4)

        from math import comb
        return comb(n + 4, 4)