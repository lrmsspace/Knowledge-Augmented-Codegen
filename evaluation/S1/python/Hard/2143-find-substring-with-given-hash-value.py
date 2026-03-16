# Source: https://leetcode.com/problems/find-substring-with-given-hash-value/   |   Difficulty: Hard
#
# Problem Description:
# The hash of a 0-indexed string s of length k, given integers p and m, is computed using the following function:
#
#
# 	hash(s, p, m) = (val(s[0]) * p0 + val(s[1]) * p1 + ... + val(s[k-1]) * pk-1) mod m.
#
#
# Where val(s[i]) represents the index of s[i] in the alphabet from val('a') = 1 to val('z') = 26.
#
# You are given a string s and the integers power, modulo, k, and hashValue. Return sub, the first substring of s of length k such that hash(sub, power, modulo) == hashValue.
#
# The test cases will be generated such that an answer always exists.
#
# A substring is a contiguous non-empty sequence of characters within a string.
#
# Example:
# Input: s = "leetcode", power = 7, modulo = 20, k = 2, hashValue = 0
# Output: "ee"
# Explanation: The hash of "ee" can be computed to be hash("ee", 7, 20) = (5 * 1 + 5 * 7) mod 20 = 40 mod 20 = 0. 
# "ee" is the first substring of length 2 with hashValue 0. Hence, we return "ee".
#
# Constraints:
# 1 <= k <= s.length <= 2 * 104
# 	1 <= power, modulo <= 109
# 	0 <= hashValue < modulo
# 	s consists of lowercase English letters only.
# 	The test cases are generated such that an answer always exists.
#
# Helpful references (internal KB):
# - Substring Search (string, number, hashing, randomized, rolling-hash)
#   • When to use: Use when efficiently finding occurrences of a pattern string within a larger text string, especially for average-case fast string matching. It is suitable for scenarios involving large texts or multiple patterns.
#   • Idea: The Rabin-Karp algorithm finds pattern occurrences in a text by comparing hash values of the pattern and text substrings. It uses a rolling hash function for O(1) substring hash updates, achieving O(N+M) average time complexity and O(NM) worst-case.
#   • Invariants: The pattern's hash value patHash remains constant throughout the search.; At each step i, txtHash accurately represents the hash of txt[i...i+m-1].
#   • Tips: Choose a large prime modulus to minimize hash collisions.; Use a random base for polynomial hashing to enhance collision resistance.
#   • Pitfalls: Hash collisions can lead to false positives, increasing worst-case time.; Improper choice of prime modulus or base can degrade performance.
# - Binary Exponentiation by Factoring (number, mod-exp)
#   • When to use: When computing a number raised to a very large power modulo another number efficiently. It is also applicable when specific properties of the base or modulus allow for specialized bitwise optimizations.
#   • Idea: Binary exponentiation (also known as exponentiation by squaring) computes a^b mod m by leveraging the binary representation of the exponent b. This method significantly reduces the number of multiplications from O(b) to O(log b), achieving O(log b) time complexity.
#   • Invariants: (original_base^original_exponent) % m == (current_base^current_exponent * accumulated_result) % m; current_exponent is always non-negative and strictly decreases towards zero.
#   • Tips: Use long long for intermediate products to prevent overflow before taking modulo.; Apply the modulo operation after each multiplication to keep numbers small.
#   • Pitfalls: Integer overflow if intermediate products are not reduced modulo m frequently enough.; Incorrectly handling the exponent 0 or negative exponents (if applicable).
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def subStrHash(self, s, power, modulo, k, hashValue):
        """
        :type s: str
        :type power: int
        :type modulo: int
        :type k: int
        :type hashValue: int
        :rtype: str
        """
        n = len(s)
        p_pow = 1
        for i in range(k):
            p_pow = (p_pow * power) % modulo

        current_hash = 0
        for i in range(n - 1, n - k - 1, -1):
            current_hash = (current_hash * power + (ord(s[i]) - ord('a') + 1)) % modulo

        if current_hash == hashValue:
            result_index = n - k

        for i in range(n - k - 1, -1, -1):
            current_hash = (current_hash * power - (ord(s[i + k]) - ord('a') + 1) * p_pow + (ord(s[i]) - ord('a') + 1)) % modulo
            if current_hash == hashValue:
                result_index = i

        return s[result_index:result_index + k]