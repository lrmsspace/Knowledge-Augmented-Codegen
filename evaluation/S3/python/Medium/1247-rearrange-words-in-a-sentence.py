# Source: https://leetcode.com/problems/rearrange-words-in-a-sentence/   |   Difficulty: Medium
#
# Problem Description:
# Given a sentence text (A sentence is a string of space-separated words) in the following format:
#
#
# 	First letter is in upper case.
# 	Each word in text are separated by a single space.
#
#
# Your task is to rearrange the words in text such that all words are rearranged in an increasing order of their lengths. If two words have the same length, arrange them in their original order.
#
# Return the new text following the format shown above.
#
# Example:
# Input: text = "Leetcode is cool"
# Output: "Is cool leetcode"
# Explanation: There are 3 words, "Leetcode" of length 8, "is" of length 2 and "cool" of length 4.
# Output is ordered by length and the new first word starts with capital letter.
#
# Constraints:
# text begins with a capital letter and then contains lowercase letters and single space between words.
# 	1 <= text.length <= 10^5
#
# Helpful references (internal KB):
# - Suffix array (array, string, suffix-array, binary-search)
#   • When to use: Use suffix arrays for efficient string processing tasks like finding all occurrences of a pattern, locating the longest common substring, or performing various substring queries. It provides a sorted index of all suffixes.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices in lexicographical order. It enables various string operations to be performed efficiently, often with O(N log N) or O(N) time complexity for construction and O(M log N) or O(M) for queries.
#   • Invariants: The suffix array A always contains N elements, where N is the length of the original string.; For any valid index i, A[i] stores a starting position within the original string S.
#   • Tips: Append a unique sentinel character (e.g., '$') to the string to ensure all suffixes are distinct.; Combine with a Longest Common Prefix (LCP) array for enhanced functionality, such as counting distinct substrings.
#   • Pitfalls: Naive construction by sorting all suffixes directly is inefficient (O(N^2 log N) or worse).; Implementing advanced construction algorithms from scratch can be complex and error-prone.
# - Aho-Corasick Algorithm for Pattern Searching (string, array, aho-corasick, enumeration)
#   • When to use: Use when you need to find all occurrences of a fixed set of patterns (a dictionary) within a larger text efficiently. It is particularly effective for scenarios with many patterns or long texts where patterns might overlap.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses this automaton to search for all pattern occurrences in a text in a single pass. It achieves a time complexity of O(N + M + K) where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: The trie structure correctly represents all prefixes of all patterns in the dictionary.; Each node's failure link points to the longest proper suffix of the string ending at that node which is also a prefix in the trie.
#   • Tips: Build the trie first from all patterns, marking terminal nodes.; Compute failure links using a BFS-like approach, similar to KMP's LPS array.
#   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to handle output links (dictionary links) will miss patterns found via failure transitions.
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def arrangeWords(self, text):
        """
        :type text: str
        :rtype: str
        """
        words = text.split()
        words[0] = words[0].lower()  # 将第一个单词转换为小写

        # 按照单词长度排序，保持相同长度的单词原有顺序
        words.sort(key=lambda w: len(w))

        # 将第一个单词首字母大写
        words[0] = words[0].capitalize()

        return ' '.join(words)