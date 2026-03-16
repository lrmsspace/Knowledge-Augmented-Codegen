# Source: https://leetcode.com/problems/sum-of-matrix-after-queries/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n and a 0-indexed 2D array queries where queries[i] = [typei, indexi, vali].
#
# Initially, there is a 0-indexed n x n matrix filled with 0's. For each query, you must apply one of the following changes:
#
#
# 	if typei == 0, set the values in the row with indexi to vali, overwriting any previous values.
# 	if typei == 1, set the values in the column with indexi to vali, overwriting any previous values.
#
#
# Return the sum of integers in the matrix after all queries are applied.
#
# Example:
# Input: n = 3, queries = [[0,0,1],[1,2,2],[0,2,3],[1,0,4]]
# Output: 23
# Explanation: The image above describes the matrix after each query. The sum of the matrix after all queries are applied is 23.
#
# Constraints:
# 1 <= n <= 104
# 	1 <= queries.length <= 5 * 104
# 	queries[i].length == 3
# 	0 <= typei <= 1
# 	0 <= indexi < n
# 	0 <= vali <= 105
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
#   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
#   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
#   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
#   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
#   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
# - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
#   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
#   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
#   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
#   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
#   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
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
    def matrixSumQueries(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: int
        """
        row_visited = set()
        col_visited = set()
        total_sum = 0
        
        for query in reversed(queries):
            t, idx, val = query
            if t == 0:  # row operation
                if idx not in row_visited:
                    total_sum += (n - len(col_visited)) * val
                    row_visited.add(idx)
            else:  # column operation
                if idx not in col_visited:
                    total_sum += (n - len(row_visited)) * val
                    col_visited.add(idx)
        
        return total_sum