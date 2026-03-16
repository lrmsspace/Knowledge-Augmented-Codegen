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
# Helpful references (internal KB):
# - Factorial modulo 
# p (number, counting, recursion)
#   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
#   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
#   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
#   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
#   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
# - Linear Sieve (array, sieve)
#   • When to use: Use when you need to find all prime numbers up to a given limit N, or compute the least prime factor for all numbers in that range, efficiently in linear time.
#   • Idea: The Linear Sieve finds all prime numbers up to N in O(N) time by ensuring each composite number is marked exactly once by its least prime factor. It also computes the least prime factor for every number up to N.
#   • Invariants: The 'primes' list always contains all prime numbers found so far in increasing order.; lpf[i] stores the least prime factor of 'i' if 'i' is composite, or 'i' itself if 'i' is prime.
#   • Tips: Store the least prime factor (LPF) for each number in an array.; Maintain a dynamically growing list of primes found so far.
#   • Pitfalls: Incorrectly marking multiples can lead to O(N log log N) or worse complexity.; Forgetting to store the least prime factor can break the linear time guarantee.
# - Primitive Root (number, mod-exp, sieve, enumeration)
#   • When to use: Use when needing to find a generator for the multiplicative group of integers modulo n, or to check if a number is a primitive root. This is often required in number theory problems involving modular arithmetic and cyclic groups.
#   • Idea: This algorithm finds a primitive root modulo n by checking candidate numbers and verifying their order using Euler's totient function and its prime factors. The optimized approach significantly reduces checks from O(phi(n)) to O(k * log(n)) for each candidate, where k is the number of distinct prime factors of phi(n).
#   • Invariants: The current candidate g is coprime to n.; The order of g modulo n is being checked against divisors of phi(n).
#   • Tips: First, determine if a primitive root exists for the given n.; Calculate Euler's totient function phi(n) for the modulus n.
#   • Pitfalls: Forgetting to check the existence condition for primitive roots.; Incorrectly calculating Euler's totient function phi(n).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numPrimeArrangements(self, n):
        """
        :type n: int
        :rtype: int
        """
        MOD = 10**9 + 7
        # Step 1: Count the number of primes up to n using the Sieve of Eratosthenes
        is_prime = [True] * (n + 1)
        is_prime[0] = is_prime[1] = False
        for i in range(2, int(n**0.5) + 1):
            if is_prime[i]:
                for j in range(i * i, n + 1, i):
                    is_prime[j] = False
        prime_count = sum(is_prime)
        non_prime_count = n - prime_count
        # Step 2: Calculate the number of arrangements
        def factorial_mod(x):
            result = 1
            for i in range(2, x + 1):
                result = (result * i) % MOD
            return result
        return (factorial_mod(prime_count) * factorial_mod(non_prime_count)) % MOD