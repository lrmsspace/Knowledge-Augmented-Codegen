# Source: https://leetcode.com/problems/sum-of-prefix-scores-of-strings/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array words of size n consisting of non-empty strings.
#
# We define the score of a string term as the number of strings words[i] such that term is a prefix of words[i].
#
#
# 	For example, if words = ["a", "ab", "abc", "cab"], then the score of "ab" is 2, since "ab" is a prefix of both "ab" and "abc".
#
#
# Return an array answer of size n where answer[i] is the sum of scores of every non-empty prefix of words[i].
#
# Note that a string is considered as a prefix of itself.
#
# Example:
# Input: words = ["abc","ab","bc","b"]
# Output: [5,4,3,2]
# Explanation: The answer for each string is the following:
# - "abc" has 3 prefixes: "a", "ab", and "abc".
# - There are 2 strings with the prefix "a", 2 strings with the prefix "ab", and 1 string with the prefix "abc".
# The total is answer[0] = 2 + 2 + 1 = 5.
# - "ab" has 2 prefixes: "a" and "ab".
# - There are 2 strings with the prefix "a", and 2 strings with the prefix "ab".
# The total is answer[1] = 2 + 2 = 4.
# - "bc" has 2 prefixes: "b" and "bc".
# - There are 2 strings with the prefix "b", and 1 string with the prefix "bc".
# The total is answer[2] = 2 + 1 = 3.
# - "b" has 1 prefix: "b".
# - There are 2 strings with the prefix "b".
# The total is answer[3] = 2.
#
# Constraints:
# 1 <= words.length <= 1000
# 	1 <= words[i].length <= 1000
# 	words[i] consists of lowercase English letters.
#
# Helpful references (internal KB):
# - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
#   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
#   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
#   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
#   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
# - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
#   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
#   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
#   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
# - Z-function and its calculation (string, array, counting)
#   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
#   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
#   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
#   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
#   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def sumPrefixScores(self, words):
        """
        :type words: List[str]
        :rtype: List[int]
        """
        # Step 1: Build a trie and count prefix occurrences
        trie = {}
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {'#count': 0}
                node = node[char]
                node['#count'] += 1

        # Step 2: Calculate prefix scores for each word
        result = []
        for word in words:
            score = 0
            node = trie
            for char in word:
                node = node[char]
                score += node['#count']
            result.append(score)

        return result