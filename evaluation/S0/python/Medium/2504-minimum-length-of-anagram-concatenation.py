# Source: https://leetcode.com/problems/minimum-length-of-anagram-concatenation/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s, which is known to be a concatenation of anagrams of some string t.
#
# Return the minimum possible length of the string t.
#
# An anagram is formed by rearranging the letters of a string. For example, "aab", "aba", and, "baa" are anagrams of "aab".
#
# Example:
# Input: s = "abba"
#
# Output: 2
#
# Explanation:
#
# One possible string t could be "ba".
#
# Constraints:
# 1 <= s.length <= 105
# 	s consist only of lowercase English letters.
#

class Solution(object):
    def minAnagramLength(self, s):
        """
        :type s: str
        :rtype: int
        """
        from collections import Counter

        n = len(s)
        left, right = 1, n

        def can_form_anagrams(length):
            if n % length != 0:
                return False

            segment_count = n // length
            target_count = Counter(s[:length])

            for i in range(1, segment_count):
                segment = s[i * length:(i + 1) * length]
                if Counter(segment) != target_count:
                    return False

            return True

        while left < right:
            mid = (left + right) // 2
            if can_form_anagrams(mid):
                right = mid
            else:
                left = mid + 1

        return left