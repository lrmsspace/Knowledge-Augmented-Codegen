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

class Solution(object):
    def countNumbers(self, l, r, b):
        """
        :type l: str
        :type r: str
        :type b: int
        :rtype: int
        """
        MOD = 10**9 + 7

        def to_base(n, base):
            digits = []
            while n:
                digits.append(n % base)
                n //= base
            return digits[::-1] if digits else [0]

        def count_up_to(n_digits):
            length = len(n_digits)
            dp = [[0] * (b + 1) for _ in range(length + 1)]
            for digit in range(1, b):
                dp[1][digit] = 1

            for i in range(2, length + 1):
                for digit in range(b):
                    dp[i][digit] = sum(dp[i - 1][d] for d in range(digit + 1)) % MOD

            total = sum(dp[length][digit] for digit in range(b)) % MOD

            for i in range(length):
                limit = n_digits[i]
                for digit in range(limit):
                    if i == 0 and digit == 0:
                        continue
                    total -= sum(dp[length - i - 1][d] for d in range(digit + 1)) % MOD
                    total %= MOD
                if i > 0 and limit < n_digits[i - 1]:
                    break
            return total % MOD

        l_num = int(l)
        r_num = int(r)

        l_digits = to_base(l_num - 1, b)
        r_digits = to_base(r_num, b)

        return (count_up_to(r_digits) - count_up_to(l_digits)) % MOD