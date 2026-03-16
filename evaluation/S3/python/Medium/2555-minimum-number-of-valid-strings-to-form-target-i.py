# Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-i/   |   Difficulty: Medium
#
# Problem Description:
# You are given an array of strings words and a string target.
#
# A string x is called valid if x is a prefix of any string in words.
#
# Return the minimum number of valid strings that can be concatenated to form target. If it is not possible to form target, return -1.
#
# Example:
# Input: words = ["abc","aaaaa","bcdef"], target = "aabcdabc"
#
# Output: 3
#
# Explanation:
#
# The target string can be formed by concatenating:
#
#
# 	Prefix of length 2 of words[1], i.e. "aa".
# 	Prefix of length 3 of words[2], i.e. "bcd".
# 	Prefix of length 3 of words[0], i.e. "abc".
#
# Constraints:
# 1 <= words.length <= 100
# 	1 <= words[i].length <= 5 * 103
# 	The input is generated such that sum(words[i].length) <= 105.
# 	words[i] consists only of lowercase English letters.
# 	1 <= target.length <= 5 * 103
# 	target consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
#   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
#   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
#   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
# - Tries (trie, tree, trie-match)
#   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
#   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
#   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
# - Tries (trie, array, trie-match)
#   • When to use: Use when managing string keys in a symbol table and needing efficient prefix, wildcard, or longest prefix matching operations, offering flexibility beyond binary search trees and speed comparable to hashing.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set or associative array where keys are typically strings. It allows for efficient retrieval of keys based on their prefixes, achieving O(L) time complexity for operations, where L is the key length.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node exists only if it is part of at least one stored key.
#   • Tips: Choose an appropriate branching factor (R) based on the alphabet size.; Represent children using arrays for fixed alphabets or hash maps for sparse ones.
#   • Pitfalls: High memory consumption for large alphabets or sparse data.; Deletion of keys can be complex, requiring careful handling of empty branches.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minValidStrings(self, words, target):
        """
        :type words: List[str]
        :type target: str
        :rtype: int
        """
        # Step 1: Create a set of valid prefixes from words
        valid_prefixes = set()
        for word in words:
            for i in range(1, len(word) + 1):
                valid_prefixes.add(word[:i])
        
        # Step 2: Use dynamic programming to find the minimum number of valid strings to form target
        dp = [float('inf')] * (len(target) + 1)
        dp[0] = 0  # Base case: 0 valid strings needed to form an empty string
        
        for i in range(1, len(target) + 1):
            for j in range(i):
                if dp[j] != float('inf') and target[j:i] in valid_prefixes:
                    dp[i] = min(dp[i], dp[j] + 1)
        
        return dp[len(target)] if dp[len(target)] != float('inf') else -1