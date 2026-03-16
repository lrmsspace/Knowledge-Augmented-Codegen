# Source: https://leetcode.com/problems/count-beautiful-substrings-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and a positive integer k.
#
# Let vowels and consonants be the number of vowels and consonants in a string.
#
# A string is beautiful if:
#
#
# 	vowels == consonants.
# 	(vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is divisible by k.
#
#
# Return the number of non-empty beautiful substrings in the given string s.
#
# A substring is a contiguous sequence of characters in a string.
#
# Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
#
# Consonant letters in English are every letter except vowels.
#
# Example:
# Input: s = "baeyh", k = 2
# Output: 2
# Explanation: There are 2 beautiful substrings in the given string.
# - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["y","h"]).
# You can see that string "aeyh" is beautiful as vowels == consonants and vowels * consonants % k == 0.
# - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["b","y"]).
# You can see that string "baey" is beautiful as vowels == consonants and vowels * consonants % k == 0.
# It can be shown that there are only 2 beautiful substrings in the given string.
#
# Constraints:
# 1 <= s.length <= 5 * 104
# 	1 <= k <= 1000
# 	s consists of only English lowercase letters.
#

class Solution(object):
    def beautifulSubstrings(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        n = len(s)
        vowels = set('aeiou')
        count = 0
        
        for i in range(n):
            v_count = 0
            c_count = 0
            
            for j in range(i, n):
                if s[j] in vowels:
                    v_count += 1
                else:
                    c_count += 1
                
                if v_count == c_count and (v_count * c_count) % k == 0:
                    count += 1
        
        return count