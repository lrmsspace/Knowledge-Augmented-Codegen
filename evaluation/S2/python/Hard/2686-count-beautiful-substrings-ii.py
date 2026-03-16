# Source: https://leetcode.com/problems/count-beautiful-substrings-ii/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string s and a positive integer k.
#
# Let vowels and consonants be the number of vowels and consonants in a string.
#
# A string is beautiful if:
#
#
# 	vowels == consonants.
# 	(vowels * consonants) % k == 0, in other terms the multiplication of vowels and consonants is divisible by k.
#
#
# Return the number of non-empty beautiful substrings in the given string s.
#
# A substring is a contiguous sequence of characters in a string.
#
# Vowel letters in English are 'a', 'e', 'i', 'o', and 'u'.
#
# Consonant letters in English are every letter except vowels.
#
# Example:
# Input: s = "baeyh", k = 2
# Output: 2
# Explanation: There are 2 beautiful substrings in the given string.
# - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["y","h"]).
# You can see that string "aeyh" is beautiful as vowels == consonants and vowels * consonants % k == 0.
# - Substring "baeyh", vowels = 2 (["a",e"]), consonants = 2 (["b","y"]).
# You can see that string "baey" is beautiful as vowels == consonants and vowels * consonants % k == 0.
# It can be shown that there are only 2 beautiful substrings in the given string.
#
# Constraints:
# 1 <= s.length <= 5 * 104
# 	1 <= k <= 1000
# 	s consists of only English lowercase letters.
#
# Helpful references (internal KB):
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def beautifulSubstrings(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: int
        """
        vowels = set('aeiou')
        count = 0
        for i in range(len(s)):
            v_count = 0
            c_count = 0
            for j in range(i, len(s)):
                if s[j] in vowels:
                    v_count += 1
                else:
                    c_count += 1
                if v_count == c_count and (v_count * c_count) % k == 0:
                    count += 1
        return count