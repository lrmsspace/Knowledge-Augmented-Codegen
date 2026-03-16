# Source: https://leetcode.com/problems/reverse-words-in-a-string-iii/   |   Difficulty: Easy
#
# Problem Description:
# Given a string s, reverse the order of characters in each word within a sentence while still preserving whitespace and initial word order.
#
# Example:
# Input: s = "Let's take LeetCode contest"
# Output: "s'teL ekat edoCteeL tsetnoc"
#
# Constraints:
# 1 <= s.length <= 5 * 104
# 	s contains printable ASCII characters.
# 	s does not contain any leading or trailing spaces.
# 	There is at least one word in s.
# 	All the words in s are separated by a single space.
#

class Solution(object):
    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """
        words = s.split(' ')
        reversed_words = [word[::-1] for word in words]
        return ' '.join(reversed_words)