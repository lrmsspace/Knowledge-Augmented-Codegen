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
# - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
#   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
#   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
#   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
#   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
#   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
# - Finding the largest zero submatrix (matrix, array, dp-2d)
#   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
#   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
#   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
#   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
#   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
# - Finding area of simple polygon in O(N) (geometry, array, enumeration, prefix-sum)
#   • When to use: Use when calculating the area of a simple polygon given its vertices in order. It is efficient for both convex and non-convex polygons.
#   • Idea: This algorithm calculates the area of a simple polygon by summing signed trapezoidal areas formed by each edge and the x-axis, or equivalently, using the shoelace formula. It achieves an optimal O(N) time complexity, where N is the number of vertices.
#   • Invariants: Vertices are processed sequentially in their given order, forming edges.; The running sum `current_sum` accumulates the signed contribution from each edge processed so far.
#   • Tips: Ensure vertices are provided in a consistent order (clockwise or counter-clockwise).; Use a data type with sufficient range (e.g., long long or double) for intermediate sums to prevent overflow.
#   • Pitfalls: Incorrect vertex order will result in an incorrect signed area or even zero.; Integer overflow can occur if coordinates are large and sums exceed standard integer limits.
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
        row_values = [0] * n
        col_values = [0] * n
        row_updated = [False] * n
        col_updated = [False] * n
        total_sum = 0

        for query in reversed(queries):
            t, idx, val = query
            if t == 0:  # Row update
                if not row_updated[idx]:
                    total_sum += val * (n - sum(col_updated))
                    row_updated[idx] = True
            else:  # Column update
                if not col_updated[idx]:
                    total_sum += val * (n - sum(row_updated))
                    col_updated[idx] = True

        return total_sum