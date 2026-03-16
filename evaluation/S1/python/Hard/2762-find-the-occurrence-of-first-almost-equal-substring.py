# Source: https://leetcode.com/problems/find-the-occurrence-of-first-almost-equal-substring/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings s and pattern.
#
# A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
#
# Return the smallest starting index of a substring in s that is almost equal to pattern. If no such index exists, return -1.
# A substring is a contiguous non-empty sequence of characters within a string.
#
# Example:
# Input: s = "abcdefg", pattern = "bcdffg"
#
# Output: 1
#
# Explanation:
#
# The substring s[1..6] == "bcdefg" can be converted to "bcdffg" by changing s[4] to "f".
#
# Constraints:
# 1 <= pattern.length < s.length <= 105
# 	s and pattern consist only of lowercase English letters.
#
#
#  
# Follow-up: Could you solve the problem if at most k consecutive characters can be changed?
#
# Helpful references (internal KB):
# - String Hashing (string, number, hashing, prefix-sum)
#   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
#   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
#   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
#   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
#   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
# - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
#   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
#   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
#   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
#   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
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
    def minStartingIndex(self, s, pattern):
        """
        :type s: str
        :type pattern: str
        :rtype: int
        """
        # Step 1: Precompute prefix hashes for string s and pattern
        def compute_prefix_hashes(string, p, m):
            prefix_hash = [0] * (len(string) + 1)
            for i in range(len(string)):
                prefix_hash[i + 1] = (prefix_hash[i] * p + ord(string[i]) - ord('a') + 1) % m
            return prefix_hash

        p = 31
        m = 10**9 + 7
        prefix_hash_s = compute_prefix_hashes(s, p, m)
        prefix_hash_pattern = compute_prefix_hashes(pattern, p, m)

        # Step 2: Compute the hash of the pattern
        pattern_hash = prefix_hash_pattern[len(pattern)]

        # Step 3: Check each substring of s with length equal to pattern's length
        for i in range(len(s) - len(pattern) + 1):
            substring_hash = (prefix_hash_s[i + len(pattern)] - prefix_hash_s[i] * pow(p, len(pattern), m)) % m
            
            # If hashes match, check for at most one character difference
            if substring_hash == pattern_hash:
                diff_count = sum(1 for j in range(len(pattern)) if s[i + j] != pattern[j])
                if diff_count <= 1:
                    return i

        return -1