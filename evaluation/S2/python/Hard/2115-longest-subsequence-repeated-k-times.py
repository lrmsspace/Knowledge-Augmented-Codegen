# Source: https://leetcode.com/problems/longest-subsequence-repeated-k-times/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s of length n, and an integer k. You are tasked to find the longest subsequence repeated k times in string s.
#
# A subsequence is a string that can be derived from another string by deleting some or no characters without changing the order of the remaining characters.
#
# A subsequence seq is repeated k times in the string s if seq * k is a subsequence of s, where seq * k represents a string constructed by concatenating seq k times.
#
#
# 	For example, "bba" is repeated 2 times in the string "bababcba", because the string "bbabba", constructed by concatenating "bba" 2 times, is a subsequence of the string "bababcba".
#
#
# Return the longest subsequence repeated k times in string s. If multiple such subsequences are found, return the lexicographically largest one. If there is no such subsequence, return an empty string.
#
# Example:
# Input: s = "letsleetcode", k = 2
# Output: "let"
# Explanation: There are two longest subsequences repeated 2 times: "let" and "ete".
# "let" is the lexicographically largest one.
#
# Constraints:
# n == s.length
# 	2 <= k <= 2000
# 	2 <= n < min(2001, k * 8)
# 	s consists of lowercase English letters.
#
# Helpful references (internal KB):
# - Suffix Array (array, string, simulation, two-pointers)
#   • When to use: Use when needing to efficiently compare substrings, find all occurrences of a pattern, or determine lexicographical order among suffixes within a string.
#   • Idea: A Suffix Array stores sorted suffixes of a string, enabling fast substring comparisons and pattern searching. Construction typically takes O(N log N) time, with comparisons often O(1) after preprocessing.
#   • Invariants: The suffix array `p` contains all suffixes of the string `s` sorted lexicographically.; During construction, equivalence classes `c` correctly group suffixes that are identical up to a certain length `2^k`.
#   • Tips: Precompute log values for efficient block length calculation.; Utilize equivalence classes for O(1) comparison of power-of-two length substrings.
#   • Pitfalls: Complexity of suffix array construction can be tricky (e.g., O(N log N) vs O(N)).; Off-by-one errors when calculating block indices or lengths.
# - Finding repetitions (string, divide-and-conquer, recursion)
#   • When to use: This algorithm is used to find all occurrences of repeating substrings within a given string. It is suitable for problems requiring the identification of periodic patterns or structural redundancies.
#   • Idea: This algorithm, often exemplified by Main-Lorentz, uses a divide-and-conquer strategy with Z-function as a subroutine to efficiently find all repetitions in a string. It typically achieves an O(N log N) time complexity for finding and describing repetitions.
#   • Invariants: All repetitions fully contained within the left or right subproblems are found recursively.; Crossing repetitions are identified by combining information from both subproblems using Z-function.
#   • Tips: Understand the definition of a 'repetition' (e.g., Crochemore triples or (i, p, r) tuples).; Leverage string algorithms like Z-function for efficient substring matching in subproblems.
#   • Pitfalls: Expanding compact repetition tuples to full start/end indices can lead to O(N^2) complexity.; Incorrectly handling string reversal or concatenation for Z-function applications.
# - Lyndon factorization (string, greedy, two-pointers)
#   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
#   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
#   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
#   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
#   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def longestSubsequenceRepeatedK(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: str
        """
        # Step 1: Binary search on the length of the subsequence
        left, right = 1, len(s) // k
        longest_subseq = ""

        while left <= right:
            mid = (left + right) // 2
            if self.can_find_subsequence(s, k, mid):
                longest_subseq = self.get_lexicographically_largest_subsequence(s, k, mid)
                left = mid + 1
            else:
                right = mid - 1

        return longest_subseq