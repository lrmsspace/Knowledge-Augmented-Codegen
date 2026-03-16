# Source: https://leetcode.com/problems/count-primes/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the number of prime numbers that are strictly less than n.
#
# Example:
# Input: n = 10
# Output: 4
# Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.
#
# Constraints:
# 0 <= n <= 5 * 106
#

class Solution(object):
    def countPrimes(self, n):
        """
        :type n: int
        :rtype: int
        """
        if n < 2:
            return 0

        is_prime = [True] * n
        is_prime[0] = is_prime[1] = False

        for i in range(2, int(n**0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, n, i):
                    is_prime[j] = False

        return sum(is_prime)