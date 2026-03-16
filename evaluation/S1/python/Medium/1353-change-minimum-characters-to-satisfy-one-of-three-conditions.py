# Source: https://leetcode.com/problems/change-minimum-characters-to-satisfy-one-of-three-conditions/   |   Difficulty: Medium
#
# Problem Description:
# You are given two strings a and b that consist of lowercase letters. In one operation, you can change any character in a or b to any lowercase letter.
#
# Your goal is to satisfy one of the following three conditions:
#
#
# 	Every letter in a is strictly less than every letter in b in the alphabet.
# 	Every letter in b is strictly less than every letter in a in the alphabet.
# 	Both a and b consist of only one distinct letter.
#
#
# Return the minimum number of operations needed to achieve your goal.
#
# Example:
# Input: a = "aba", b = "caa"
# Output: 2
# Explanation: Consider the best way to make each condition true:
# 1) Change b to "ccc" in 2 operations, then every letter in a is less than every letter in b.
# 2) Change a to "bbb" and b to "aaa" in 3 operations, then every letter in b is less than every letter in a.
# 3) Change a to "aaa" and b to "aaa" in 2 operations, then a and b consist of one distinct letter.
# The best way was done in 2 operations (either condition 1 or condition 3).
#
# Constraints:
# 1 <= a.length, b.length <= 105
# 	a and b consist only of lowercase letters.
#
# Helpful references (internal KB):
# - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, dp-2d)
#   • When to use: Use when efficiently finding all occurrences of a pattern in a text, analyzing string periodicity, or counting distinct substrings. It is especially useful for processing extremely long or recursively defined strings where explicit construction is impossible.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm leverages a precomputed prefix function (LPS array) to avoid redundant comparisons during string searching, achieving linear time complexity. The prefix function itself determines the longest proper prefix of a string that is also a suffix, enabling various string property analyses in O(N) time.
#   • Invariants: For any index `i`, `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix.
#   • Tips: The prefix function `pi[i]` stores the length of the longest proper prefix of `s[0...i]` that is also a suffix.; Concatenate pattern, a unique separator, and text (`P + # + T`) to find all pattern occurrences.
#   • Pitfalls: Off-by-one errors with array indexing or the precise definition of the prefix function.; Incorrectly handling the unique separator character in concatenated strings, leading to false matches.
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
#   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
#   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
#   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
#   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
#   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minCharacters(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: int
        """
        countA = [0] * 26
        countB = [0] * 26
        
        for char in a:
            countA[ord(char) - ord('a')] += 1
        for char in b:
            countB[ord(char) - ord('a')] += 1
        
        prefixA = [0] * 26
        prefixB = [0] * 26
        
        prefixA[0] = countA[0]
        prefixB[0] = countB[0]
        
        for i in range(1, 26):
            prefixA[i] = prefixA[i - 1] + countA[i]
            prefixB[i] = prefixB[i - 1] + countB[i]
        
        totalA = len(a)
        totalB = len(b)
        
        min_operations = float('inf')
        
        # Condition 1: Every letter in a is strictly less than every letter in b
        for i in range(25):
            ops = (totalA - prefixA[i]) + prefixB[i]
            min_operations = min(min_operations, ops)
        
        # Condition 2: Every letter in b is strictly less than every letter in a
        for i in range(25):
            ops = (totalB - prefixB[i]) + prefixA[i]
            min_operations = min(min_operations, ops)
        
        # Condition 3: Both a and b consist of only one distinct letter
        for i in range(26):
            ops = (totalA - countA[i]) + (totalB - countB[i])
            min_operations = min(min_operations, ops)
        
        return min_operations