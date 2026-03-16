# Source: https://leetcode.com/problems/vowel-spellchecker/   |   Difficulty: Medium
#
# Problem Description:
# Given a wordlist, we want to implement a spellchecker that converts a query word into a correct word.
#
# For a given query word, the spell checker handles two categories of spelling mistakes:
#
#
# 	Capitalization: If the query matches a word in the wordlist (case-insensitive), then the query word is returned with the same case as the case in the wordlist.
#
# Example:
# wordlist = ["yellow"], query = "YellOw": correct = "yellow"
#
# Constraints:
# 1 <= wordlist.length, queries.length <= 5000
# 	1 <= wordlist[i].length, queries[i].length <= 7
# 	wordlist[i] and queries[i] consist only of only English letters.
#
# Helpful references (internal KB):
# - String Hashing (string, array, hashing, enumeration)
#   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
#   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
#   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
#   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
#   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: When you need O(1) query time for any associative operation (like sum, min, max, GCD) on a static array, after an O(N log N) preprocessing step.
#   • Idea: A Disjoint Sparse Table is a data structure that supports O(1) range queries for any associative operation on a static array. It achieves this by precomputing results for specific disjoint and overlapping ranges, with an O(N log N) construction time and space complexity.
#   • Invariants: table[k][i] stores the result of the operation for a range of length 2^k starting at index i.; For any query [L, R], the result is obtained by combining two precomputed values from blocks that cover [L, mid] and [mid+1, R].
#   • Tips: Understand the block decomposition based on powers of two for construction.; Queries combine results from two precomputed blocks that cover the query range.
#   • Pitfalls: Does not support point updates efficiently; any modification requires a full rebuild.; Higher space complexity of O(N log N) compared to some other range query structures.
# - Aho-Corasick Algorithm for Pattern Searching (string, trie, aho-corasick, simulation)
#   • When to use: Use when you need to find all occurrences of a fixed set of patterns within a larger text efficiently. It's particularly effective for scenarios involving many patterns and potential overlaps.
#   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, then uses it to find all occurrences of these patterns in a text in a single pass. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
#   • Invariants: All patterns in the dictionary are correctly represented in the trie (goto function).; The failure link `f[u]` for any state `u` points to the state representing the longest proper suffix of the string corresponding to `u` that is also a prefix of some pattern.
#   • Tips: Build the trie (goto function) first from all patterns.; Construct failure links using a BFS-like approach to ensure correct shortest suffix matching.
#   • Pitfalls: Incorrectly building failure links can lead to missed matches or infinite loops.; Forgetting to propagate output matches through failure links can miss valid pattern occurrences.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def spellchecker(self, wordlist, queries):
        """
        :type wordlist: List[str]
        :type queries: List[str]
        :rtype: List[str]
        """
        exact_words = set(wordlist)
        lower_map = {}
        vowel_map = {}
        
        def devowel(word):
            return ''.join('*' if c in 'aeiou' else c for c in word)
        
        for word in wordlist:
            lower_word = word.lower()
            if lower_word not in lower_map:
                lower_map[lower_word] = word
            devoweled_word = devowel(lower_word)
            if devoweled_word not in vowel_map:
                vowel_map[devoweled_word] = word
        
        result = []
        for query in queries:
            if query in exact_words:
                result.append(query)
            else:
                lower_query = query.lower()
                if lower_query in lower_map:
                    result.append(lower_map[lower_query])
                else:
                    devoweled_query = devowel(lower_query)
                    if devoweled_query in vowel_map:
                        result.append(vowel_map[devoweled_query])
                    else:
                        result.append("")
        
        return result