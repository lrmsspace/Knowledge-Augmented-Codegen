# Source: https://leetcode.com/problems/greatest-common-divisor-of-strings/   |   Difficulty: Easy
#
# Problem Description:
# For two strings s and t, we say "t divides s" if and only if s = t + t + t + ... + t + t (i.e., t is concatenated with itself one or more times).
#
# Given two strings str1 and str2, return the largest string x such that x divides both str1 and str2.
#
# Example:
# Input: str1 = "ABCABC", str2 = "ABC"
# Output: "ABC"
#
# Constraints:
# 1 <= str1.length, str2.length <= 1000
# 	str1 and str2 consist of English uppercase letters.
#
# Helpful references (internal KB):
# - Substring Search (string, array, kmp, simulation)
#   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
#   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
#   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
#   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
# - Suffix Array (array, string, simulation, two-pointers)
#   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
#   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
#   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
#   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
#   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
# - String Hashing (string, number, hashing, prefix-sum)
#   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
#   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
#   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
#   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
#   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def gcdOfStrings(self, str1, str2):
        """
        :type str1: str
        :type str2: str
        :rtype: str
        """
        # Check if str1 + str2 is equal to str2 + str1
        if str1 + str2 != str2 + str1:
            return ""

        # Find the greatest common divisor of the lengths of str1 and str2
        def gcd(a, b):
            while b:
                a, b = b, a % b
            return a

        gcd_length = gcd(len(str1), len(str2))
        return str1[:gcd_length]