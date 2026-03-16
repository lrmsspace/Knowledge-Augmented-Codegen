# Source: https://leetcode.com/problems/count-numbers-with-non-decreasing-digits/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integers, l and r, represented as strings, and an integer b. Return the count of integers in the inclusive range [l, r] whose digits are in non-decreasing order when represented in base b.
#
# An integer is considered to have non-decreasing digits if, when read from left to right (from the most significant digit to the least significant digit), each digit is greater than or equal to the previous one.
#
# Since the answer may be too large, return it modulo 109 + 7.
#
# Example:
# Input: l = "23", r = "28", b = 8
#
# Output: 3
#
# Explanation:
#
#
# 	The numbers from 23 to 28 in base 8 are: 27, 30, 31, 32, 33, and 34.
# 	Out of these, 27, 33, and 34 have non-decreasing digits. Hence, the output is 3.
#
# Constraints:
# 1 <= l.length <= r.length <= 100
# 	2 <= b <= 10
# 	l and r consist only of digits.
# 	The value represented by l is less than or equal to the value represented by r.
# 	l and r do not contain leading zeros.
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
    def countNumbers(self, l, r, b):
        """
        :type l: str
        :type r: str
        :type b: int
        :rtype: int
        """
        MOD = 10**9 + 7
        
        def count_non_decreasing(n):
            digits = []
            while n > 0:
                digits.append(n % b)
                n //= b
            digits.reverse()
            
            dp = [[0] * (b) for _ in range(len(digits) + 1)]
            dp[0][0] = 1
            
            for i in range(1, len(digits) + 1):
                for j in range(b):
                    dp[i][j] = dp[i-1][j]
                    if j > 0:
                        dp[i][j] += dp[i][j-1]
                    dp[i][j] %= MOD
            
            result = 0
            for j in range(digits[0], b):
                result += dp[len(digits)][j]
                result %= MOD
            
            return result
        
        l_num = int(l)
        r_num = int(r)
        
        return (count_non_decreasing(r_num) - count_non_decreasing(l_num - 1)) % MOD