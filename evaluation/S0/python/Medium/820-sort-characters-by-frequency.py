# Source: https://leetcode.com/problems/sort-characters-by-frequency/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, sort it in decreasing order based on the frequency of the characters. The frequency of a character is the number of times it appears in the string.
#
# Return the sorted string. If there are multiple answers, return any of them.
#
# Example:
# Input: s = "tree"
# Output: "eert"
# Explanation: 'e' appears twice while 'r' and 't' both appear once.
# So 'e' must appear before both 'r' and 't'. Therefore "eetr" is also a valid answer.
#
# Constraints:
# 1 <= s.length <= 5 * 105
# 	s consists of uppercase and lowercase English letters and digits.
#

class Solution(object):
    def frequencySort(self, s):
        """
        :type s: str
        :rtype: str
        """
        from collections import Counter
        freq = Counter(s)
        sorted_chars = sorted(freq.items(), key=lambda x: x[1], reverse=True)
        result = []
        for char, count in sorted_chars:
            result.append(char * count)
        return ''.join(result)