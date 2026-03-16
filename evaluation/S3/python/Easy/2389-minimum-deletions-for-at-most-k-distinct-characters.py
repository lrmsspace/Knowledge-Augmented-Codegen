# Source: https://leetcode.com/problems/minimum-deletions-for-at-most-k-distinct-characters/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s consisting of lowercase English letters, and an integer k.
#
# Your task is to delete some (possibly none) of the characters in the string so that the number of distinct characters in the resulting string is at most k.
#
# Return the minimum number of deletions required to achieve this.
#
# Example:
# Input: s = "abc", k = 2
#
# Output: 1
#
# Explanation:
#
#
# 	s has three distinct characters: 'a', 'b' and 'c', each with a frequency of 1.
# 	Since we can have at most k = 2 distinct characters, remove all occurrences of any one character from the string.
# 	For example, removing all occurrences of 'c' results in at most k distinct characters. Thus, the answer is 1.
#
# Constraints:
# 1 <= s.length <= 16
# 	1 <= k <= 16
# 	s consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Finding repetitions (string, array, z-function, enumeration)
#   • When to use: This algorithm efficiently finds all repetitions (periodic substrings) within a given string by combining divide-and-conquer with the Z-function. It is particularly useful for identifying overlapping or crossing periodic patterns.
#   • Idea: The Main-Lorentz algorithm finds all repetitions in a string by recursively splitting it into halves and identifying 'crossing repetitions' using the Z-function. This approach achieves an optimal O(N log N) time complexity.
#   • Invariants: For any fixed `cntr` position, all identified crossing repetitions have a total length of $2 	imes (|u| - cntr)$.; The segment $u[cntr - k_1 	ext{ to } cntr - 1]$ is identical to $u[|u| - k_1 	ext{ to } |u| - 1]$.
#   • Tips: Employ divide-and-conquer to break the problem into subproblems for repetitions within halves and crossing repetitions.; Utilize the Z-function to compute $k_1$ and $k_2$ values in O(1) for each `cntr` position, speeding up crossing repetition detection.
#   • Pitfalls: Correctly identifying and defining 'crossing repetitions' is the most intricate part of the algorithm.; Careful implementation of the Z-function for both the original and reversed string segments is crucial.
# - Suffix Array (string, array, counting-sort, radix-sort)
#   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
#   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
#   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
#   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
#   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minDeletion(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        from collections import Counter

        # Count the frequency of each character in the string
        char_count = Counter(s)

        # Get the frequencies and sort them in descending order
        frequencies = sorted(char_count.values(), reverse=True)

        # If the number of distinct characters is already less than or equal to k, no deletions are needed
        if len(frequencies) <= k:
            return 0

        # Calculate the number of deletions needed to reduce distinct characters to k
        deletions = sum(frequencies[k:])  # Sum of frequencies of characters that need to be removed

        return deletions