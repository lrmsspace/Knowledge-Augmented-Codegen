# Source: https://leetcode.com/problems/using-a-robot-to-print-the-lexicographically-smallest-string/   |   Difficulty: Medium
#
# Problem Description:
# You are given a string s and a robot that currently holds an empty string t. Apply one of the following operations until s and t are both empty:
#
#
# 	Remove the first character of a string s and give it to the robot. The robot will append this character to the string t.
# 	Remove the last character of a string t and give it to the robot. The robot will write this character on paper.
#
#
# Return the lexicographically smallest string that can be written on the paper.
#
# Example:
# Input: s = "zza"
# Output: "azz"
# Explanation: Let p denote the written string.
# Initially p="", s="zza", t="".
# Perform first operation three times p="", s="", t="zza".
# Perform second operation three times p="azz", s="", t="".
#
# Constraints:
# 1 <= s.length <= 105
# 	s consists of only English lowercase letters.
#

class Solution(object):
    def robotWithString(self, s):
        """
        :type s: str
        :rtype: str
        """
        from collections import Counter

        t = []
        result = []
        count = Counter(s)
        min_char = 'a'

        for char in s:
            t.append(char)
            count[char] -= 1

            while min_char <= 'z' and count[min_char] == 0:
                min_char = chr(ord(min_char) + 1)

            while t and t[-1] <= min_char:
                result.append(t.pop())

        return ''.join(result)