# Source: https://leetcode.com/problems/decode-string/   |   Difficulty: Medium
#
# Problem Description:
# Given an encoded string, return its decoded string.
#
# The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.
#
# You may assume that the input string is always valid; there are no extra white spaces, square brackets are well-formed, etc. Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there will not be input like 3a or 2[4].
#
# The test cases are generated so that the length of the output will never exceed 105.
#
# Example:
# Input: s = "3[a]2[bc]"
# Output: "aaabcbc"
#
# Constraints:
# 1 <= s.length <= 30
# 	s consists of lowercase English letters, digits, and square brackets '[]'.
# 	s is guaranteed to be a valid input.
# 	All the integers in s are in the range [1, 300].
#

class Solution(object):
    def decodeString(self, s):
        """
        :type s: str
        :rtype: str
        """
        stack = []
        current_num = 0
        current_string = ''
        
        for char in s:
            if char.isdigit():
                current_num = current_num * 10 + int(char)
            elif char == '[':
                stack.append((current_string, current_num))
                current_string = ''
                current_num = 0
            elif char == ']':
                last_string, num = stack.pop()
                current_string = last_string + num * current_string
            else:
                current_string += char
        
        return current_string