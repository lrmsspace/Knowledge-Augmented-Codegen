# Source: https://leetcode.com/problems/count-vowel-strings-in-ranges/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of strings words and a 2D array of integers queries.
#
# Each query queries[i] = [li, ri] asks us to find the number of strings present at the indices ranging from li to ri (both inclusive) of words that start and end with a vowel.
#
# Return an array ans of size queries.length, where ans[i] is the answer to the ith query.
#
# Note that the vowel letters are 'a', 'e', 'i', 'o', and 'u'.
#
# Example:
# Input: words = ["aba","bcb","ece","aa","e"], queries = [[0,2],[1,4],[1,1]]
# Output: [2,3,0]
# Explanation: The strings starting and ending with a vowel are "aba", "ece", "aa" and "e".
# The answer to the query [0,2] is 2 (strings "aba" and "ece").
# to query [1,4] is 3 (strings "ece", "aa", "e").
# to query [1,1] is 0.
# We return [2,3,0].
#
# Constraints:
# 1 <= words.length <= 105
# 	1 <= words[i].length <= 40
# 	words[i] consists only of lowercase English letters.
# 	sum(words[i].length) <= 3 * 105
# 	1 <= queries.length <= 105
# 	0 <= li <= ri < words.length
#

class Solution(object):
    def vowelStrings(self, words, queries):
        """
        :type words: List[str]
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        vowels = set('aeiou')
        n = len(words)
        
        # Precompute a prefix sum array where prefix[i] indicates the number of valid words from words[0] to words[i-1]
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + (1 if words[i][0] in vowels and words[i][-1] in vowels else 0)
        
        result = []
        for l, r in queries:
            result.append(prefix[r + 1] - prefix[l])
        
        return result