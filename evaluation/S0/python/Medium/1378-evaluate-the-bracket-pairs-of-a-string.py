# Source: https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.
#
#
# 	For example, in the string "(name)is(age)yearsold", there are two bracket pairs that contain the keys "name" and "age".
#
#
# You know the values of a wide range of keys. This is represented by a 2D string array knowledge where each knowledge[i] = [keyi, valuei] indicates that key keyi has a value of valuei.
#
# You are tasked to evaluate all of the bracket pairs. When you evaluate a bracket pair that contains some key keyi, you will:
#
#
# 	Replace keyi and the bracket pair with the key's corresponding valuei.
# 	If you do not know the value of the key, you will replace keyi and the bracket pair with a question mark "?" (without the quotation marks).
#
#
# Each key will appear at most once in your knowledge. There will not be any nested brackets in s.
#
# Return the resulting string after evaluating all of the bracket pairs.
#
# Example:
# Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
# Output: "bobistwoyearsold"
# Explanation:
# The key "name" has a value of "bob", so replace "(name)" with "bob".
# The key "age" has a value of "two", so replace "(age)" with "two".
#
# Constraints:
# 1 <= s.length <= 105
# 	0 <= knowledge.length <= 105
# 	knowledge[i].length == 2
# 	1 <= keyi.length, valuei.length <= 10
# 	s consists of lowercase English letters and round brackets '(' and ')'.
# 	Every open bracket '(' in s will have a corresponding close bracket ')'.
# 	The key in each bracket pair of s will be non-empty.
# 	There will not be any nested bracket pairs in s.
# 	keyi and valuei consist of lowercase English letters.
# 	Each keyi in knowledge is unique.
#

class Solution(object):
    def evaluate(self, s, knowledge):
        """
        :type s: str
        :type knowledge: List[List[str]]
        :rtype: str
        """
        knowledge_dict = {key: value for key, value in knowledge}
        result = []
        i = 0
        while i < len(s):
            if s[i] == '(':
                j = i + 1
                while s[j] != ')':
                    j += 1
                key = s[i+1:j]
                result.append(knowledge_dict.get(key, '?'))
                i = j + 1
            else:
                result.append(s[i])
                i += 1
        return ''.join(result)