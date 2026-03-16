# Source: https://leetcode.com/problems/string-without-aaa-or-bbb/   |   Difficulty: Medium
#
# Problem Description:
# Given two integers a and b, return any string s such that:
#
#
# 	s has length a + b and contains exactly a 'a' letters, and exactly b 'b' letters,
# 	The substring 'aaa' does not occur in s, and
# 	The substring 'bbb' does not occur in s.
#
# Example:
# Input: a = 1, b = 2
# Output: "abb"
# Explanation: "abb", "bab" and "bba" are all correct answers.
#
# Constraints:
# 0 <= a, b <= 100
# 	It is guaranteed such an s exists for the given a and b.
#

class Solution(object):
    def strWithout3a3b(self, a, b):
        """
        :type a: int
        :type b: int
        :rtype: str
        """
        res = []
        while a > 0 or b > 0:
            if a > b:
                if a > 1:
                    res.append('aa')
                    a -= 2
                else:
                    res.append('a')
                    a -= 1
                if b > 0:
                    res.append('b')
                    b -= 1
            elif b > a:
                if b > 1:
                    res.append('bb')
                    b -= 2
                else:
                    res.append('b')
                    b -= 1
                if a > 0:
                    res.append('a')
                    a -= 1
            else:  # a == b
                if a > 0:
                    res.append('ab')
                    a -= 1
                    b -= 1
        return ''.join(res)