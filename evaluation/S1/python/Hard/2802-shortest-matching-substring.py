# Source: https://leetcode.com/problems/shortest-matching-substring/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and a pattern string p, where p contains exactly two '*' characters.
#
# The '*' in p matches any sequence of zero or more characters.
#
# Return the length of the shortest substring in s that matches p. If there is no such substring, return -1.
# Note: The empty substring is considered valid.
#
# Example:
# Input: s = "abaacbaecebce", p = "ba*c*ce"
#
# Output: 8
#
# Explanation:
#
# The shortest matching substring of p in s is "baecebce".
#
# Constraints:
# 1 <= s.length <= 105
# 	2 <= p.length <= 105
# 	s contains only lowercase English letters.
# 	p contains only lowercase English letters and exactly two '*'.
#
# Helpful references (internal KB):
# - Substring Search (string, array, two-pointers, simulation)
#   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
#   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
#   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
#   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
# - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
#   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
#   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
#   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
#   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
#   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def shortestMatchingSubstring(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: int
        """
        # Split the pattern into three parts: prefix, middle, and suffix
        prefix, middle, suffix = p.split('*')
        
        # Find all occurrences of the prefix in s
        prefix_positions = []
        start = 0
        while True:
            start = s.find(prefix, start)
            if start == -1:
                break
            prefix_positions.append(start)
            start += 1  # Move to the next character for the next search
        
        # Find all occurrences of the suffix in s
        suffix_positions = []
        start = 0
        while True:
            start = s.find(suffix, start)
            if start == -1:
                break
            suffix_positions.append(start)
            start += 1  # Move to the next character for the next search
        
        # If there are no occurrences of either prefix or suffix, return -1
        if not prefix_positions or not suffix_positions:
            return -1
        
        min_length = float('inf')
        
        # Check each combination of prefix and suffix positions
        for prefix_pos in prefix_positions:
            for suffix_pos in suffix_positions:
                if prefix_pos < suffix_pos:  # Ensure prefix comes before suffix
                    middle_start = prefix_pos + len(prefix)
                    middle_end = suffix_pos
                    middle_substring = s[middle_start:middle_end]
                    
                    # Check if the middle substring matches the middle part of the pattern
                    if self.matches_middle(middle_substring, middle):
                        total_length = len(prefix) + len(middle_substring) + len(suffix)
                        min_length = min(min_length, total_length)
        
        return min_length if min_length != float('inf') else -1