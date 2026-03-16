# Source: https://leetcode.com/problems/find-common-characters/   |   Difficulty: Easy
#
# Problem Description:
# Given a string array words, return an array of all characters that show up in all strings within the words (including duplicates). You may return the answer in any order.
#
# Example:
# Input: words = ["bella","label","roller"]
# Output: ["e","l","l"]
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 100
# 	words[i] consists of lowercase English letters.
#

class Solution(object):
    def commonChars(self, words):
        """
        :type words: List[str]
        :rtype: List[str]
        """
        from collections import Counter
        common_count = Counter(words[0])
        
        for word in words[1:]:
            common_count &= Counter(word)
        
        result = []
        for char, count in common_count.items():
            result.extend([char] * count)
        
        return result