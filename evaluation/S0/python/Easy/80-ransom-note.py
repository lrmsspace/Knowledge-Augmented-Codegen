# Source: https://leetcode.com/problems/ransom-note/   |   Difficulty: Easy
#
# Problem Description:
# Given two strings ransomNote and magazine, return true if ransomNote can be constructed by using the letters from magazine and false otherwise.
#
# Each letter in magazine can only be used once in ransomNote.
#
# Example:
# Input: ransomNote = "a", magazine = "b"
# Output: false
#
# Constraints:
# 1 <= ransomNote.length, magazine.length <= 105
# 	ransomNote and magazine consist of lowercase English letters.
#

class Solution(object):
    def canConstruct(self, ransomNote, magazine):
        """
        :type ransomNote: str
        :type magazine: str
        :rtype: bool
        """
        from collections import Counter
        ransom_counter = Counter(ransomNote)
        magazine_counter = Counter(magazine)
        
        for char, count in ransom_counter.items():
            if magazine_counter[char] < count:
                return False
        return True