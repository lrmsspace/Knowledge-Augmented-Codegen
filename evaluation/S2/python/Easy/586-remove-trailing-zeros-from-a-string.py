# Source: https://leetcode.com/problems/remove-trailing-zeros-from-a-string/   |   Difficulty: Easy
#
# Problem Description:
# Given a positive integer num represented as a string, return the integer num without trailing zeros as a string.
#
# Example:
# Input: num = "51230100"
# Output: "512301"
# Explanation: Integer "51230100" has 2 trailing zeros, we remove them and return integer "512301".
#
# Constraints:
# 1 <= num.length <= 1000
# 	num consists of only digits.
# 	num doesn't have any leading zeros.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def removeTrailingZeros(self, num):
        """
        :type num: str
        :rtype: str
        """
        # 从字符串末尾开始检查，直到遇到非 '0' 的字符
        i = len(num) - 1
        while i >= 0 and num[i] == '0':
            i -= 1
        
        # 返回去掉末尾 '0' 的字符串
        return num[:i + 1]