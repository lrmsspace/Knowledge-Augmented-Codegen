# Source: https://leetcode.com/problems/split-the-array-to-make-coprime-products/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array nums of length n.
#
# A split at an index i where 0 <= i <= n - 2 is called valid if the product of the first i + 1 elements and the product of the remaining elements are coprime.
#
#
# 	For example, if nums = [2, 3, 3], then a split at the index i = 0 is valid because 2 and 9 are coprime, while a split at the index i = 1 is not valid because 6 and 3 are not coprime. A split at the index i = 2 is not valid because i == n - 1.
#
#
# Return the smallest index i at which the array can be split validly or -1 if there is no such split.
#
# Two values val1 and val2 are coprime if gcd(val1, val2) == 1 where gcd(val1, val2) is the greatest common divisor of val1 and val2.
#
# Example:
# Input: nums = [4,7,8,15,3,5]
# Output: 2
# Explanation: The table above shows the values of the product of the first i + 1 elements, the remaining elements, and their gcd at each index i.
# The only valid split is at index 2.
#
# Constraints:
# n == nums.length
# 	1 <= n <= 104
# 	1 <= nums[i] <= 106
#
# Helpful references (internal KB):
# - Linear Sieve (array, sieve)
#   • When to use: Use when you need to find the smallest prime factor or full prime factorization for all numbers up to a given limit N in linear time. It's particularly useful for tasks requiring precomputed factorizations.
#   • Idea: The Linear Sieve computes the smallest prime factor for every number up to N, ensuring each composite number is marked exactly once by its smallest prime factor. It achieves this in O(N) time complexity.
#   • Invariants: Every number `i` from 2 to N has its `lp[i]` correctly set to its smallest prime factor.; The `primes` array contains all prime numbers less than or equal to the current iteration `i`.
#   • Tips: Stores the smallest prime factor (lp) for each number.; Efficiently generates all prime numbers up to N.
#   • Pitfalls: Higher memory usage compared to the classic Sieve of Eratosthenes due to storing lp array.; Can be slower in practice than optimized Sieve of Eratosthenes for merely generating primes.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Garner's algorithm
#  (number, array, enumeration)
#   • When to use: Use when reconstructing a large integer from a system of congruences with pairwise coprime moduli, offering an alternative to the direct Chinese Remainder Theorem approach.
#   • Idea: Garner's algorithm efficiently reconstructs an integer from its remainders modulo a set of pairwise coprime numbers, by computing its mixed radix representation coefficients. It typically runs in O(k^2 log M) time, where k is the number of moduli and M is the maximum modulus, assuming modular inverse takes log M time.
#   • Invariants: At the start of iteration j, the partial sum $V_{j-1}$ satisfies $V_{j-1} \equiv a_i \pmod{p_i}$ for all $i < j$.; For each iteration j, the coefficient $x_j$ is uniquely determined in the range $[0, p_j - 1]$.
#   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Precompute modular inverses for efficiency, especially if many are needed.
#   • Pitfalls: Incorrectly calculating modular inverses, leading to wrong coefficients.; Not handling large intermediate products, which can cause integer overflow.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findValidSplit(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from math import gcd
        from collections import defaultdict

        n = len(nums)
        if n == 1:
            return -1

        # Step 1: Count the frequency of each prime factor across all numbers
        prime_count = defaultdict(int)

        def prime_factors(num):
            factors = set()
            d = 2
            while d * d <= num:
                while num % d == 0:
                    factors.add(d)
                    num //= d
                d += 1
            if num > 1:
                factors.add(num)
            return factors

        for num in nums:
            for p in prime_factors(num):
                prime_count[p] += 1

        # Step 2: Iterate through the array and keep track of the count of prime factors in the left and right parts
        left_prime_count = defaultdict(int)

        for i in range(n - 1):
            for p in prime_factors(nums[i]):
                left_prime_count[p] += 1
                prime_count[p] -= 1

            # Check if all prime factors in the left part are coprime with those in the right part
            if all(left_prime_count[p] == 0 or prime_count[p] == 0 for p in left_prime_count):
                return i

        return -1