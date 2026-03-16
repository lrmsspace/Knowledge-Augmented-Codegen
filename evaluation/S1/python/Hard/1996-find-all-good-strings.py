# Source: https://leetcode.com/problems/find-all-good-strings/   |   Difficulty: Hard
#
# Problem Description:
# Given the strings s1 and s2 of size n and the string evil, return the number of good strings.
#
# A good string has size n, it is alphabetically greater than or equal to s1, it is alphabetically smaller than or equal to s2, and it does not contain the string evil as a substring. Since the answer can be a huge number, return this modulo 109 + 7.
#
# Example:
# Input: n = 2, s1 = "aa", s2 = "da", evil = "b"
# Output: 51 
# Explanation: There are 25 good strings starting with 'a': "aa","ac","ad",...,"az". Then there are 25 good strings starting with 'c': "ca","cc","cd",...,"cz" and finally there is one good string starting with 'd': "da".
#
# Constraints:
# s1.length == n
# 	s2.length == n
# 	s1 <= s2
# 	1 <= n <= 500
# 	1 <= evil.length <= 50
# 	All strings consist of lowercase English letters.
#
# Helpful references (internal KB):
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Substring Search (string, array, kmp, simulation)
#   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
#   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
#   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
#   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
# - Knuth's Optimization (array, interval, dp-2d)
#   • When to use: When a range DP problem has a recurrence of the form dp(i, j) = min_k [dp(i, k) + dp(k+1, j) + C(i, j)] and the optimal splitting points satisfy opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Idea: Knuth's Optimization is a technique to speed up certain dynamic programming problems on ranges from O(N^3) to O(N^2) time complexity. It applies when the optimal splitting point for a subproblem exhibits a monotonic property across adjacent subproblems.
#   • Invariants: dp[i][j] stores the minimum cost for the interval [i, j].; opt[i][j] stores the optimal split point k for interval [i, j].
#   • Tips: Verify the quadrangle inequality for the cost function C(i, j).; Ensure the optimal split points exhibit monotonicity: opt(i, j-1) <= opt(i, j) <= opt(i+1, j).
#   • Pitfalls: Applying the optimization without rigorously verifying the monotonicity condition.; Incorrectly calculating the cost function C(i, j) or its properties.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findGoodStrings(self, n, s1, s2, evil):
        """
        :type n: int
        :type s1: str
        :type s2: str
        :type evil: str
        :rtype: int
        """
        MOD = 10**9 + 7
        m = len(evil)

        # Build KMP table for evil string
        lps = [0] * m
        for i in range(1, m):
            j = lps[i - 1]
            while j > 0 and evil[i] != evil[j]:
                j = lps[j - 1]
            if evil[i] == evil[j]:
                j += 1
            lps[i] = j

        # DP cache: dp(pos, prefix_s1, prefix_s2, evil_match)
        from functools import lru_cache

        @lru_cache(None)
        def dp(pos, prefix_s1, prefix_s2, evil_match):
            if evil_match == m:  # Found evil as substring
                return 0
            if pos == n:  # Reached end of string
                return 1

            start_char = s1[pos] if prefix_s1 else 'a'
            end_char = s2[pos] if prefix_s2 else 'z'
            total = 0

            for c in range(ord(start_char), ord(end_char) + 1):
                char = chr(c)
                new_prefix_s1 = prefix_s1 and (char == start_char)
                new_prefix_s2 = prefix_s2 and (char == end_char)

                # Update evil match using KMP logic
                new_evil_match = evil_match
                while new_evil_match > 0 and char != evil[new_evil_match]:
                    new_evil_match = lps[new_evil_match - 1]
                if char == evil[new_evil_match]:
                    new_evil_match += 1

                total += dp(pos + 1, new_prefix_s1, new_prefix_s2, new_evil_match)
                total %= MOD

            return total

        return dp(0, True, True, 0)