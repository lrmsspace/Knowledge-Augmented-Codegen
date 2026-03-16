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
# - Substring Search (string, array, kmp, simulation)
#   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
#   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
#   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
#   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
# - Substring Search (string, array, kmp)
#   • When to use: Use when needing to find all occurrences or the first occurrence of a pattern string within a larger text string efficiently. It is particularly useful when the pattern might have significant self-overlapping prefixes and suffixes, allowing for linear time complexity.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently searches for occurrences of a pattern within a text by avoiding redundant comparisons. It preprocesses the pattern to build a Deterministic Finite Automaton (DFA) or Longest Proper Prefix Suffix (LPS) array, achieving O(N + M) time complexity.
#   • Invariants: During DFA construction, dfa[c][j] correctly stores the next state if character c is encountered in state j.; During DFA construction, x maintains the length of the longest proper prefix of pattern[0...j-1] that is also a suffix of pattern[0...j-1].
#   • Tips: Precompute the LPS array or DFA for the pattern to guide the search.; The LPS array indicates the longest proper prefix that is also a suffix, enabling efficient shifts.
#   • Pitfalls: Incorrect construction of the LPS array or DFA is a common source of errors.; High constant factors for small alphabets or short patterns might make simpler algorithms faster.
# - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
#   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
#   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
#   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
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
        from collections import deque

        queue = deque([(s1, s2)])
        count = 0
        mod = 10**9 + 7

        while queue:
            low, high = queue.popleft()
            if low > high:
                continue
            if evil in low:
                continue
            if low == high:
                count = (count + 1) % mod
                continue
            for c in range(ord(low[0]), ord(high[0]) + 1):
                new_low = chr(c) + low[1:]
                new_high = chr(c) + high[1:]
                queue.append((new_low, new_high))

        return count