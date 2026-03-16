# Source: https://leetcode.com/problems/odd-string-difference/   |   Difficulty: Easy
#
# Problem Description:
# You are given an array of equal-length strings words. Assume that the length of each string is n.
#
# Each string words[i] can be converted into a difference integer array difference[i] of length n - 1 where difference[i][j] = words[i][j+1] - words[i][j] where 0 <= j <= n - 2. Note that the difference between two letters is the difference between their positions in the alphabet i.e. the position of 'a' is 0, 'b' is 1, and 'z' is 25.
#
#
# 	For example, for the string "acb", the difference integer array is [2 - 0, 1 - 2] = [2, -1].
#
#
# All the strings in words have the same difference integer array, except one. You should find that string.
#
# Return the string in words that has different difference integer array.
#
# Example:
# Input: words = ["adc","wzy","abc"]
# Output: "abc"
# Explanation: 
# - The difference integer array of "adc" is [3 - 0, 2 - 3] = [3, -1].
# - The difference integer array of "wzy" is [25 - 22, 24 - 25]= [3, -1].
# - The difference integer array of "abc" is [1 - 0, 2 - 1] = [1, 1]. 
# The odd array out is [1, 1], so we return the corresponding string, "abc".
#
# Constraints:
# 3 <= words.length <= 100
# 	n == words[i].length
# 	2 <= n <= 20
# 	words[i] consists of lowercase English letters.
#

class Solution(object):
    def oddString(self, words):
        """
        :type words: List[str]
        :rtype: str
        """
        def get_diff_array(word):
            return [ord(word[i+1]) - ord(word[i]) for i in range(len(word)-1)]
        
        diff_map = {}
        
        for word in words:
            diff_array = tuple(get_diff_array(word))
            if diff_array in diff_map:
                diff_map[diff_array].append(word)
            else:
                diff_map[diff_array] = [word]
        
        for diff_array, word_list in diff_map.items():
            if len(word_list) == 1:
                return word_list[0]
        
        return ""