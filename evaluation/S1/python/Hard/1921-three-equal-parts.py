# Source: https://leetcode.com/problems/three-equal-parts/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array arr which consists of only zeros and ones, divide the array into three non-empty parts such that all of these parts represent the same binary value.
#
# If it is possible, return any [i, j] with i + 1 < j, such that:
#
#
# 	arr[0], arr[1], ..., arr[i] is the first part,
# 	arr[i + 1], arr[i + 2], ..., arr[j - 1] is the second part, and
# 	arr[j], arr[j + 1], ..., arr[arr.length - 1] is the third part.
# 	All three parts have equal binary values.
#
#
# If it is not possible, return [-1, -1].
#
# Note that the entire part is used when considering what binary value it represents. For example, [1,1,0] represents 6 in decimal, not 3. Also, leading zeros are allowed, so [0,1,1] and [1,1] represent the same value.
#
# Example:
# Input: arr = [1,0,1,0,1]
# Output: [0,3]
#
# Constraints:
# 3 <= arr.length <= 3 * 104
# 	arr[i] is 0 or 1
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - palindrome-partitioning (string, two-pointers, simulation)
#   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
#   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
#   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
#   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
#   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
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
    def threeEqualParts(self, arr):
        """
        :type arr: List[int]
        :rtype: List[int]
        """
        total_ones = sum(arr)
        if total_ones == 0:
            return [0, len(arr) - 1]
        if total_ones % 3 != 0:
            return [-1, -1]

        ones_per_part = total_ones // 3
        first = second = third = -1
        count = 0

        for i in range(len(arr)):
            if arr[i] == 1:
                count += 1
                if count == 1:
                    first = i
                elif count == ones_per_part + 1:
                    second = i
                elif count == 2 * ones_per_part + 1:
                    third = i

        part_length = len(arr) - third
        if first + part_length <= second and second + part_length <= third:
            return [first + part_length - 1, second + part_length]
        else:
            return [-1, -1]