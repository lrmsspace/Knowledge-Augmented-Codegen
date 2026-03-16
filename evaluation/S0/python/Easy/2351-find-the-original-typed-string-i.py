# Source: https://leetcode.com/problems/find-the-original-typed-string-i/   |   Difficulty: Easy
#
# Problem Description:
# Alice is attempting to type a specific string on her computer. However, she tends to be clumsy and may press a key for too long, resulting in a character being typed multiple times.
#
# Although Alice tried to focus on her typing, she is aware that she may still have done this at most once.
#
# You are given a string word, which represents the final output displayed on Alice's screen.
#
# Return the total number of possible original strings that Alice might have intended to type.
#
# Example:
# Input: word = "abbcccc"
#
# Output: 5
#
# Explanation:
#
# The possible strings are: "abbcccc", "abbccc", "abbcc", "abbc", and "abcccc".
#
# Constraints:
# 1 <= word.length <= 100
# 	word consists only of lowercase English letters.
#

class Solution(object):
    def possibleStringCount(self, word):
        """
        :type word: str
        :rtype: int
        """
        count = 1
        i = 0
        n = len(word)
        
        while i < n:
            char_count = 1
            while i + 1 < n and word[i] == word[i + 1]:
                char_count += 1
                i += 1
            
            if char_count > 1:
                count += char_count - 1
            
            i += 1
        
        return count