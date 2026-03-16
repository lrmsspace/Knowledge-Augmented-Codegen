# Source: https://leetcode.com/problems/count-ways-to-make-array-with-product/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 2D integer array, queries. For each queries[i], where queries[i] = [ni, ki], find the number of different ways you can place positive integers into an array of size ni such that the product of the integers is ki. As the number of ways may be too large, the answer to the ith query is the number of ways modulo 109 + 7.
#
# Return an integer array answer where answer.length == queries.length, and answer[i] is the answer to the ith query.
#
# Example:
# Input: queries = [[2,6],[5,1],[73,660]]
# Output: [4,1,50734910]
# Explanation: Each query is independent.
# [2,6]: There are 4 ways to fill an array of size 2 that multiply to 6: [1,6], [2,3], [3,2], [6,1].
# [5,1]: There is 1 way to fill an array of size 5 that multiply to 1: [1,1,1,1,1].
# [73,660]: There are 1050734917 ways to fill an array of size 73 that multiply to 660. 1050734917 modulo 109 + 7 = 50734910.
#
# Constraints:
# 1 <= queries.length <= 104 
# 	1 <= ni, ki <= 104
#
# Helpful references (internal KB):
# - Sieve of Eratosthenes (array, sieve, enumeration)
#   • When to use: Use when you need to find all prime numbers up to a certain limit or precompute primality for a range. It is efficient for generating primes within a reasonable upper bound.
#   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer by iteratively marking multiples of primes as composite. It achieves a time complexity of O(N log log N).
#   • Invariants: All numbers less than the current prime 'p' have already been processed.; If 'i' is marked as prime, then all its multiples less than 'i*i' have been marked composite by smaller primes.
#   • Tips: Optimize by starting inner loop from p*p, as smaller multiples would have been marked.; Use a boolean array for primality, or an integer array to store smallest prime factor (SPF).
#   • Pitfalls: Incorrectly handling 0 and 1, which are neither prime nor composite.; Off-by-one errors when setting array bounds or loop conditions.
# - Number of divisors / sum of divisors (number, counting, enumeration)
#   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
#   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
#   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
#   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
#   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
# - Binomial Coefficients (array, number, mod-exp, enumeration)
#   • When to use: Use when calculating combinations (n choose k) efficiently, especially for large n, and when results are required modulo a prime or prime power.
#   • Idea: This algorithm computes binomial coefficients C(n, k) modulo a given prime m or prime power p^b. It leverages precomputed factorials and their modular inverses to achieve O(1) query time after O(MAXN) or O(MAXN log m) precomputation.
#   • Invariants: Factorials `fact[i]` are correctly computed as `i! % m`.; Modular inverse factorials `invFact[i]` satisfy `(fact[i] * invFact[i]) % m == 1`.
#   • Tips: Precompute factorials modulo m up to MAXN.; Precompute modular inverses of factorials for O(1) query time.
#   • Pitfalls: Forgetting to take modulo at each multiplication step during factorial precomputation.; Using Fermat's Little Theorem for modular inverse when the modulus is not prime.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def waysToFillArray(self, queries):
        """
        :type queries: List[List[int]]
        :rtype: List[int]
        """
        MOD = 10**9 + 7
        MAX_K = max(k for _, k in queries)

        # Step 1: Sieve of Eratosthenes to find all primes up to MAX_K
        is_prime = [True] * (MAX_K + 1)
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(MAX_K**0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, MAX_K + 1, i):
                    is_prime[j] = False
        primes = [i for i in range(2, MAX_K + 1) if is_prime[i]]

        # Step 2: Precompute the number of divisors for each k
        divisor_count = [1] * (MAX_K + 1)
        for p in primes:
            for multiple in range(p, MAX_K + 1, p):
                count = 0
                temp = multiple
                while temp % p == 0:
                    temp //= p
                    count += 1
                divisor_count[multiple] *= (count + 1)

        # Step 3: Compute the answer for each query using the divisor counts
        results = []
        for n, k in queries:
            if k == 1:
                results.append(1)  # Only one way to fill an array with product 1: all elements are 1
            else:
                total_divisors = divisor_count[k]
                # The number of ways to fill an array of size n with a product of k is the number of ways to distribute total_divisors into n parts
                # This can be computed using the formula C(total_divisors + n - 1, n - 1)
                ways = self.binomial(total_divisors + n - 1, n - 1, MOD)
                results.append(ways)

        return results  