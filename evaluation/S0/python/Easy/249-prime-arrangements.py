# Source: https://leetcode.com/problems/prime-arrangements/   |   Difficulty: Easy
#
# Problem Description:
# Return the number of permutations of 1 to n so that prime numbers are at prime indices (1-indexed.)
#
# (Recall that an integer is prime if and only if it is greater than 1, and cannot be written as a product of two positive integers both smaller than it.)
#
# Since the answer may be large, return the answer modulo 10^9 + 7.
#
# Example:
# Input: n = 5
# Output: 12
# Explanation: For example [1,2,5,4,3] is a valid permutation, but [5,2,3,4,1] is not because the prime number 5 is at index 1.
#
# Constraints:
# 1 <= n <= 100
#

class Solution(object):
    def numPrimeArrangements(self, n):
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

        prime_count = sum(1 for i in range(1, n + 1) if is_prime(i))
        non_prime_count = n - prime_count

        MOD = 10**9 + 7

        def factorial_mod(x):
            result = 1
            for i in range(2, x + 1):
                result = (result * i) % MOD
            return result

        prime_permutations = factorial_mod(prime_count)
        non_prime_permutations = factorial_mod(non_prime_count)

        return (prime_permutations * non_prime_permutations) % MOD