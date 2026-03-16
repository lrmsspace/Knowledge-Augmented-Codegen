# Source: https://leetcode.com/problems/add-binary/   |   Difficulty: Easy
#
# Problem Description:
# Given two binary strings a and b, return their sum as a binary string.
#
# Example:
# Input: a = "11", b = "1"
# Output: "100"
#
# Constraints:
# 1 <= a.length, b.length <= 104
# 	a and b consist only of '0' or '1' characters.
# 	Each string does not contain leading zeros except for the zero itself.
#

class Solution(object):
    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """
        result = []
        carry = 0
        i, j = len(a) - 1, len(b) - 1

        while i >= 0 or j >= 0 or carry:
            sum = carry
            if i >= 0:
                sum += int(a[i])
                i -= 1
            if j >= 0:
                sum += int(b[j])
                j -= 1

            result.append(str(sum % 2))
            carry = sum // 2

        return ''.join(reversed(result))