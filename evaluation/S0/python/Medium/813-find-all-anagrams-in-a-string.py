# Source: https://leetcode.com/problems/find-all-anagrams-in-a-string/   |   Difficulty: Medium
#
# Problem Description:
# Given two strings s and p, return an array of all the start indices of p's anagrams in s. You may return the answer in any order.
#
# Example:
# Input: s = "cbaebabacd", p = "abc"
# Output: [0,6]
# Explanation:
# The substring with start index = 0 is "cba", which is an anagram of "abc".
# The substring with start index = 6 is "bac", which is an anagram of "abc".
#
# Constraints:
# 1 <= s.length, p.length <= 3 * 104
# 	s and p consist of lowercase English letters.
#

class Solution(object):
    def findAnagrams(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: List[int]
        """
        from collections import Counter

        len_s, len_p = len(s), len(p)
        if len_s < len_p:
            return []

        p_count = Counter(p)
        s_count = Counter(s[:len_p])

        result = []
        for i in range(len_s - len_p + 1):
            if i > 0:
                s_count[s[i - 1]] -= 1
                if s_count[s[i - 1]] == 0:
                    del s_count[s[i - 1]]
                s_count[s[i + len_p - 1]] += 1

            if s_count == p_count:
                result.append(i)

        return result