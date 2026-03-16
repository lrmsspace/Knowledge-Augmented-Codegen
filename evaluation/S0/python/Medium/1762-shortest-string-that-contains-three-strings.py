# Source: https://leetcode.com/problems/shortest-string-that-contains-three-strings/   |   Difficulty: Medium
#
# Problem Description:
# Given three strings a, b, and c, your task is to find a string that has the minimum length and contains all three strings as substrings.
# If there are multiple such strings, return the lexicographically smallest one.
#
# Return a string denoting the answer to the problem.
#
# Notes
#
#
# 	A string a is lexicographically smaller than a string b (of the same length) if in the first position where a and b differ, string a has a letter that appears earlier in the alphabet than the corresponding letter in b.
# 	A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: a = "abc", b = "bca", c = "aaa"
# Output: "aaabca"
# Explanation:  We show that "aaabca" contains all the given strings: a = ans[2...4], b = ans[3..5], c = ans[0..2]. It can be shown that the length of the resulting string would be at least 6 and "aaabca" is the lexicographically smallest one.
#
# Constraints:
# 1 <= a.length, b.length, c.length <= 100
# 	a, b, c consist only of lowercase English letters.
#

class Solution(object):
    def minimumString(self, a, b, c):
        """
        :type a: str
        :type b: str
        :type c: str
        :rtype: str
        """
        def merge(s1, s2):
            max_overlap = 0
            for i in range(1, min(len(s1), len(s2)) + 1):
                if s1[-i:] == s2[:i]:
                    max_overlap = i
            return s1 + s2[max_overlap:]

        from itertools import permutations

        candidates = []
        for perm in permutations([a, b, c]):
            merged = merge(merge(perm[0], perm[1]), perm[2])
            candidates.append(merged)

        return min(candidates, key=lambda x: (len(x), x))