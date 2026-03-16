# Source: https://leetcode.com/problems/right-triangles/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 2D boolean matrix grid.
#
# A collection of 3 elements of grid is a right triangle if one of its elements is in the same row with another element and in the same column with the third element. The 3 elements may not be next to each other.
#
# Return an integer that is the number of right triangles that can be made with 3 elements of grid such that all of them have a value of 1.
#
# Example:
# 0
# 			1
# 			0
# 		
# 		
# 			0
# 			1
# 			1
# 		
# 		
# 			0
# 			1
# 			0
# 		
# 	
#
#
#
# 	
# 		
# 			0
# 			1
# 			0
# 		
# 		
# 			0
# 			1
# 			1
# 		
# 		
# 			0
# 			1
# 			0
# 		
# 	
#
#
#
# 	
# 		
# 			0
# 			1
# 			0
# 		
# 		
# 			0
# 			1
# 			1
# 		
# 		
# 			0
# 			1
# 			0
# 		
# 	
#
#
#
#
# Input: grid = [[0,1,0],[0,1,1],[0,1,0]]
#
# Output: 2
#
# Explanation:
#
# There are two right triangles with elements of the value 1. Notice that the blue ones do not form a right triangle because the 3 elements are in the same column.
#
# Constraints:
# 1 <= grid.length <= 1000
# 	1 <= grid[i].length <= 1000
# 	0 <= grid[i][j] <= 1
#
# Helpful references (internal KB):
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
# - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
#   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
#   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
#   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
#   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
#   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
# - Binomial Coefficients (array, enumeration)
#   • When to use: When you need to calculate the number of ways to choose k items from n distinct items, often under modular constraints.
#   • Idea: Binomial coefficients represent the number of ways to choose k items from a set of n distinct items. They can be computed using Pascal's identity or factorials, with complexity varying based on the method and modulo requirements.
#   • Invariants: For Pascal's triangle, dp[i][j] stores C(i, j).; For factorial method, fact[i] stores i! % M.
#   • Tips: Use Pascal's triangle for small n and k values.; Precompute factorials and inverse factorials for larger n modulo a prime.
#   • Pitfalls: Overflow with large factorials if not using modular arithmetic.; Division by zero when computing inverse modulo if modulus is not prime.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def numberOfRightTriangles(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        MOD = 10**9 + 7
        m, n = len(grid), len(grid[0])
        
        row_count = [0] * m
        col_count = [0] * n
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    row_count[i] += 1
                    col_count[j] += 1
        
        result = 0
        
        for i in range(m):
            for j in range(n):
                if grid[i][j] == 1:
                    result += (row_count[i] - 1) * (col_count[j] - 1)
                    result %= MOD
        
        return result