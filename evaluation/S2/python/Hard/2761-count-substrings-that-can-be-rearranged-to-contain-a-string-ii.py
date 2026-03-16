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
# - Z-function and its calculation (string, array, counting)
#   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
#   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
#   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
#   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
#   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
# - Digit DP (array, number, digit-dp)
#   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
#   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
#   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
#   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
#   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
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
        from collections import Counter

        count2 = Counter(word2)
        required = len(count2)
        formed = 0
        window_counts = {}
        left = 0
        ans = 0

        for right in range(len(word1)):
            char = word1[right]
            window_counts[char] = window_counts.get(char, 0) + 1

            if char in count2 and window_counts[char] == count2[char]:
                formed += 1

            while formed == required:
                ans += len(word1) - right

                left_char = word1[left]
                window_counts[left_char] -= 1
                if left_char in count2 and window_counts[left_char] < count2[left_char]:
                    formed -= 1
                left += 1

        return ans