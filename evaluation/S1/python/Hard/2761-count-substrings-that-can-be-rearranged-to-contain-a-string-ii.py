# Source: https://leetcode.com/problems/count-substrings-that-can-be-rearranged-to-contain-a-string-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given two strings word1 and word2.
#
# A string x is called valid if x can be rearranged to have word2 as a prefix.
#
# Return the total number of valid substrings of word1.
#
# Note that the memory limits in this problem are smaller than usual, so you must implement a solution with a linear runtime complexity.
#
# Example:
# Input: word1 = "bcca", word2 = "abc"
#
# Output: 1
#
# Explanation:
#
# The only valid substring is "bcca" which can be rearranged to "abcc" having "abc" as a prefix.
#
# Constraints:
# 1 <= word1.length <= 106
# 	1 <= word2.length <= 104
# 	word1 and word2 consist only of lowercase English letters.
#
# Helpful references (internal KB):
# - Suffix Array (string, array, counting-sort, radix-sort)
#   • When to use: Use when you need to efficiently query or analyze all suffixes of a string, often for pattern matching, string searching, or finding repeated substrings. It provides a sorted order of all suffixes.
#   • Idea: The Suffix Array algorithm constructs an array containing the starting indices of all suffixes of a string, sorted lexicographically. It typically uses a doubling strategy with counting sort or radix sort in each step, achieving an O(N log N) time complexity.
#   • Invariants: After iteration k, p contains the sorted indices of all cyclic substrings of length 2^k.; After iteration k, c[i] represents the equivalence class of the cyclic substring starting at i with length 2^k.
#   • Tips: Append a unique, smallest character (e.g., '$') to the string to handle suffixes as cyclic shifts.; Utilize counting sort for efficient sorting of characters and pairs of equivalence classes.
#   • Pitfalls: Incorrectly handling the sentinel character can lead to incorrect suffix order or out-of-bounds access.; Off-by-one errors when calculating indices for cyclic shifts or substring lengths.
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Z-function and its calculation (string, array, two-pointers)
#   • When to use: Use when you need to find the length of the longest common prefix between a string and all its suffixes efficiently. It is fundamental for various string matching and pattern searching problems.
#   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the original string and its suffix starting at index i. This algorithm calculates the entire Z-array in O(N) time complexity.
#   • Invariants: For all k < i, z[k] has been correctly computed.; The interval [l, r) always represents the rightmost segment match found so far.
#   • Tips: Leverage previously computed Z-values to avoid redundant comparisons.; Maintain a [l, r) window representing the rightmost segment match found so far.
#   • Pitfalls: Incorrectly handling the base case z[0] (usually set to 0).; Off-by-one errors when calculating the length of the prefix or updating the window.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def validSubstringCount(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """
        from collections import defaultdict

        len1, len2 = len(word1), len(word2)

        # Step 1: Count frequency of characters in word2
        freq_word2 = defaultdict(int)
        for char in word2:
            freq_word2[char] += 1

        # Step 2: Initialize frequency dictionary for the current window in word1
        freq_window = defaultdict(int)
        valid_count = 0
        left = 0

        # Step 3: Sliding window over word1
        for right in range(len1):
            freq_window[word1[right]] += 1

            # Shrink the window from the left if it exceeds the length of word2
            while right - left + 1 > len2:
                freq_window[word1[left]] -= 1
                if freq_window[word1[left]] == 0:
                    del freq_window[word1[left]]
                left += 1

            # Check if the current window can form word2
            if right - left + 1 == len2:
                can_form = True
                for char in freq_word2:
                    if freq_window[char] < freq_word2[char]:
                        can_form = False
                        break
                if can_form:
                    valid_count += 1

        return valid_count  