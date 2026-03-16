# Source: https://leetcode.com/problems/minimum-number-of-valid-strings-to-form-target-ii/   |   Difficulty: Hard
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
# 	1 <= words[i].length <= 5 * 104
# 	The input is generated such that sum(words[i].length) <= 105.
# 	words[i] consists only of lowercase English letters.
# 	1 <= target.length <= 5 * 104
# 	target consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - Tries (trie, tree, trie-match)
#   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
#   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
#   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
# - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-1d)
#   • When to use: Used for efficient string searching and pattern matching in linear time. It's also fundamental for various string algorithms that leverage self-matching properties.
#   • Idea: The prefix function computes for each position in a string the length of the longest proper prefix of its substring that is also a suffix of that substring. This forms the core of the Knuth-Morris-Pratt (KMP) algorithm, enabling linear time O(N) string matching.
#   • Invariants: For each i, pi[i] is the length of the longest proper prefix of s[0...i] that is also a suffix of s[0...i].; The current j (length of the matched prefix) always represents pi[i-1] or a shorter valid prefix length.
#   • Tips: The prefix function array (pi array) stores lengths, not indices.; It can be used to build the KMP automaton for pattern matching.
#   • Pitfalls: Confusing proper prefix/suffix with non-proper ones.; Incorrectly handling the base case pi[0] = 0.
# - Suffix Automaton (graph, string, simulation)
#   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
#   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
#   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
#   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
#   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
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
        # Build a trie from the words
        trie = {}
        for word in words:
            node = trie
            for char in word:
                if char not in node:
                    node[char] = {}
                node = node[char]
        
        n = len(target)
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        
        for i in range(n):
            if dp[i] == float('inf'):
                continue
            
            node = trie
            for j in range(i, n):
                char = target[j]
                if char not in node:
                    break
                node = node[char]
                dp[j + 1] = min(dp[j + 1], dp[i] + 1)
        
        return dp[n] if dp[n] != float('inf') else -1