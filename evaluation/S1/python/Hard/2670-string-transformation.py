# Source: https://leetcode.com/problems/string-transformation/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings s and t of equal length n. You can perform the following operation on the string s:
#
#
# 	Remove a suffix of s of length l where 0 < l < n and append it at the start of s.
# 	For example, let s = 'abcd' then in one operation you can remove the suffix 'cd' and append it in front of s making s = 'cdab'.
#
#
# You are also given an integer k. Return the number of ways in which s can be transformed into t in exactly k operations.
#
# Since the answer can be large, return it modulo 109 + 7.
#
# Example:
# Input: s = "abcd", t = "cdab", k = 2
# Output: 2
# Explanation: 
# First way:
# In first operation, choose suffix from index = 3, so resulting s = "dabc".
# In second operation, choose suffix from index = 3, so resulting s = "cdab".
#
# Second way:
# In first operation, choose suffix from index = 1, so resulting s = "bcda".
# In second operation, choose suffix from index = 1, so resulting s = "cdab".
#
# Constraints:
# 2 <= s.length <= 5 * 105
# 	1 <= k <= 1015
# 	s.length == t.length
# 	s and t consist of only lowercase English alphabets.
#
# Helpful references (internal KB):
# - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
#   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
#   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
#   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
#   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
#   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
# - Binomial Coefficients (array, enumeration)
#   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
#   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
#   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
#   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
#   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
# - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
#   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
#   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
#   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
#   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfWays(self, s, t, k):
        """
        :type s: str
        :type t: str
        :type k: int
        :rtype: int
        """
        MOD = 10**9 + 7
        n = len(s)

        # Step 1: Find the index of t in the rotations of s
        idx = -1
        for i in range(n):
            if s[i:] + s[:i] == t:
                idx = i
                break

        if idx == -1:
            return 0

        # Step 2: Count the number of ways to reach idx in k steps
        # We can move from i to (i + l) % n for any l in [1, n-1]
        # This is equivalent to counting paths in a complete graph with n vertices and self-loops

        # dp[i][j] = number of ways to reach vertex j in i steps
        dp = [[0] * n for _ in range(k + 1)]
        dp[0][0] = 1  # Start at vertex 0

        for i in range(1, k + 1):
            for j in range(n):
                dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD  # Stay at j
                for l in range(1, n):
                    dp[i][(j + l) % n] = (dp[i][(j + l) % n] + dp[i - 1][j]) % MOD

        return dp[k][idx]