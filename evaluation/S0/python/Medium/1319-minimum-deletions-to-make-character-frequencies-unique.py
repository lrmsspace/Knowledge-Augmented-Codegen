# Source: https://leetcode.com/problems/minimum-deletions-to-make-character-frequencies-unique/   |   Difficulty: Medium
#
# Problem Description:
# A string s is called good if there are no two different characters in s that have the same frequency.
#
# Given a string s, return the minimum number of characters you need to delete to make s good.
#
# The frequency of a character in a string is the number of times it appears in the string. For example, in the string "aab", the frequency of 'a' is 2, while the frequency of 'b' is 1.
#
# Example:
# Input: s = "aab"
# Output: 0
# Explanation: s is already good.
#
# Constraints:
# 1 <= s.length <= 105
# 	s contains only lowercase English letters.
#

class Solution(object):
    def minDeletions(self, s):
        """
        :type s: str
        :rtype: int
        """
        from collections import Counter

        freq = Counter(s)
        used_frequencies = set()
        deletions = 0

        for char, count in freq.items():
            while count > 0 and count in used_frequencies:
                count -= 1
                deletions += 1
            if count > 0:
                used_frequencies.add(count)

        return deletions