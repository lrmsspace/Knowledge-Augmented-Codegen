# Source: https://leetcode.com/problems/length-of-the-longest-valid-substring/   |   Difficulty: Hard
#
# Problem Description:
# You are given a string word and an array of strings forbidden.
#
# A string is called valid if none of its substrings are present in forbidden.
#
# Return the length of the longest valid substring of the string word.
#
# A substring is a contiguous sequence of characters in a string, possibly empty.
#
# Example:
# Input: word = "cbaaaabc", forbidden = ["aaa","cb"]
# Output: 4
# Explanation: There are 11 valid substrings in word: "c", "b", "a", "ba", "aa", "bc", "baa", "aab", "ab", "abc" and "aabc". The length of the longest valid substring is 4. 
# It can be shown that all other substrings contain either "aaa" or "cb" as a substring.
#
# Constraints:
# 1 <= word.length <= 105
# 	word consists only of lowercase English letters.
# 	1 <= forbidden.length <= 105
# 	1 <= forbidden[i].length <= 10
# 	forbidden[i] consists only of lowercase English letters.
#
# Helpful references (internal KB):
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
# - Ordered Set - Python (ds, hashing)
#   • When to use: When you need a collection of unique items where the order of insertion must be preserved, allowing for efficient membership testing and iteration in that specific order.
#   • Idea: An ordered set stores unique elements while maintaining their original insertion order. It provides O(1) average time complexity for additions, deletions, and membership checks, typically implemented using a hash table combined with a linked list.
#   • Invariants: Every element within the set is unique.; The sequence of elements during iteration strictly follows their initial insertion order.
#   • Tips: In Python 3.7+, standard `dict`s maintain insertion order, effectively serving as ordered sets.; Use `collections.OrderedDict` for older Python versions or explicit semantic clarity.
#   • Pitfalls: Order is based on insertion, not value-based sorting; do not confuse the two.; Modifying an element's hash value while it's in the set can lead to undefined behavior.
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
    def longestValidSubstring(self, word, forbidden):
        """
        :type word: str
        :type forbidden: List[str]
        :rtype: int
        """
        forbidden_set = set(forbidden)
        max_length = 0
        n = len(word)

        for start in range(n):
            for end in range(start + 1, n + 1):
                substring = word[start:end]
                if substring in forbidden_set:
                    break
                max_length = max(max_length, end - start)

        return max_length