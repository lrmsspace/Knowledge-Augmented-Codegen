# Source: https://leetcode.com/problems/find-special-substring-of-length-k/   |   Difficulty: Easy
#
# Problem Description:
# You are given a string s and an integer k.
#
# Determine if there exists a substring of length exactly k in s that satisfies the following conditions:
#
#
# 	The substring consists of only one distinct character (e.g., "aaa" or "bbb").
# 	If there is a character immediately before the substring, it must be different from the character in the substring.
# 	If there is a character immediately after the substring, it must also be different from the character in the substring.
#
#
# Return true if such a substring exists. Otherwise, return false.
#
# Example:
# Input: s = "aaabaaa", k = 3
#
# Output: true
#
# Explanation:
#
# The substring s[4..6] == "aaa" satisfies the conditions.
#
#
# 	It has a length of 3.
# 	All characters are the same.
# 	The character before "aaa" is 'b', which is different from 'a'.
# 	There is no character after "aaa".
#
# Constraints:
# 1 <= k <= s.length <= 100
# 	s consists of lowercase English letters only.
#
# Helpful references (internal KB):
# - Substring Search (string, array, two-pointers, simulation)
#   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
#   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
#   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
#   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
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
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def hasSpecialSubstring(self, s, k):
        """
        :type s: str
        :type k: int
        :rtype: bool
        """
        n = len(s)
        for i in range(n - k + 1):
            # Check if the substring s[i:i+k] consists of the same character
            if all(s[j] == s[i] for j in range(i, i + k)):
                # Check the character before the substring (if it exists)
                if i > 0 and s[i - 1] == s[i]:
                    continue
                # Check the character after the substring (if it exists)
                if i + k < n and s[i + k] == s[i]:
                    continue
                return True
        return False