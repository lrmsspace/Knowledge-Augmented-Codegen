# Source: https://leetcode.com/problems/count-k-subsequences-of-a-string-with-maximum-beauty/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and an integer k.
#
# A k-subsequence is a subsequence of s, having length k, and all its characters are unique, i.e., every character occurs once.
#
# Let f(c) denote the number of times the character c occurs in s.
#
# The beauty of a k-subsequence is the sum of f(c) for every character c in the k-subsequence.
#
# For example, consider s = "abbbdd" and k = 2:
#
#
# 	f('a') = 1, f('b') = 3, f('d') = 2
# 	Some k-subsequences of s are:
# 	
# 		"abbbdd" -> "ab" having a beauty of f('a') + f('b') = 4
# 		"abbbdd" -> "ad" having a beauty of f('a') + f('d') = 3
# 		"abbbdd" -> "bd" having a beauty of f('b') + f('d') = 5
# 	
# 	
#
#
# Return an integer denoting the number of k-subsequences whose beauty is the maximum among all k-subsequences. Since the answer may be too large, return it modulo 109 + 7.
#
# A subsequence of a string is a new string formed from the original string by deleting some (possibly none) of the characters without disturbing the relative positions of the remaining characters.
#
# Notes
#
#
# 	f(c) is the number of times a character c occurs in s, not a k-subsequence.
# 	Two k-subsequences are considered different if one is formed by an index that is not present in the other. So, two k-subsequences may form the same string.
#
# Example:
# Input: s = "bcca", k = 2
# Output: 4
# Explanation: From s we have f('a') = 1, f('b') = 1, and f('c') = 2.
# The k-subsequences of s are: 
# bcca having a beauty of f('b') + f('c') = 3 
# bcca having a beauty of f('b') + f('c') = 3 
# bcca having a beauty of f('b') + f('a') = 2 
# bcca having a beauty of f('c') + f('a') = 3
# bcca having a beauty of f('c') + f('a') = 3 
# There are 4 k-subsequences that have the maximum beauty, 3. 
# Hence, the answer is 4.
#
# Constraints:
# 1 <= s.length <= 2 * 105
# 	1 <= k <= s.length
# 	s consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Number of divisors / sum of divisors (number, counting, enumeration)
#   • When to use: Use this approach when you need to calculate the total count or sum of all positive divisors for a given integer, typically by leveraging its prime factorization.
#   • Idea: The number of divisors d(n) and sum of divisors sigma(n) are arithmetic functions derived from the prime factorization of an integer n. Both can be computed efficiently by first finding prime factors and their exponents, resulting in an O(sqrt(N)) or O(log N) complexity with precomputed primes.
#   • Invariants: The current count of divisors is the product of (exponent + 1) for all prime factors found so far.; The current sum of divisors is the product of (1 + p + ... + p^e) for all prime factors found so far.
#   • Tips: Precompute primes using a sieve for efficiency when dealing with multiple queries or large numbers.; For sum of divisors, the formula is sigma(n) = product((1 + p_i + ... + p_i^e_i)) for each prime factor p_i^e_i.
#   • Pitfalls: Forgetting to handle n=1 correctly, which has one divisor.; Integer overflow when calculating sums or products of large powers, especially for sum of divisors.
# - Chinese Remainder Theorem (number, mod-exp)
#   • When to use: Used to find an integer that satisfies a system of multiple congruence relations, particularly when the moduli are pairwise coprime. It's essential for reconstructing numbers from their remainders.
#   • Idea: The Chinese Remainder Theorem finds a unique integer solution to a system of linear congruences, modulo the product of their pairwise coprime moduli. It iteratively combines congruences, often using the Extended Euclidean Algorithm for modular inverses, with a complexity polynomial in the number of congruences.
#   • Invariants: The current combined solution satisfies all previously processed congruences.; The current combined modulus is the product of all previously processed pairwise coprime moduli.
#   • Tips: Ensure all moduli are pairwise coprime for a unique solution.; Use the Extended Euclidean Algorithm to find modular inverses.
#   • Pitfalls: Forgetting to check if moduli are pairwise coprime, leading to no unique solution or no solution.; Incorrectly calculating modular inverses, which is crucial for the algorithm.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countKSubsequencesWithMaxBeauty(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        from collections import Counter
        from math import comb

        MOD = 10**9 + 7
        freq = Counter(s)
        counts = sorted(freq.values(), reverse=True)

        if k > len(counts):
            return 0

        max_beauty = sum(counts[:k])
        count_max_beauty = 1
        for i in range(k):
            count_max_beauty *= counts[i]
            count_max_beauty %= MOD

        # Handle duplicates in counts for the k-th element
        kth_count = counts[k-1]
        same_count = counts.count(kth_count)

        if same_count > 1:
            # We need to choose how many of the same_count elements to include in our k-subsequence
            # We have already included one of them (the k-th element), so we need to choose (same_count - 1) from the remaining (same_count - 1)
            count_max_beauty *= comb(same_count, same_count - 1)
            count_max_beauty %= MOD

        return count_max_beauty