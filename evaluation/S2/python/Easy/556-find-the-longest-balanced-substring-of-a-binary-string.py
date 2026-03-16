# Source: https://leetcode.com/problems/find-the-longest-balanced-substring-of-a-binary-string/   |   Difficulty: Easy
#
# Problem Description:
# You are given a binary string s consisting only of zeroes and ones.
#
# A substring of s is considered balanced if all zeroes are before ones and the number of zeroes is equal to the number of ones inside the substring. Notice that the empty substring is considered a balanced substring.
#
# Return the length of the longest balanced substring of s.
#
# A substring is a contiguous sequence of characters within a string.
#
# Example:
# Input: s = "01000111"
# Output: 6
# Explanation: The longest balanced substring is "000111", which has length 6.
#
# Constraints:
# 1 <= s.length <= 50
# 	'0' <= s[i] <= '1'
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Prefix function. Knuth–Morris–Pratt algorithm (string, array, kmp, two-pointers)
#   • When to use: When efficiently searching for all occurrences of a pattern string within a larger text string, or when computing the longest proper prefix of a string that is also a suffix for all its prefixes.
#   • Idea: The KMP algorithm efficiently finds all occurrences of a pattern within a text by pre-processing the pattern to build a prefix function (LPS array), which avoids redundant character comparisons. It achieves a time complexity of O(N + M) for text length N and pattern length M.
#   • Invariants: The prefix function array `pi` stores for each `i` the length of the longest proper prefix of `s[0...i]` that is also a suffix of `s[0...i]`.; During prefix function computation for `pi[i]`, `j` always represents the length of the longest proper prefix of `s[0...i-1]` that is also a suffix of `s[0...i-1]`.
#   • Tips: Precompute the prefix function (LPS array) for the pattern to guide shifts.; Use two pointers: one for the text (or current character in pattern for prefix function), one for the pattern (or length of matched prefix).
#   • Pitfalls: Incorrectly calculating or using the prefix function values, leading to wrong shifts.; Off-by-one errors when indexing or shifting pointers, especially at boundaries.
# - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
#   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
#   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
#   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
#   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
#   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findTheLongestBalancedSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """
        max_length = 0
        count_0 = 0
        count_1 = 0

        for char in s:
            if char == '0':
                # If we encounter a '0' after counting some '1's, reset counts
                if count_1 > 0:
                    count_0 = 0
                    count_1 = 0
                count_0 += 1
            else:  # char == '1'
                count_1 += 1
            
            # Update max_length if we have a balanced substring
            if count_0 == count_1:
                max_length = max(max_length, 2 * count_0)

        return max_length