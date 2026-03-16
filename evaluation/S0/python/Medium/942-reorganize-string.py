# Source: https://leetcode.com/problems/reorganize-string/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, rearrange the characters of s so that any two adjacent characters are not the same.
#
# Return any possible rearrangement of s or return "" if not possible.
#
# Example:
# Input: s = "aab"
# Output: "aba"
#
# Constraints:
# 1 <= s.length <= 500
# 	s consists of lowercase English letters.
#

class Solution(object):
    def reorganizeString(self, s):
        """
        :type s: str
        :rtype: str
        """
        from collections import Counter
        import heapq

        count = Counter(s)
        max_heap = [(-freq, char) for char, freq in count.items()]
        heapq.heapify(max_heap)

        prev_freq, prev_char = 0, ''
        result = []

        while max_heap:
            freq, char = heapq.heappop(max_heap)
            result.append(char)

            if prev_freq < 0:
                heapq.heappush(max_heap, (prev_freq, prev_char))

            prev_freq, prev_char = freq + 1, char

        reorganized = ''.join(result)
        if len(reorganized) != len(s):
            return ""
        return reorganized