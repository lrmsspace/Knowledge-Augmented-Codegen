# Source: https://leetcode.com/problems/special-binary-string/   |   Difficulty: Hard
#
# Problem Description:
# Special binary strings are binary strings with the following two properties:
#
#
# 	The number of 0's is equal to the number of 1's.
# 	Every prefix of the binary string has at least as many 1's as 0's.
#
#
# You are given a special binary string s.
#
# A move consists of choosing two consecutive, non-empty, special substrings of s, and swapping them. Two strings are consecutive if the last character of the first string is exactly one index before the first character of the second string.
#
# Return the lexicographically largest resulting string possible after applying the mentioned operations on the string.
#
# Example:
# Input: s = "11011000"
# Output: "11100100"
# Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
# This is the lexicographically largest string possible after some number of swaps.
#
# Constraints:
# 1 <= s.length <= 50
# 	s[i] is either '0' or '1'.
# 	s is a special binary string.
#

class Solution(object):
    def makeLargestSpecial(self, s):
        """
        :type s: str
        :rtype: str
        """
        count = 0
        i = 0
        specials = []
        for j in range(len(s)):
            if s[j] == '1':
                count += 1
            else:
                count -= 1
            if count == 0:
                specials.append('1' + self.makeLargestSpecial(s[i+1:j]) + '0')
                i = j + 1
        specials.sort(reverse=True)
        return ''.join(specials)