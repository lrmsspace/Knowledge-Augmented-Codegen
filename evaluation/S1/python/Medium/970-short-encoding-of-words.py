# Source: https://leetcode.com/problems/short-encoding-of-words/   |   Difficulty: Medium
#
# Problem Description:
# A valid encoding of an array of words is any reference string s and array of indices indices such that:
#
#
# 	words.length == indices.length
# 	The reference string s ends with the '#' character.
# 	For each index indices[i], the substring of s starting from indices[i] and up to (but not including) the next '#' character is equal to words[i].
#
#
# Given an array of words, return the length of the shortest reference string s possible of any valid encoding of words.
#
# Example:
# Input: words = ["time", "me", "bell"]
# Output: 10
# Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
# words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
# words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
# words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"
#
# Constraints:
# 1 <= words.length <= 2000
# 	1 <= words[i].length <= 7
# 	words[i] consists of only lowercase letters.
#
# Helpful references (internal KB):
# - Suffix array (array, string, suffix-array, divide-and-conquer, recursion)
#   • When to use: Use when you need to efficiently perform various string operations like pattern searching, finding repeated substrings, or comparing suffixes lexicographically on a given text. It is a fundamental data structure for advanced string algorithms.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string. It allows for efficient string operations, with construction typically achievable in O(N log N) or O(N) time for advanced algorithms.
#   • Invariants: The suffix array SA[i] stores the starting index of the i-th lexicographically smallest suffix.; All suffixes of the input string are present exactly once in the suffix array.
#   • Tips: Consider using SA-IS for optimal O(N) construction time and space complexity.; Pair the suffix array with an LCP array for enhanced functionality, such as finding longest common substrings.
#   • Pitfalls: Naive O(N^2 log N) construction is too slow for large input strings.; Implementing linear-time algorithms like SA-IS or DC3 can be complex and error-prone.
# - Tries (trie, tree, trie-match)
#   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
#   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
#   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
#   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
#   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
# - Aho-Corasick algorithm (trie, graph, dfs, trie-match)
#   • When to use: Use when searching for all occurrences of a fixed set of multiple patterns within a larger text efficiently. It is ideal for problems requiring simultaneous matching of a dictionary of strings.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, enabling efficient simultaneous searching for all pattern occurrences within a given text. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: Every node in the trie represents a prefix of at least one pattern.; A suffix link from node 'u' points to the node representing the longest proper suffix of 'u' that is also a prefix of some pattern.
#   • Tips: Build the trie for all patterns first, then compute suffix links.; Use BFS to construct suffix links level by level for efficiency.
#   • Pitfalls: Incorrectly building suffix links, especially for the root's children or when no direct transition exists.; High memory consumption if using arrays for transitions with a very large alphabet.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minimumLengthEncoding(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        trie = {}
        nodes = []

        for word in set(words):
            current = trie
            for char in reversed(word):
                if char not in current:
                    current[char] = {}
                current = current[char]
            nodes.append((current, len(word) + 1))

        return sum(length for node, length in nodes if not node)