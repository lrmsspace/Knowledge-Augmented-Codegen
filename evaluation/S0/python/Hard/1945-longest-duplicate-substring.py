# Source: https://leetcode.com/problems/longest-duplicate-substring/   |   Difficulty: Hard
#
# Problem Description:
# Given a string s, consider all duplicated substrings: (contiguous) substrings of s that occur 2 or more times. The occurrences may overlap.
#
# Return any duplicated substring that has the longest possible length. If s does not have a duplicated substring, the answer is "".
#
# Example:
# Input: s = "banana"
# Output: "ana"
#
# Constraints:
# 2 <= s.length <= 3 * 104
# 	s consists of lowercase English letters.
#

class Solution(object):
    def longestDupSubstring(self, s):
        """
        :type s: str
        :rtype: str
        """
        def search(length):
            """Search a substring of given length that occurs at least 2 times.
            Return start position if found, else -1."""
            a = 256
            modulus = 2**32

            h = 0
            for i in range(length):
                h = (h * a + ord(s[i])) % modulus
            seen = {h}
            aL = pow(a, length, modulus)

            for start in range(1, len(s) - length + 1):
                h = (h * a - ord(s[start - 1]) * aL + ord(s[start + length - 1])) % modulus
                if h in seen:
                    return start
                seen.add(h)
            return -1

        left, right = 1, len(s)
        result_start = -1
        while left <= right:
            mid = left + (right - left) // 2
            start = search(mid)
            if start != -1:
                left = mid + 1
                result_start = start
            else:
                right = mid - 1

        if result_start != -1:
            return s[result_start:result_start + left - 1]
        return ""