# Source: https://leetcode.com/problems/prime-pairs-with-target-sum/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n. We say that two integers x and y form a prime number pair if:
#
#
# 	1 <= x <= y <= n
# 	x + y == n
# 	x and y are prime numbers
#
#
# Return the 2D sorted list of prime number pairs [xi, yi]. The list should be sorted in increasing order of xi. If there are no prime number pairs at all, return an empty array.
#
# Note: A prime number is a natural number greater than 1 with only two factors, itself and 1.
#
# Example:
# Input: n = 10
# Output: [[3,7],[5,5]]
# Explanation: In this example, there are two prime pairs that satisfy the criteria. 
# These pairs are [3,7] and [5,5], and we return them in the sorted order as described in the problem statement.
#
# Constraints:
# 1 <= n <= 106
#

class Solution(object):
    def findPrimePairs(self, n):
        """
        :type n: int
        :rtype: List[List[int]]
        """
        def is_prime(num):
            if num < 2:
                return False
            for i in range(2, int(num**0.5) + 1):
                if num % i == 0:
                    return False
            return True

        primes = [i for i in range(2, n) if is_prime(i)]
        prime_set = set(primes)
        result = []

        for prime in primes:
            complement = n - prime
            if complement >= prime and complement in prime_set:
                result.append([prime, complement])

        return result