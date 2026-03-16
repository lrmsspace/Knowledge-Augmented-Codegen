# Source: https://leetcode.com/problems/k-similar-strings/   |   Difficulty: Hard
#
# Problem Description:
# Strings s1 and s2 are k-similar (for some non-negative integer k) if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.
#
# Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.
#
# Example:
# Input: s1 = "ab", s2 = "ba"
# Output: 1
# Explanation: The two string are 1-similar because we can use one swap to change s1 to s2: "ab" --> "ba".
#
# Constraints:
# 1 <= s1.length <= 20
# 	s2.length == s1.length
# 	s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
# 	s2 is an anagram of s1.
#

class Solution(object):
    def kSimilarity(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: int
        """
        from collections import deque

        if s1 == s2:
            return 0

        def neighbors(s):
            res = []
            i = 0
            while s[i] == s2[i]:
                i += 1
            for j in range(i + 1, len(s)):
                if s[j] == s2[i] and s[j] != s2[j]:
                    new_s = list(s)
                    new_s[i], new_s[j] = new_s[j], new_s[i]
                    res.append(''.join(new_s))
            return res

        queue = deque([(s1, 0)])
        visited = set([s1])

        while queue:
            curr, steps = queue.popleft()
            for nei in neighbors(curr):
                if nei not in visited:
                    if nei == s2:
                        return steps + 1
                    visited.add(nei)
                    queue.append((nei, steps + 1))
        return -1