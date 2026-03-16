# Source: https://leetcode.com/problems/find-the-count-of-good-integers/   |   Difficulty: Hard
#
# Problem Description:
# You are given two positive integers n and k.
#
# An integer x is called k-palindromic if:
#
#
# 	x is a palindrome.
# 	x is divisible by k.
#
#
# An integer is called good if its digits can be rearranged to form a k-palindromic integer. For example, for k = 2, 2020 can be rearranged to form the k-palindromic integer 2002, whereas 1010 cannot be rearranged to form a k-palindromic integer.
#
# Return the count of good integers containing n digits.
#
# Note that any integer must not have leading zeros, neither before nor after rearrangement. For example, 1010 cannot be rearranged to form 101.
#
# Example:
# Input: n = 3, k = 5
#
# Output: 27
#
# Explanation:
#
# Some of the good integers are:
#
#
# 	551 because it can be rearranged to form 515.
# 	525 because it is already k-palindromic.
#
# Constraints:
# 1 <= n <= 10
# 	1 <= k <= 9
#

class Solution(object):
    def countGoodIntegers(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7

        if n % 2 == 0:
            half_len = n // 2
            count = pow(10, half_len - 1, MOD) * 9 % MOD
        else:
            half_len = n // 2
            count = pow(10, half_len, MOD) * 9 % MOD

        # Check divisibility by k
        valid_count = 0
        for first_half in range(10**(half_len - 1), 10**half_len):
            if n % 2 == 0:
                palin_num = int(str(first_half) + str(first_half)[::-1])
            else:
                for mid_digit in range(10):
                    palin_num = int(str(first_half) + str(mid_digit) + str(first_half)[::-1])
                    if palin_num % k == 0:
                        valid_count += 1
                continue

            if palin_num % k == 0:
                valid_count += 1

        return valid_count % MOD