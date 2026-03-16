# Source: https://leetcode.com/problems/minimum-number-of-flips-to-make-the-binary-string-alternating/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string s. You are allowed to perform two types of operations on the string in any sequence:
#
#
# 	Type-1: Remove the character at the start of the string s and append it to the end of the string.
# 	Type-2: Pick any character in s and flip its value, i.e., if its value is '0' it becomes '1' and vice-versa.
#
#
# Return the minimum number of type-2 operations you need to perform such that s becomes alternating.
#
# The string is called alternating if no two adjacent characters are equal.
#
#
# 	For example, the strings "010" and "1010" are alternating, while the string "0100" is not.
#
# Example:
# Input: s = "111000"
# Output: 2
# Explanation: Use the first operation two times to make s = "100011".
# Then, use the second operation on the third and sixth elements to make s = "101010".
#
# Constraints:
# 1 <= s.length <= 105
# 	s[i] is either '0' or '1'.
#

class Solution(object):
    def minFlips(self, s):
        """
        :type s: str
        :rtype: int
        """
        n = len(s)
        s = s + s  # Concatenate string to itself to simulate rotations
        alt1 = ''.join('0' if i % 2 == 0 else '1' for i in range(2 * n))  # Pattern starting with '0'
        alt2 = ''.join('1' if i % 2 == 0 else '0' for i in range(2 * n))  # Pattern starting with '1'

        diff1 = diff2 = 0
        min_flips = float('inf')

        for i in range(2 * n):
            if s[i] != alt1[i]:
                diff1 += 1
            if s[i] != alt2[i]:
                diff2 += 1

            if i >= n:
                if s[i - n] != alt1[i - n]:
                    diff1 -= 1
                if s[i - n] != alt2[i - n]:
                    diff2 -= 1

            if i >= n - 1:
                min_flips = min(min_flips, diff1, diff2)

        return min_flips