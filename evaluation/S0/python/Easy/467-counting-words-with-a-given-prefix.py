# Source: https://leetcode.com/problems/counting-words-with-a-given-prefix/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of strings words and a string pref.
#
# Return the number of strings in words that contain pref as a prefix.
#
# A prefix of a string s is any leading contiguous substring of s.
#
# Example:
# Input: words = ["pay","attention","practice","attend"], pref = "at"
# Output: 2
# Explanation: The 2 strings that contain "at" as a prefix are: "attention" and "attend".
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length, pref.length <= 100
# 	words[i] and pref consist of lowercase English letters.
#

class Solution(object):
    def prefixCount(self, words, pref):
        """
        :type words: List[str]
        :type pref: str
        :rtype: int
        """
        count = 0
        for word in words:
            if word.startswith(pref):
                count += 1
        return count