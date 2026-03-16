# Source: https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s and an integer k, return the maximum number of vowel letters in any substring of s with length k.
#
# Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
#
# Example:
# Input: s = "abciiidef", k = 3
# Output: 3
# Explanation: The substring "iii" contains 3 vowel letters.
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of lowercase English letters.
# 	1 <= k <= s.length
#

class Solution(object):
    def maxVowels(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        vowels = set('aeiou')
        max_count = 0
        current_count = 0
        
        # Initialize the first window
        for i in range(k):
            if s[i] in vowels:
                current_count += 1
        max_count = current_count
        
        # Slide the window
        for i in range(k, len(s)):
            if s[i] in vowels:
                current_count += 1
            if s[i - k] in vowels:
                current_count -= 1
            max_count = max(max_count, current_count)
        
        return max_count