# Source: https://leetcode.com/problems/uncommon-words-from-two-sentences/   |   Difficulty: Easy
#
# Problem Description:
# A sentence is a string of single-space separated words where each word consists only of lowercase letters.
#
# A word is uncommon if it appears exactly once in one of the sentences, and does not appear in the other sentence.
#
# Given two sentences s1 and s2, return a list of all the uncommon words. You may return the answer in any order.
#
# Example:
# Input: s1 = "this apple is sweet", s2 = "this apple is sour"
#
# Output: ["sweet","sour"]
#
# Explanation:
#
# The word "sweet" appears only in s1, while the word "sour" appears only in s2.
#
# Constraints:
# 1 <= s1.length, s2.length <= 200
# 	s1 and s2 consist of lowercase English letters and spaces.
# 	s1 and s2 do not have leading or trailing spaces.
# 	All the words in s1 and s2 are separated by a single space.
#

class Solution(object):
    def uncommonFromSentences(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: List[str]
        """
        from collections import Counter
        
        words1 = s1.split()
        words2 = s2.split()
        
        count1 = Counter(words1)
        count2 = Counter(words2)
        
        uncommon_words = []
        
        for word in count1:
            if count1[word] == 1 and word not in count2:
                uncommon_words.append(word)
        
        for word in count2:
            if count2[word] == 1 and word not in count1:
                uncommon_words.append(word)
        
        return uncommon_words