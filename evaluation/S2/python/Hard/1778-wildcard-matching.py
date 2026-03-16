# Source: https://leetcode.com/problems/wildcard-matching/   |   Difficulty: Hard
#
# Problem Description:
# Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:
#
#
# 	'?' Matches any single character.
# 	'*' Matches any sequence of characters (including the empty sequence).
#
#
# The matching should cover the entire input string (not partial).
#
# Example:
# Input: s = "aa", p = "a"
# Output: false
# Explanation: "a" does not match the entire string "aa".
#
# Constraints:
# 0 <= s.length, p.length <= 2000
# 	s contains only lowercase English letters.
# 	p contains only lowercase English letters, '?' or '*'.
#
# Helpful references (internal KB):
# - Substring Search (string, array, kmp, simulation)
#   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
#   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
#   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
#   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
# - Tries (trie, array, trie-match)
#   • When to use: Use when managing string keys in a symbol table and needing efficient prefix, wildcard, or longest prefix matching operations, offering flexibility beyond binary search trees and speed comparable to hashing.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set or associative array where keys are typically strings. It allows for efficient retrieval of keys based on their prefixes, achieving O(L) time complexity for operations, where L is the key length.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node exists only if it is part of at least one stored key.
#   • Tips: Choose an appropriate branching factor (R) based on the alphabet size.; Represent children using arrays for fixed alphabets or hash maps for sparse ones.
#   • Pitfalls: High memory consumption for large alphabets or sparse data.; Deletion of keys can be complex, requiring careful handling of empty branches.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """
        # 1. 初始化指针和变量
        s_len, p_len = len(s), len(p)
        s_idx = p_idx = 0
        star_idx = -1
        s_tmp_idx = -1

        # 2. 遍历字符串 s
        while s_idx < s_len:
            # 3. 如果当前字符匹配或模式字符是 '?'
            if p_idx < p_len and (p[p_idx] == s[s_idx] or p[p_idx] == '?'):
                s_idx += 1
                p_idx += 1
            # 4. 如果模式字符是 '*'
            elif p_idx < p_len and p[p_idx] == '*':
                star_idx = p_idx
                s_tmp_idx = s_idx
                p_idx += 1
            # 5. 如果之前有 '*'，尝试回退并匹配更多字符
            elif star_idx != -1:
                p_idx = star_idx + 1
                s_tmp_idx += 1
                s_idx = s_tmp_idx
            # 6. 不匹配且没有 '*' 可回退，返回 False
            else:
                return False

        # 7. 检查模式剩余部分是否全是 '*'
        while p_idx < p_len and p[p_idx] == '*':
            p_idx += 1

        return p_idx == p_len