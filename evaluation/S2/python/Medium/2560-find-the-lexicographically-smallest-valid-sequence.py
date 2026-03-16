# Source: https://leetcode.com/problems/find-the-lexicographically-smallest-valid-sequence/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings word1 and word2.
#
# A string x is called almost equal to y if you can change at most one character in x to make it identical to y.
#
# A sequence of indices seq is called valid if:
#
#
# 	The indices are sorted in ascending order.
# 	Concatenating the characters at these indices in word1 in the same order results in a string that is almost equal to word2.
#
#
# Return an array of size word2.length representing the lexicographically smallest valid sequence of indices. If no such sequence of indices exists, return an empty array.
#
# Note that the answer must represent the lexicographically smallest array, not the corresponding string formed by those indices.
#
# Example:
# Input: word1 = "vbcca", word2 = "abc"
#
# Output: [0,1,2]
#
# Explanation:
#
# The lexicographically smallest valid sequence of indices is [0, 1, 2]:
#
#
# 	Change word1[0] to 'a'.
# 	word1[1] is already 'b'.
# 	word1[2] is already 'c'.
#
# Constraints:
# 1 <= word2.length < word1.length <= 3 * 105
# 	word1 and word2 consist only of lowercase English letters.
#
# Helpful references (internal KB):
# - Substring Search (string, array, two-pointers, simulation)
#   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
#   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
#   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
#   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# - 0-1 BFS (graph, array, dijkstra, bfs)
#   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
#   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
#   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
#   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
#   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def validSequence(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: List[int]
        """
        m, n = len(word1), len(word2)
        if n >= m:
            return []

        # Precompute the next occurrence of each character in word1
        next_occurrence = [[-1] * 26 for _ in range(m + 1)]
        for i in range(m - 1, -1, -1):
            for j in range(26):
                next_occurrence[i][j] = next_occurrence[i + 1][j]
            next_occurrence[i][ord(word1[i]) - ord('a')] = i

        result = []
        prev_index = -1
        for char in word2:
            char_index = ord(char) - ord('a')
            prev_index = next_occurrence[prev_index + 1][char_index]
            if prev_index == -1:
                return []
            result.append(prev_index)

        return result