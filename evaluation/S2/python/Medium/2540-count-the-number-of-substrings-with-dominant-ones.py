# Source: https://leetcode.com/problems/count-the-number-of-substrings-with-dominant-ones/   |   Difficulty: Medium
#
# Problem Description:
# You are given a binary string s.
#
# Return the number of substrings with dominant ones.
#
# A string has dominant ones if the number of ones in the string is greater than or equal to the square of the number of zeros in the string.
#
# Example:
# Input: s = "00011"
#
# Output: 5
#
# Explanation:
#
# The substrings with dominant ones are shown in the table below.
#
#
#
# 	
# 		
# 			i
# 			j
# 			s[i..j]
# 			Number of Zeros
# 			Number of Ones
# 		
# 	
# 	
# 		
# 			3
# 			3
# 			1
# 			0
# 			1
# 		
# 		
# 			4
# 			4
# 			1
# 			0
# 			1
# 		
# 		
# 			2
# 			3
# 			01
# 			1
# 			1
# 		
# 		
# 			3
# 			4
# 			11
# 			0
# 			2
# 		
# 		
# 			2
# 			4
# 			011
# 			1
# 			2
#
# Constraints:
# 1 <= s.length <= 4 * 104
# 	s consists only of characters '0' and '1'.
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Z-function and its calculation (string, array, counting)
#   • When to use: Use when you need to find all occurrences of a pattern within a text, or to identify repeated prefixes within a string efficiently.
#   • Idea: The Z-function computes an array where each element z[i] is the length of the longest common prefix between the string and its suffix starting at index i. It runs in linear time, O(N), where N is the length of the string.
#   • Invariants: For all j < i, z[j] correctly stores the length of the longest common prefix between S and S[j...].; The segment [l, r-1] represents the rightmost segment that is a prefix of S and has been fully processed.
#   • Tips: Initialize z[0] to 0 (or N, depending on definition) and handle it as a base case.; Utilize previously computed Z-values to avoid redundant comparisons, especially within the 'rightmost matching segment' [l, r].
#   • Pitfalls: Incorrectly updating or using the 'rightmost matching segment' boundaries (l and r).; Off-by-one errors when calculating indices or lengths, especially with 0-based vs. 1-based indexing.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfSubstrings(self, s):
        """
        :type s: str
        :rtype: int
        """
        count = 0
        n = len(s)

        for i in range(n):
            zeros = 0
            ones = 0

            for j in range(i, n):
                if s[j] == '0':
                    zeros += 1
                else:
                    ones += 1

                if ones >= zeros * zeros:
                    count += 1

        return count