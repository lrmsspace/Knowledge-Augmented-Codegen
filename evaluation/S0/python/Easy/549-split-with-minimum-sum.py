# Source: https://leetcode.com/problems/split-with-minimum-sum/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer num, split it into two non-negative integers num1 and num2 such that:
#
#
# 	The concatenation of num1 and num2 is a permutation of num.
#
# 	
# 		In other words, the sum of the number of occurrences of each digit in num1 and num2 is equal to the number of occurrences of that digit in num.
# 	
# 	
# 	num1 and num2 can contain leading zeros.
#
#
# Return the minimum possible sum of num1 and num2.
#
# Example:
# Input: num = 4325
# Output: 59
# Explanation: We can split 4325 so that num1 is 24 and num2 is 35, giving a sum of 59. We can prove that 59 is indeed the minimal possible sum.
#
# Constraints:
# 10 <= num <= 109
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def splitNum(self, num):
        """
        :type num: int
        :rtype: int
        """
        digits = list(str(num))
        digits.sort()
        
        num1 = ""
        num2 = ""
        
        for i in range(len(digits)):
            if i % 2 == 0:
                num1 += digits[i]
            else:
                num2 += digits[i]
        
        return int(num1) + int(num2)