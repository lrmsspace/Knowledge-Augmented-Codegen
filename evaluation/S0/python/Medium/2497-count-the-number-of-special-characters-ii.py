# Source: https://leetcode.com/problems/count-the-number-of-special-characters-ii/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.
#
# Return the number of special letters in word.
#
# Example:
# Input: word = "aaAbcBC"
#
# Output: 3
#
# Explanation:
#
# The special characters are 'a', 'b', and 'c'.
#
# Constraints:
# 1 <= word.length <= 2 * 105
# 	word consists of only lowercase and uppercase English letters.
#

class Solution(object):
    def numberOfSpecialChars(self, word):
        """
        :type word: str
        :rtype: int
        """
        lower_set = set()
        special_set = set()
        
        for char in word:
            if char.islower():
                lower_set.add(char)
            elif char.isupper():
                if char.lower() in lower_set:
                    special_set.add(char.lower())
        
        return len(special_set)