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
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
# - Suffix Array (array, string, simulation, two-pointers)
#   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
#   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
#   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
#   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
#   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
# - Factorial modulo 
# p (number, counting, recursion)
#   • When to use: Use when the problem asks for the total count of possibilities or arrangements that can be naturally broken down into smaller, self-similar subproblems. It's effective for exploring decision trees or state spaces.
#   • Idea: Counting determines the number of elements or event occurrences. It uses combinatorial or iterative/recursive methods, often with O(N) or O(log N) complexity.
#   • Invariants: Each recursive call processes a smaller, well-defined subproblem.; The base cases correctly return the count for the simplest scenarios.
#   • Tips: Identify the smallest subproblem and its base cases to stop recursion.; Define the recursive relation clearly, showing how larger problems depend on smaller ones.
#   • Pitfalls: Incorrectly defining base cases can lead to infinite recursion or incorrect results.; Overlapping subproblems without memoization can lead to exponential time complexity.
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
        mod = 10**9 + 7
        m = len(evil)

        # Build KMP table for evil string
        kmp = [0] * m
        for i in range(1, m):
            j = kmp[i - 1]
            while j > 0 and evil[i] != evil[j]:
                j = kmp[j - 1]
            if evil[i] == evil[j]:
                j += 1
            kmp[i] = j

        @functools.lru_cache(None)
        def dp(i, prefix_s1, prefix_s2, evil_idx):
            if evil_idx == m:
                return 0
            if i == n:
                return 1

            start_char = s1[i] if prefix_s1 else 'a'
            end_char = s2[i] if prefix_s2 else 'z'
            total = 0

            for c in range(ord(start_char), ord(end_char) + 1):
                c = chr(c)
                new_prefix_s1 = prefix_s1 and (c == start_char)
                new_prefix_s2 = prefix_s2 and (c == end_char)

                # Update evil index using KMP logic
                new_evil_idx = evil_idx
                while new_evil_idx > 0 and c != evil[new_evil_idx]:
                    new_evil_idx = kmp[new_evil_idx - 1]
                if c == evil[new_evil_idx]:
                    new_evil_idx += 1

                total += dp(i + 1, new_prefix_s1, new_prefix_s2, new_evil_idx)
                total %= mod

            return total

        return dp(0, True, True, 0)