# Source: https://leetcode.com/problems/distinct-prime-factors-of-product-of-array/   |   Difficulty: Medium
#
# Problem Description:
# Given an array of positive integers nums, return the number of distinct prime factors in the product of the elements of nums.
#
# Note that:
#
#
# 	A number greater than 1 is called prime if it is divisible by only 1 and itself.
# 	An integer val1 is a factor of another integer val2 if val2 / val1 is an integer.
#
# Example:
# Input: nums = [2,4,3,7,10,6]
# Output: 4
# Explanation:
# The product of all the elements in nums is: 2 * 4 * 3 * 7 * 10 * 6 = 10080 = 25 * 32 * 5 * 7.
# There are 4 distinct prime factors so we return 4.
#
# Constraints:
# 1 <= nums.length <= 104
# 	2 <= nums[i] <= 1000
#

class Solution(object):
    def distinctPrimeFactors(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def sieve(n):
            is_prime = [True] * (n + 1)
            is_prime[0] = is_prime[1] = False
            for i in range(2, int(n**0.5) + 1):
                if is_prime[i]:
                    for j in range(i * i, n + 1, i):
                        is_prime[j] = False
            return [i for i in range(n + 1) if is_prime[i]]

        primes = sieve(1000)
        prime_factors = set()

        for num in nums:
            temp = num
            for prime in primes:
                if prime * prime > temp:
                    break
                while temp % prime == 0:
                    prime_factors.add(prime)
                    temp //= prime
            if temp > 1:
                prime_factors.add(temp)

        return len(prime_factors)