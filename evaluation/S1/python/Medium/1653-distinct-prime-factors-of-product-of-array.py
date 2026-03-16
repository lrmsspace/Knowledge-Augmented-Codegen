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
# Helpful references (internal KB):
# - Integer factorization (number, array, enumeration, sieve, counting)
#   • When to use: Use when needing to find the prime factors of a composite number, especially for relatively small numbers or as a base case for more advanced algorithms.
#   • Idea: This algorithm finds the prime factorization of an integer by iteratively dividing it by its smallest prime factors. It typically checks divisors up to the square root of the number, achieving an O(sqrt(N)) time complexity.
#   • Invariants: The product of all found prime factors multiplied by the current remaining number equals the original input number.; All prime factors found so far are less than or equal to the current divisor being tested.
#   • Tips: Perform a primality test first to avoid unnecessary factorization attempts.; Only check divisors up to the square root of the number.
#   • Pitfalls: Trial division is pseudo-polynomial time, making it inefficient for very large numbers.; Forgetting to handle the case where the remaining number after division is itself a prime greater than its original square root.
# - Sieve of Eratosthenes (array, bitset, sieve)
#   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
#   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
#   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
#   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
# - The Inclusion-Exclusion Principle (matrix, array, dp-2d, counting)
#   • When to use: Use when needing to count elements satisfying "at least one" of several properties, especially when direct counting is complicated by overlapping sets. It's also applicable for counting elements satisfying "none" of the properties by subtracting from the total.
#   • Idea: The Inclusion-Exclusion Principle is a combinatorial method to determine the size of the union of multiple finite sets. It works by summing the sizes of individual sets, subtracting the sizes of all pairwise intersections, adding back the sizes of all three-way intersections, and so on, with alternating signs.
#   • Invariants: The count for any element satisfying `k` properties is adjusted to be exactly 1 in the final sum.; Each term in the sum corresponds to the size of an intersection of a distinct subset of properties.
#   • Tips: Clearly define the universe and the properties (sets) you are interested in.; Systematically list all combinations of properties for intersection terms.
#   • Pitfalls: Incorrectly identifying or defining the properties or sets.; Missing certain intersection terms or double-counting them.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def distinctPrimeFactors(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        def sieve_of_eratosthenes(n):
            is_prime = [True] * (n + 1)
            is_prime[0] = is_prime[1] = False
            for i in range(2, int(n**0.5) + 1):
                if is_prime[i]:
                    for j in range(i * i, n + 1, i):
                        is_prime[j] = False
            primes = [i for i in range(n + 1) if is_prime[i]]
            return primes

        def prime_factors(num, primes):
            factors = set()
            for prime in primes:
                if prime * prime > num:
                    break
                while num % prime == 0:
                    factors.add(prime)
                    num //= prime
            if num > 1:
                factors.add(num)
            return factors

        max_num = max(nums)
        primes = sieve_of_eratosthenes(max_num)
        distinct_factors = set()

        for num in nums:
            factors = prime_factors(num, primes)
            distinct_factors.update(factors)

        return len(distinct_factors)