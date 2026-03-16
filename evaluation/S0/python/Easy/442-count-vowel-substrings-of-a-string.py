# Source: https://leetcode.com/problems/count-vowel-substrings-of-a-string/   |   Difficulty: Easy
#
# Problem Description:
# A substring is a contiguous (non-empty) sequence of characters within a string.
#
# A vowel substring is a substring that only consists of vowels ('a', 'e', 'i', 'o', and 'u') and has all five vowels present in it.
#
# Given a string word, return the number of vowel substrings in word.
#
# Example:
# Input: word = "aeiouu"
# Output: 2
# Explanation: The vowel substrings of word are as follows (underlined):
# - "aeiouu"
# - "aeiouu"
#
# Constraints:
# 1 <= word.length <= 100
# 	word consists of lowercase English letters only.
#

class Solution(object):
    def countVowelSubstrings(self, word):
        """
        :type word: str
        :rtype: int
        """
        vowels = set('aeiou')
        n = len(word)
        count = 0
        
        for i in range(n):
            if word[i] not in vowels:
                continue
            
            seen = set()
            for j in range(i, n):
                if word[j] in vowels:
                    seen.add(word[j])
                    if len(seen) == 5:
                        count += 1
                else:
                    break
        
        return count