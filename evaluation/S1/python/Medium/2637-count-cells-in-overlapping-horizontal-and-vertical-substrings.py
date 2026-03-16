# Source: https://leetcode.com/problems/count-cells-in-overlapping-horizontal-and-vertical-substrings/   |   Difficulty: Medium
#
# Problem Description:
# You are given an m x n matrix grid consisting of characters and a string pattern.
#
# A horizontal substring is a contiguous sequence of characters read from left to right. If the end of a row is reached before the substring is complete, it wraps to the first column of the next row and continues as needed. You do not wrap from the bottom row back to the top.
#
# A vertical substring is a contiguous sequence of characters read from top to bottom. If the bottom of a column is reached before the substring is complete, it wraps to the first row of the next column and continues as needed. You do not wrap from the last column back to the first.
#
# Count the number of cells in the matrix that satisfy the following condition:
#
#
# 	The cell must be part of at least one horizontal substring and at least one vertical substring, where both substrings are equal to the given pattern.
#
#
# Return the count of these cells.
#
# Example:
# Input: grid = [["a","a","c","c"],["b","b","b","c"],["a","a","b","a"],["c","a","a","c"],["a","a","b","a"]], pattern = "abaca"
#
# Output: 1
#
# Explanation:
#
# The pattern "abaca" appears once as a horizontal substring (colored blue) and once as a vertical substring (colored red), intersecting at one cell (colored purple).
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 1000
# 	1 <= m * n <= 105
# 	1 <= pattern.length <= m * n
# 	grid and pattern consist of only lowercase English letters.
#
# Helpful references (internal KB):
# - Substring Search (string, array, two-pointers, simulation)
#   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
#   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
#   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
#   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
#   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - The Inclusion-Exclusion Principle (string, counting)
#   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
#   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
#   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
#   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
#   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def countCells(self, grid, pattern):
        """
        :type grid: List[List[str]]
        :type pattern: str
        :rtype: int
        """
        m, n = len(grid), len(grid[0])
        p_len = len(pattern)

        def kmp_search(s):
            # Build KMP "next" array
            next_arr = [0] * p_len
            j = 0
            for i in range(1, p_len):
                while j > 0 and pattern[i] != pattern[j]:
                    j = next_arr[j - 1]
                if pattern[i] == pattern[j]:
                    j += 1
                next_arr[i] = j

            # Search for pattern in s
            j = 0
            positions = set()
            for i in range(len(s)):
                while j > 0 and s[i] != pattern[j]:
                    j = next_arr[j - 1]
                if s[i] == pattern[j]:
                    j += 1
                if j == p_len:
                    positions.add(i - p_len + 1)
                    j = next_arr[j - 1]
            return positions

        horizontal_hits = set()
        for i in range(m):
            row_str = ''.join(grid[i])
            hits = kmp_search(row_str + row_str[:p_len - 1])
            for start in hits:
                for k in range(p_len):
                    horizontal_hits.add((i, (start + k) % n))

        vertical_hits = set()
        for j in range(n):
            col_str = ''.join(grid[i][j] for i in range(m))
            hits = kmp_search(col_str + col_str[:p_len - 1])
            for start in hits:
                for k in range(p_len):
                    vertical_hits.add(((start + k) % m, j))

        return len(horizontal_hits & vertical_hits)