# Source: https://leetcode.com/problems/occurrences-after-bigram/   |   Difficulty: Easy
#
# Problem Description:
# Given two strings first and second, consider occurrences in some text of the form "first second third", where second comes immediately after first, and third comes immediately after second.
#
# Return an array of all the words third for each occurrence of "first second third".
#
# Example:
# Input: text = "alice is a good girl she is a good student", first = "a", second = "good"
# Output: ["girl","student"]
#
# Constraints:
# 1 <= text.length <= 1000
# 	text consists of lowercase English letters and spaces.
# 	All the words in text are separated by a single space.
# 	1 <= first.length, second.length <= 10
# 	first and second consist of lowercase English letters.
# 	text will not have any leading or trailing spaces.
#

class Solution(object):
    def findOcurrences(self, text, first, second):
        """
        :type text: str
        :type first: str
        :type second: str
        :rtype: List[str]
        """
        words = text.split()
        result = []
        
        for i in range(len(words) - 2):
            if words[i] == first and words[i + 1] == second:
                result.append(words[i + 2])
        
        return result