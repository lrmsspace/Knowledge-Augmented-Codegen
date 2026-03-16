# Source: https://leetcode.com/problems/prime-palindrome/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the smallest prime palindrome greater than or equal to n.
#
# An integer is prime if it has exactly two divisors: 1 and itself. Note that 1 is not a prime number.
#
#
# 	For example, 2, 3, 5, 7, 11, and 13 are all primes.
#
#
# An integer is a palindrome if it reads the same from left to right as it does from right to left.
#
#
# 	For example, 101 and 12321 are palindromes.
#
#
# The test cases are generated so that the answer always exists and is in the range [2, 2 * 108].
#
# Example:
# Input: n = 6
# Output: 7
#
# Constraints:
# 1 <= n <= 108
#

class Solution(object):
    def primePalindrome(self, n):
        """
        :type n: int
        :rtype: int
        """
        def is_prime(num):
            if num < 2:
                return False
            for i in range(2, int(num**0.5) + 1):
                if num % i == 0:
                    return False
            return True

        def is_palindrome(num):
            s = str(num)
            return s == s[::-1]

        candidate = n
        while True:
            if is_palindrome(candidate) and is_prime(candidate):
                return candidate
            candidate += 1