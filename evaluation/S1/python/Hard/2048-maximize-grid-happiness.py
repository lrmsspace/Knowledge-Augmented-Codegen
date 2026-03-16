# Source: https://leetcode.com/problems/maximize-grid-happiness/   |   Difficulty: Hard
#
# Problem Description:
# You are given four integers, m, n, introvertsCount, and extrovertsCount. You have an m x n grid, and there are two types of people: introverts and extroverts. There are introvertsCount introverts and extrovertsCount extroverts.
#
# You should decide how many people you want to live in the grid and assign each of them one grid cell. Note that you do not have to have all the people living in the grid.
#
# The happiness of each person is calculated as follows:
#
#
# 	Introverts start with 120 happiness and lose 30 happiness for each neighbor (introvert or extrovert).
# 	Extroverts start with 40 happiness and gain 20 happiness for each neighbor (introvert or extrovert).
#
#
# Neighbors live in the directly adjacent cells north, east, south, and west of a person's cell.
#
# The grid happiness is the sum of each person's happiness. Return the maximum possible grid happiness.
#
# Example:
# Input: m = 2, n = 3, introvertsCount = 1, extrovertsCount = 2
# Output: 240
# Explanation: Assume the grid is 1-indexed with coordinates (row, column).
# We can put the introvert in cell (1,1) and put the extroverts in cells (1,3) and (2,3).
# - Introvert at (1,1) happiness: 120 (starting happiness) - (0 * 30) (0 neighbors) = 120
# - Extrovert at (1,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
# - Extrovert at (2,3) happiness: 40 (starting happiness) + (1 * 20) (1 neighbor) = 60
# The grid happiness is 120 + 60 + 60 = 240.
# The above figure shows the grid in this example with each person's happiness. The introvert stays in the light green cell while the extroverts live on the light purple cells.
#
# Constraints:
# 1 <= m, n <= 5
# 	0 <= introvertsCount, extrovertsCount <= min(m * n, 6)
#
# Helpful references (internal KB):
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
#   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
#   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
#   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
#   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
#   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def getMaxGridHappiness(self, m, n, introvertsCount, extrovertsCount):
        """
        :type m: int
        :type n: int
        :type introvertsCount: int
        :type extrovertsCount: int
        :rtype: int
        """
        # 1. 状态定义：dp[row][mask][introverts_left][extroverts_left] 表示在第 row 行，当前行的状态为 mask（0: 空格, 1: 内向, 2: 外向），剩余 introverts_left 个内向者和 extroverts_left 个外向者时的最大幸福值。
        # 2. 转移方程：对于每个可能的 mask，计算当前行的幸福值，并根据上一行的状态更新 dp[row][mask][introverts_left][extroverts_left]。
        # 3. 边界条件：dp[0][0][introvertsCount][extrovertsCount] = 0，表示初始状态。
        # 4. 最终答案：max(dp[m-1][mask][0][0])，其中 mask 遍历所有可能的状态。
        
        from functools import lru_cache
        
        @lru_cache(None)
        def get_happiness(mask):
            happiness = 0
            for i in range(n):
                if mask[i] == 1:  # introvert
                    happiness += 120
                elif mask[i] == 2:  # extrovert
                    happiness += 40
            for i in range(n - 1):
                if mask[i] != 0 and mask[i + 1] != 0:
                    if mask[i] == 1:
                        happiness -= 30
                    else:
                        happiness += 20
                    if mask[i + 1] == 1:
                        happiness -= 30
                    else:
                        happiness += 20
            return happiness
        
        @lru_cache(None)
        def dfs(row, prev_mask, introverts_left, extroverts_left):
            if row == m:
                return 0
            
            max_happiness = float('-inf')
            for mask in range(3 ** n):
                current_mask = []
                temp = mask
                for _ in range(n):
                    current_mask.append(temp % 3)
                    temp //= 3
                
                introverts_used = sum(1 for x in current_mask if x == 1)
                extroverts_used = sum(1 for x in current_mask if x == 2)
                
                if introverts_used > introverts_left or extroverts_used > extroverts_left:
                    continue
                current_happiness = get_happiness(tuple(current_mask))  
                for i in range(n):
                    if current_mask[i] != 0 and prev_mask[i] != 0:
                        if current_mask[i] == 1:
                            current_happiness -= 30
                        else:
                            current_happiness += 20
                        if prev_mask[i] == 1:
                            current_happiness -= 30
                        else:
                            current_happiness += 20
                total_happiness = current_happiness + dfs(row + 1, tuple(current_mask), introverts_left - introverts_used, extroverts_left - extroverts_used)
                max_happiness = max(max_happiness, total_happiness)
            return max_happiness
        return dfs(0, tuple([0] * n), introvertsCount, extrovertsCount) 