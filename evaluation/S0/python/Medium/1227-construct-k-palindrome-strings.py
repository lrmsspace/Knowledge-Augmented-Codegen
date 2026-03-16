# Source: https://leetcode.com/problems/construct-k-palindrome-strings/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s and an integer k, return true if you can use all the characters in s to construct non-empty k palindrome strings or false otherwise.
#
# Example:
# Input: s = "annabelle", k = 2
# Output: true
# Explanation: You can construct two palindromes using all characters in s.
# Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
# 	1 <= k <= 105
#

class Solution(object):
    def canConstruct(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: bool
        """
        from collections import Counter

        if k > len(s):
            return False

        char_count = Counter(s)
        odd_count = sum(1 for count in char_count.values() if count % 2 != 0)

        return odd_count <= k