# Source: https://leetcode.com/problems/longest-substring-of-one-repeating-character/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.
#
# The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].
#
# Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.
#
# Example:
# Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
# Output: [3,3,4]
# Explanation: 
# - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
# - 2nd query updates s = "bbbccc". 
#   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
# - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
# Thus, we return [3,3,4].
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
# 	k == queryCharacters.length == queryIndices.length
# 	1 <= k <= 105
# 	queryCharacters consists of lowercase English letters.
# 	0 <= queryIndices[i] < s.length
#

class Solution(object):
    def longestRepeating(self, s, queryCharacters, queryIndices):
        """
        :type s: str
        :type queryCharacters: str
        :type queryIndices: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict
        import bisect

        n = len(s)
        max_len = 1
        char_intervals = defaultdict(list)

        def add_interval(c, start, end):
            char_intervals[c].append((start, end))

        def remove_interval(c, start, end):
            char_intervals[c].remove((start, end))

        i = 0
        while i < n:
            j = i
            while j < n and s[j] == s[i]:
                j += 1
            add_interval(s[i], i, j - 1)
            max_len = max(max_len, j - i)
            i = j

        res = []
        s = list(s)

        for c, idx in zip(queryCharacters, queryIndices):
            if s[idx] == c:
                res.append(max_len)
                continue

            old_char = s[idx]
            s[idx] = c

            left = idx - 1
            right = idx + 1

            new_start = idx
            new_end = idx

            if left >= 0 and s[left] == c:
                for start, end in char_intervals[c]:
                    if end == left:
                        new_start = start
                        remove_interval(c, start, end)
                        break

            if right < n and s[right] == c:
                for start, end in char_intervals[c]:
                    if start == right:
                        new_end = end
                        remove_interval(c, start, end)
                        break

            add_interval(c, new_start, new_end)
            max_len = max(max_len, new_end - new_start + 1)

            for start, end in char_intervals[old_char][:]:
                if start <= idx <= end:
                    remove_interval(old_char, start, end)
                    if start < idx:
                        add_interval(old_char, start, idx - 1)
                    if idx < end:
                        add_interval(old_char, idx + 1, end)
                    break

            res.append(max_len)

        return res