# Source: https://leetcode.com/problems/longest-substring-of-all-vowels-in-order/   |   Difficulty: Medium
#
# Problem Description:
# A string is considered beautiful if it satisfies the following conditions:
#
#
# 	Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
# 	The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
#
#
# For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.
#
# Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.
#
# A substring is a contiguous sequence of characters in a string.
#
# Example:
# Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
# Output: 13
# Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.
#
# Constraints:
# 1 <= word.length <= 5 * 105
# 	word consists of characters 'a', 'e', 'i', 'o', and 'u'.
#

class Solution(object):
    def longestBeautifulSubstring(self, word):
        """
        :type word: str
        :rtype: int
        """
        vowels = 'aeiou'
        max_length = 0
        n = len(word)
        
        i = 0
        while i < n:
            if word[i] == 'a':
                count = 1
                current_length = 1
                j = i + 1
                
                while j < n and word[j] >= word[j - 1]:
                    if word[j] != word[j - 1]:
                        count += 1
                    current_length += 1
                    j += 1
                
                if count == 5:
                    max_length = max(max_length, current_length)
                
                i = j
            else:
                i += 1
        
        return max_length