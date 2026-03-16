# Source: https://leetcode.com/problems/print-words-vertically/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s. Return all the words vertically in the same order in which they appear in s.
# Words are returned as a list of strings, complete with spaces when is necessary. (Trailing spaces are not allowed).
# Each word would be put on only one column and that in one column there will be only one word.
#
# Example:
# Input: s = "HOW ARE YOU"
# Output: ["HAY","ORO","WEU"]
# Explanation: Each word is printed vertically. 
#  "HAY"
#  "ORO"
#  "WEU"
#
# Constraints:
# 1 <= s.length <= 200
# 	s contains only upper case English letters.
# 	It's guaranteed that there is only one space between 2 words.
#

class Solution(object):
    def printVertically(self, s):
        """
        :type s: str
        :rtype: List[str]
        """
        words = s.split()
        max_len = max(len(word) for word in words)
        result = []
        
        for i in range(max_len):
            vertical_word = []
            for word in words:
                if i < len(word):
                    vertical_word.append(word[i])
                else:
                    vertical_word.append(' ')
            # Remove trailing spaces
            while vertical_word and vertical_word[-1] == ' ':
                vertical_word.pop()
            result.append(''.join(vertical_word))
        
        return result