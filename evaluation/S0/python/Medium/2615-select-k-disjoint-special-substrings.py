# Source: https://leetcode.com/problems/select-k-disjoint-special-substrings/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s of length n and an integer k, determine whether it is possible to select k disjoint special substrings.
#
# A special substring is a substring where:
#
#
# 	Any character present inside the substring should not appear outside it in the string.
# 	The substring is not the entire string s.
#
#
# Note that all k substrings must be disjoint, meaning they cannot overlap.
#
# Return true if it is possible to select k such disjoint special substrings; otherwise, return false.
#
# Example:
# Input: s = "abcdbaefab", k = 2
#
# Output: true
#
# Explanation:
#
#
# 	We can select two disjoint special substrings: "cd" and "ef".
# 	"cd" contains the characters 'c' and 'd', which do not appear elsewhere in s.
# 	"ef" contains the characters 'e' and 'f', which do not appear elsewhere in s.
#
# Constraints:
# 2 <= n == s.length <= 5 * 104
# 	0 <= k <= 26
# 	s consists only of lowercase English letters.
#

class Solution(object):
    def maxSubstringLength(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: bool
        """
        from collections import Counter

        char_count = Counter(s)
        special_substrings = 0
        visited = set()
        i = 0
        n = len(s)

        while i < n:
            if s[i] in visited:
                i += 1
                continue

            if char_count[s[i]] == 1:
                special_substrings += 1
                visited.add(s[i])
                i += 1
            else:
                j = i + 1
                substring_chars = set(s[i])

                while j < n:
                    substring_chars.add(s[j])
                    if all(char_count[c] == 1 for c in substring_chars):
                        special_substrings += 1
                        visited.update(substring_chars)
                        break
                    j += 1

                i = j + 1

            if special_substrings >= k:
                return True

        return special_substrings >= k