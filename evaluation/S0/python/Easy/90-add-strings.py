# Source: https://leetcode.com/problems/add-strings/   |   Difficulty: Easy
#
# Problem Description:
# Given two non-negative integers, num1 and num2 represented as string, return the sum of num1 and num2 as a string.
#
# You must solve the problem without using any built-in library for handling large integers (such as BigInteger). You must also not convert the inputs to integers directly.
#
# Example:
# Input: num1 = "11", num2 = "123"
# Output: "134"
#
# Constraints:
# 1 <= num1.length, num2.length <= 104
# 	num1 and num2 consist of only digits.
# 	num1 and num2 don't have any leading zeros except for the zero itself.
#

class Solution(object):
    def addStrings(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """
        i, j = len(num1) - 1, len(num2) - 1
        carry = 0
        result = []
        
        while i >= 0 or j >= 0 or carry:
            digit1 = int(num1[i]) if i >= 0 else 0
            digit2 = int(num2[j]) if j >= 0 else 0
            
            total = digit1 + digit2 + carry
            carry = total // 10
            result.append(str(total % 10))
            
            i -= 1
            j -= 1
        
        return ''.join(reversed(result))