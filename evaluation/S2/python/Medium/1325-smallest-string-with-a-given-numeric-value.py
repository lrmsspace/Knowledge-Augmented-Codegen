# Source: https://leetcode.com/problems/smallest-string-with-a-given-numeric-value/   |   Difficulty: Medium
#
# Problem Description:
# The numeric value of a lowercase character is defined as its position (1-indexed) in the alphabet, so the numeric value of a is 1, the numeric value of b is 2, the numeric value of c is 3, and so on.
#
# The numeric value of a string consisting of lowercase characters is defined as the sum of its characters' numeric values. For example, the numeric value of the string "abe" is equal to 1 + 2 + 5 = 8.
#
# You are given two integers n and k. Return the lexicographically smallest string with length equal to n and numeric value equal to k.
#
# Note that a string x is lexicographically smaller than string y if x comes before y in dictionary order, that is, either x is a prefix of y, or if i is the first position such that x[i] != y[i], then x[i] comes before y[i] in alphabetic order.
#
# Example:
# Input: n = 3, k = 27
# Output: "aay"
# Explanation: The numeric value of the string is 1 + 1 + 25 = 27, and it is the smallest string with such a value and length equal to 3.
#
# Constraints:
# 1 <= n <= 105
# 	n <= k <= 26 * n
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getSmallestString(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """
        # The idea is to start from the end of the string and fill it with 'z' (which has a numeric value of 26) until we can no longer do so without exceeding k. Then we fill the remaining part of the string with 'a' (which has a numeric value of 1) and adjust the last character to make sure the total numeric value equals k.

        # Initialize an array to hold the characters of the resulting string
        result = ['a'] * n  # Start with all 'a's, which have a numeric value of 1
        k -= n  # We have already accounted for n 'a's

        # Fill the string from the end
        for i in range(n - 1, -1, -1):
            if k > 0:
                add_value = min(k, 25)  # We can add at most 25 to turn 'a' into 'z'
                result[i] = chr(ord('a') + add_value)  # Update the character at position i
                k -= add_value  # Decrease k by the amount we added

        return ''.join(result)