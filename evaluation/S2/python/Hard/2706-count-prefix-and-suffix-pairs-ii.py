# Source: https://leetcode.com/problems/count-prefix-and-suffix-pairs-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed string array words.
#
# Let's define a boolean function isPrefixAndSuffix that takes two strings, str1 and str2:
#
#
# 	isPrefixAndSuffix(str1, str2) returns true if str1 is both a prefix and a suffix of str2, and false otherwise.
#
#
# For example, isPrefixAndSuffix("aba", "ababa") is true because "aba" is a prefix of "ababa" and also a suffix, but isPrefixAndSuffix("abc", "abcd") is false.
#
# Return an integer denoting the number of index pairs (i, j) such that i < j, and isPrefixAndSuffix(words[i], words[j]) is true.
#
# Example:
# Input: words = ["a","aba","ababa","aa"]
# Output: 4
# Explanation: In this example, the counted index pairs are:
# i = 0 and j = 1 because isPrefixAndSuffix("a", "aba") is true.
# i = 0 and j = 2 because isPrefixAndSuffix("a", "ababa") is true.
# i = 0 and j = 3 because isPrefixAndSuffix("a", "aa") is true.
# i = 1 and j = 2 because isPrefixAndSuffix("aba", "ababa") is true.
# Therefore, the answer is 4.
#
# Constraints:
# 1 <= words.length <= 105
# 	1 <= words[i].length <= 105
# 	words[i] consists only of lowercase English letters.
# 	The sum of the lengths of all words[i] does not exceed 5 * 105.
#
# Helpful references (internal KB):
# - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
#   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
#   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
#   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
#   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
# - Suffix Automaton (string, enumeration)
#   • When to use: When you need to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings or pattern matching in linear time.
#   • Idea: A Suffix Automaton is a minimal finite automaton that accepts all suffixes of a given string. It implicitly represents all substrings and can be constructed in linear time, O(N) where N is the string length.
#   • Invariants: Every path from the initial state spells a substring of the original string.; Each state represents a set of substrings that share the same end positions in the original string.
#   • Tips: Understand the concept of `endpos` sets and how they define states.; The number of states and transitions in a suffix automaton is linear with respect to string length.
#   • Pitfalls: The construction algorithm can be complex and prone to off-by-one errors or incorrect link updates.; Debugging state transitions and suffix links requires careful attention.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countPrefixSuffixPairs(self, words):
        """
        :type words: List[str]
        :rtype: int
        """
        # Step 1: Group words by their lengths
        length_map = {}
        for word in words:
            length_map.setdefault(len(word), []).append(word)

        count = 0

        # Step 2: For each group of words with the same length
        for length, group in length_map.items():
            # Create a set for quick lookup
            word_set = set(group)

            # Step 3: Check each pair of words in the group
            for i in range(len(group)):
                for j in range(i + 1, len(group)):
                    if group[i] == group[j]:
                        count += 1  # Identical words are both prefix and suffix
                    elif group[i] == group[j][:length] and group[i] == group[j][-length:]:
                        count += 1

        return count