# Source: https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/   |   Difficulty: Hard
#
# Problem Description:
# A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following conditions is true:
#
#
# 	It is ().
# 	It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
# 	It can be written as (A), where A is a valid parentheses string.
#
#
# You are given an m x n matrix of parentheses grid. A valid parentheses string path in the grid is a path satisfying all of the following conditions:
#
#
# 	The path starts from the upper left cell (0, 0).
# 	The path ends at the bottom-right cell (m - 1, n - 1).
# 	The path only ever moves down or right.
# 	The resulting parentheses string formed by the path is valid.
#
#
# Return true if there exists a valid parentheses string path in the grid. Otherwise, return false.
#
# Example:
# Input: grid = [["(","(","("],[")","(",")"],["(","(",")"],["(","(",")"]]
# Output: true
# Explanation: The above diagram shows two possible paths that form valid parentheses strings.
# The first path shown results in the valid parentheses string "()(())".
# The second path shown results in the valid parentheses string "((()))".
# Note that there may be other valid parentheses string paths.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 100
# 	grid[i][j] is either '(' or ')'.
#
# Helpful references (internal KB):
# - Directed Graphs (graph, matrix, dfs)
#   • When to use: Use when needing to determine reachability between all pairs of vertices in a directed graph, especially for small or dense graphs where O(V*(V+E)) time is acceptable.
#   • Idea: This approach determines all-pairs reachability in a directed graph by performing a Depth-First Search starting from each vertex. It has a time complexity of O(V*(V+E)) and a space complexity of O(V^2).
#   • Invariants: For any vertex u, after its dedicated DFS completes, TC[u][v] is true for all v reachable from u.; The transitive closure matrix TC accurately reflects all-pairs reachability in the original graph.
#   • Tips: Initialize a boolean matrix to store reachability results.; For each vertex, perform a full DFS to mark all nodes reachable from it.
#   • Pitfalls: High time complexity O(V*(V+E)) makes it unsuitable for large sparse graphs.; High space complexity O(V^2) can be prohibitive for graphs with many vertices.
# - Balanced bracket sequences (number, counting)
#   • When to use: When asked to count the total number of valid or well-formed bracket sequences of a certain length or with a specific number of pairs. This often involves combinatorial reasoning or dynamic programming.
#   • Idea: Counts the total number of valid bracket sequences of a given length or with a specific number of pairs, where each opening bracket has a corresponding closing bracket. This problem often has a combinatorial solution, typically involving Catalan numbers, with a time complexity of O(N) or O(N^2) for DP.
#   • Invariants: At any prefix of the sequence, the number of open brackets is greater than or equal to the number of closing brackets.; The total number of open brackets in the sequence equals the total number of closing brackets.
#   • Tips: Recognize the pattern for Catalan numbers if applicable.; Dynamic programming can be used for more complex variations.
#   • Pitfalls: Incorrectly handling the balance constraint (open count >= close count).; Overcounting or undercounting sequences.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def hasValidPath(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: bool
        """
        m, n = len(grid), len(grid[0])
        if (m + n) % 2 == 0:  # Odd length is needed for a valid parentheses string
            return False

        # dp[i][j] will store the set of possible counts of open parentheses at cell (i, j)
        dp = [[set() for _ in range(n)] for _ in range(m)]
        dp[0][0].add(1 if grid[0][0] == '(' else -1)

        for i in range(m):
            for j in range(n):
                if i == 0 and j == 0:
                    continue
                current_char = grid[i][j]
                current_value = 1 if current_char == '(' else -1

                if i > 0:
                    for val in dp[i-1][j]:
                        new_val = val + current_value
                        if new_val >= 0:  # Valid only if open count is non-negative
                            dp[i][j].add(new_val)

                if j > 0:
                    for val in dp[i][j-1]:
                        new_val = val + current_value
                        if new_val >= 0:  # Valid only if open count is non-negative
                            dp[i][j].add(new_val)

        # Check if we can end with exactly 0 open parentheses at the bottom-right cell
        return 0 in dp[m-1][n-1]