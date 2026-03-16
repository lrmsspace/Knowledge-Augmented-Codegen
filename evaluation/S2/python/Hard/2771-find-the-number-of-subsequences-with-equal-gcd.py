# Source: https://leetcode.com/problems/find-the-number-of-subsequences-with-equal-gcd/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer array nums.
#
# Your task is to find the number of pairs of non-empty subsequences (seq1, seq2) of nums that satisfy the following conditions:
#
#
# 	The subsequences seq1 and seq2 are disjoint, meaning no index of nums is common between them.
# 	The GCD of the elements of seq1 is equal to the GCD of the elements of seq2.
#
#
# Return the total number of such pairs.
#
# Since the answer may be very large, return it modulo 109 + 7.
#
# Example:
# Input: nums = [1,2,3,4]
#
# Output: 10
#
# Explanation:
#
# The subsequence pairs which have the GCD of their elements equal to 1 are:
#
#
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
# 	([1, 2, 3, 4], [1, 2, 3, 4])
#
# Constraints:
# 1 <= nums.length <= 200
# 	1 <= nums[i] <= 200
#
# Helpful references (internal KB):
# - Binomial Coefficients (array, number, dp-1d, mod-exp)
#   • When to use: Use when calculating binomial coefficients C(n, k) modulo a composite number M, especially when M is not prime and direct modular inverse computation for factorials is not possible.
#   • Idea: This technique computes binomial coefficients modulo an arbitrary composite number M by factoring M into prime powers. For each prime power, it calculates prime exponents in factorials and combines coprime parts, then uses Chinese Remainder Theorem.
#   • Invariants: For any `i <= N`, `c[i]` correctly stores the exponent of prime `p` in `i!`.; For any `i <= N`, `g[i]` correctly stores `(i! / p^c[i]) % (p^b)`.
#   • Tips: Precompute factorials and their prime exponents up to N using dynamic programming.; Apply Legendre's formula to efficiently find the exponent of a prime 'p' in 'x!'.
#   • Pitfalls: Failing to correctly factorize the modulus 'M' into its prime power components.; Incorrectly computing modular inverses when a number is not coprime to the modulus.
# - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
#   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
#   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
#   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
#   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
#   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
# - Euler's totient function
#  (array, number, enumeration)
#   • When to use: Use when needing to count positive integers up to n that are relatively prime to n. It is also efficient for computing totient values for all numbers in a given range.
#   • Idea: Euler's totient function, φ(n), counts positive integers less than or equal to n that are relatively prime to n. It can be computed for a single n in O(sqrt(n)) using prime factorization, or for all numbers up to N in O(N log log N) using a sieve-like algorithm.
#   • Invariants: phi[i] stores the current totient value for i, which is i initially, then updated by (1 - 1/p) for each prime p dividing i.; After iterating through all primes p up to sqrt(N), phi[i] holds the correct totient value for all i <= N.
#   • Tips: For a single n, compute φ(n) using its prime factorization.; For all φ(i) up to N, use a sieve approach similar to Sieve of Eratosthenes.
#   • Pitfalls: Confusing 'relatively prime' with 'prime number'.; Applying the multiplicative property incorrectly when numbers share common factors.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def subsequencePairCount(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        from math import gcd
        from collections import defaultdict

        MOD = 10**9 + 7
        max_num = max(nums)
        
        # Count frequency of each number in nums
        freq = [0] * (max_num + 1)
        for num in nums:
            freq[num] += 1
        
        # Count subsequences with GCD equal to i
        count_gcd = [0] * (max_num + 1)
        
        for i in range(1, max_num + 1):
            count = 0
            for j in range(i, max_num + 1, i):
                count += freq[j]
            if count > 0:
                count_gcd[i] = pow(2, count, MOD) - 1
        
        # Count pairs of subsequences with equal GCD
        result = 0
        for i in range(1, max_num + 1):
            if count_gcd[i] > 0:
                result += (count_gcd[i] * count_gcd[i]) % MOD
                result %= MOD
        
        return result