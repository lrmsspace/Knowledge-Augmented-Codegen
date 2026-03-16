# Source: https://leetcode.com/problems/count-common-words-with-one-occurrence/   |   Difficulty: Easy
#
# Problem Description:
# Given two string arrays words1 and words2, return the number of strings that appear exactly once in each of the two arrays.
#
# Example:
# Input: words1 = ["leetcode","is","amazing","as","is"], words2 = ["amazing","leetcode","is"]
# Output: 2
# Explanation:
# - "leetcode" appears exactly once in each of the two arrays. We count this string.
# - "amazing" appears exactly once in each of the two arrays. We count this string.
# - "is" appears in each of the two arrays, but there are 2 occurrences of it in words1. We do not count this string.
# - "as" appears once in words1, but does not appear in words2. We do not count this string.
# Thus, there are 2 strings that appear exactly once in each of the two arrays.
#
# Constraints:
# 1 <= words1.length, words2.length <= 1000
# 	1 <= words1[i].length, words2[j].length <= 30
# 	words1[i] and words2[j] consists only of lowercase English letters.
#

class Solution(object):
    def countWords(self, words1, words2):
        """
        :type words1: List[str]
        :type words2: List[str]
        :rtype: int
        """
        from collections import Counter
        
        count1 = Counter(words1)
        count2 = Counter(words2)
        
        result = 0
        
        for word in count1:
            if count1[word] == 1 and count2.get(word, 0) == 1:
                result += 1
                
        return result