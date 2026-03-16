# Source: https://leetcode.com/problems/replace-all-digits-with-characters/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 0-indexed string s that has lowercase English letters in its even indices and digits in its odd indices.
#
# You must perform an operation shift(c, x), where c is a character and x is a digit, that returns the xth character after c.
#
#
# 	For example, shift('a', 5) = 'f' and shift('x', 0) = 'x'.
#
#
# For every odd index i, you want to replace the digit s[i] with the result of the shift(s[i-1], s[i]) operation.
#
# Return s after replacing all digits. It is guaranteed that shift(s[i-1], s[i]) will never exceed 'z'.
#
# Note that shift(c, x) is not a preloaded function, but an operation to be implemented as part of the solution.
#
# Example:
# Input: s = "a1c1e1"
# Output: "abcdef"
# Explanation: The digits are replaced as follows:
# - s[1] -> shift('a',1) = 'b'
# - s[3] -> shift('c',1) = 'd'
# - s[5] -> shift('e',1) = 'f'
#
# Constraints:
# 1 <= s.length <= 100
# 	s consists only of lowercase English letters and digits.
# 	shift(s[i-1], s[i]) <= 'z' for all odd indices i.
#

class Solution(object):
    def replaceDigits(self, s):
        """
        :type s: str
        :rtype: str
        """
        res = list(s)
        for i in range(1, len(s), 2):
            res[i] = chr(ord(res[i-1]) + int(res[i]))
        return ''.join(res)