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
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Digit DP (array, number, digit-dp, recursion)
#   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
#   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
#   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
#   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
#   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
# - Digit DP (array, number, digit-dp)
#   • When to use: When counting numbers within a given range [A, B] that satisfy certain digit-based properties, or calculating a sum of such properties.
#   • Idea: Digit DP is a dynamic programming technique used to count numbers or calculate sums of properties for numbers within a given range, based on their digits. It typically involves a recursive function with memoization, processing digits from most significant to least significant, achieving a time complexity of O(log(N) * S * T) where S is sum/state range and T is tight constraint.
#   • Invariants: The `idx` parameter always represents the current digit position being processed, from most significant to least significant.; The `tight` boolean parameter accurately indicates if the current digit choice is restricted by the original number's corresponding digit.
#   • Tips: Handle leading zeros carefully, often with a dedicated boolean state in the DP function.; Use a 'tight' or 'limit' boolean parameter to manage the upper bound constraint imposed by the original number.
#   • Pitfalls: Incorrectly handling the 'tight' constraint can lead to overcounting or undercounting.; Forgetting to reset the memoization table for each new query or test case, especially in competitive programming.
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
        n, m = len(word1), len(word2)
        if m >= n:
            return []

        # Precompute the positions of each character in word1
        char_positions = {}
        for i, ch in enumerate(word1):
            if ch not in char_positions:
                char_positions[ch] = []
            char_positions[ch].append(i)

        # Try to find the lexicographically smallest valid sequence
        result = []
        for i, ch in enumerate(word2):
            if ch in char_positions:
                result.append(char_positions[ch][0])  # Take the first occurrence
            else:
                # If the character is not found, we can change one character in word1
                # We will try to replace the first character in the result with this character
                if result:
                    result[0] = 0  # Change the first character to match word2[0]
                    break
                else:
                    return []  # No valid sequence if we can't even match the first character

        return sorted(result)           