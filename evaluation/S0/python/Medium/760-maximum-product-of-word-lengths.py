# Source: https://leetcode.com/problems/maximum-product-of-word-lengths/   |   Difficulty: Medium
#
# Problem Description:
# Given a string array words, return the maximum value of length(word[i]) * length(word[j]) where the two words do not share common letters. If no such two words exist, return 0.
#
# Example:
# Input: words = ["abcw","baz","foo","bar","xtfn","abcdef"]
# Output: 16
# Explanation: The two words can be "abcw", "xtfn".
#
# Constraints:
# 2 <= words.length <= 1000
# 	1 <= words[i].length <= 1000
# 	words[i] consists only of lowercase English letters.
#

class Solution(object):
    def maxProduct(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        n = len(words)
        bit_masks = [0] * n
        
        for i in range(n):
            for char in words[i]:
                bit_masks[i] |= 1 << (ord(char) - ord('a'))
        
        max_product = 0
        for i in range(n):
            for j in range(i + 1, n):
                if bit_masks[i] & bit_masks[j] == 0:
                    max_product = max(max_product, len(words[i]) * len(words[j]))
        
        return max_product