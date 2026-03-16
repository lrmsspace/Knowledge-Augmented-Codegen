# Source: https://leetcode.com/problems/prime-palindrome/   |   Difficulty: Medium
#
# Problem Description:
# Given an integer n, return the smallest prime palindrome greater than or equal to n.
#
# An integer is prime if it has exactly two divisors: 1 and itself. Note that 1 is not a prime number.
#
#
# 	For example, 2, 3, 5, 7, 11, and 13 are all primes.
#
#
# An integer is a palindrome if it reads the same from left to right as it does from right to left.
#
#
# 	For example, 101 and 12321 are palindromes.
#
#
# The test cases are generated so that the answer always exists and is in the range [2, 2 * 108].
#
# Example:
# Input: n = 6
# Output: 7
#
# Constraints:
# 1 <= n <= 108
#
# Helpful references (internal KB):
# - Primality tests (number, enumeration, simulation)
#   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
#   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
#   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
#   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
#   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
#   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
#   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
#   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
#   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
#   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def primePalindrome(self, n):
        """
        :type n: int
        :rtype: int
        """
        def is_prime(x):
            if x < 2:
                return False
            for i in range(2, int(x**0.5) + 1):
                if x % i == 0:
                    return False
            return True

        def is_palindrome(x):
            s = str(x)
            return s == s[::-1]

        if 8 <= n <= 11:
            return 11

        for num in range(n, 2 * 10**8):
            if is_palindrome(num) and is_prime(num):
                return num