# Source: https://leetcode.com/problems/verifying-an-alien-dictionary/   |   Difficulty: Easy
#
# Problem Description:
# In an alien language, surprisingly, they also use English lowercase letters, but possibly in a different order. The order of the alphabet is some permutation of lowercase letters.
#
# Given a sequence of words written in the alien language, and the order of the alphabet, return true if and only if the given words are sorted lexicographically in this alien language.
#
# Example:
# Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
# Output: true
# Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 20
# 	order.length == 26
# 	All characters in words[i] and order are English lowercase letters.
#

class Solution(object):
    def isAlienSorted(self, words, order):
        """
        :type words: List[str]
        :type order: str
        :rtype: bool
        """
        order_map = {char: index for index, char in enumerate(order)}
        
        for i in range(len(words) - 1):
            word1 = words[i]
            word2 = words[i + 1]
            min_length = min(len(word1), len(word2))
            
            for j in range(min_length):
                if order_map[word1[j]] < order_map[word2[j]]:
                    break
                elif order_map[word1[j]] > order_map[word2[j]]:
                    return False
            else:
                if len(word1) > len(word2):
                    return False
        
        return True