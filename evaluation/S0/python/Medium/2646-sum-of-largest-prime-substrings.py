# Source: https://leetcode.com/problems/sum-of-largest-prime-substrings/   |   Difficulty: Medium
#
# Problem Description:
# Given a string s, find the sum of the 3 largest unique prime numbers that can be formed using any of its substrings.
#
# Return the sum of the three largest unique prime numbers that can be formed. If fewer than three exist, return the sum of all available primes. If no prime numbers can be formed, return 0.
#
# Note: Each prime number should be counted only once, even if it appears in multiple substrings. Additionally, when converting a substring to an integer, any leading zeros are ignored.
#
# Example:
# Input: s = "12234"
#
# Output: 1469
#
# Explanation:
#
#
# 	The unique prime numbers formed from the substrings of "12234" are 2, 3, 23, 223, and 1223.
# 	The 3 largest primes are 1223, 223, and 23. Their sum is 1469.
#
# Constraints:
# 1 <= s.length <= 10
# 	s consists of only digits.
#

class Solution(object):
    def sumOfLargestPrimes(self, s):
        """
        :type s: str
        :rtype: int
        """
        def is_prime(num):
            if num < 2:
                return False
            for i in range(2, int(num**0.5) + 1):
                if num % i == 0:
                    return False
            return True

        unique_primes = set()
        n = len(s)

        for i in range(n):
            for j in range(i + 1, n + 1):
                substring = s[i:j]
                num = int(substring.lstrip('0') or '0')
                if is_prime(num):
                    unique_primes.add(num)

        largest_primes = sorted(unique_primes, reverse=True)[:3]
        return sum(largest_primes)