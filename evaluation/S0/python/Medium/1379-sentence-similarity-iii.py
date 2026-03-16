# Source: https://leetcode.com/problems/sentence-similarity-iii/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings sentence1 and sentence2, each representing a sentence composed of words. A sentence is a list of words that are separated by a single space with no leading or trailing spaces. Each word consists of only uppercase and lowercase English characters.
#
# Two sentences s1 and s2 are considered similar if it is possible to insert an arbitrary sentence (possibly empty) inside one of these sentences such that the two sentences become equal. Note that the inserted sentence must be separated from existing words by spaces.
#
# For example,
#
#
# 	s1 = "Hello Jane" and s2 = "Hello my name is Jane" can be made equal by inserting "my name is" between "Hello" and "Jane" in s1.
# 	s1 = "Frog cool" and s2 = "Frogs are cool" are not similar, since although there is a sentence "s are" inserted into s1, it is not separated from "Frog" by a space.
#
#
# Given two sentences sentence1 and sentence2, return true if sentence1 and sentence2 are similar. Otherwise, return false.
#
# Example:
# Input: sentence1 = "My name is Haley", sentence2 = "My Haley"
#
# Output: true
#
# Explanation:
#
# sentence2 can be turned to sentence1 by inserting "name is" between "My" and "Haley".
#
# Constraints:
# 1 <= sentence1.length, sentence2.length <= 100
# 	sentence1 and sentence2 consist of lowercase and uppercase English letters and spaces.
# 	The words in sentence1 and sentence2 are separated by a single space.
#

class Solution(object):
    def areSentencesSimilar(self, sentence1, sentence2):
        """
        :type sentence1: str
        :type sentence2: str
        :rtype: bool
        """
        words1 = sentence1.split()
        words2 = sentence2.split()
        
        len1, len2 = len(words1), len(words2)
        
        # Ensure words1 is the shorter sentence
        if len1 > len2:
            words1, words2 = words2, words1
            len1, len2 = len2, len1
        
        # Check prefix
        i = 0
        while i < len1 and words1[i] == words2[i]:
            i += 1
        
        # Check suffix
        j = 0
        while j < len1 - i and words1[len1 - 1 - j] == words2[len2 - 1 - j]:
            j += 1
        
        return i + j >= len1