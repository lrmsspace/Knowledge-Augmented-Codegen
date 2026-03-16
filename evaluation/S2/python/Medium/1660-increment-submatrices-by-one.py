# Source: https://leetcode.com/problems/increment-submatrices-by-one/   |   Difficulty: Medium
#
# Problem Description:
# You are given a positive integer n, indicating that we initially have an n x n 0-indexed integer matrix mat filled with zeroes.
#
# You are also given a 2D integer array query. For each query[i] = [row1i, col1i, row2i, col2i], you should do the following operation:
#
#
# 	Add 1 to every element in the submatrix with the top left corner (row1i, col1i) and the bottom right corner (row2i, col2i). That is, add 1 to mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.
#
#
# Return the matrix mat after performing every query.
#
# Example:
# Input: n = 3, queries = [[1,1,2,2],[0,0,1,1]]
# Output: [[1,1,0],[1,2,1],[0,1,1]]
# Explanation: The diagram above shows the initial matrix, the matrix after the first query, and the matrix after the second query.
# - In the first query, we add 1 to every element in the submatrix with the top left corner (1, 1) and bottom right corner (2, 2).
# - In the second query, we add 1 to every element in the submatrix with the top left corner (0, 0) and bottom right corner (1, 1).
#
# Constraints:
# 1 <= n <= 500
# 	1 <= queries.length <= 104
# 	0 <= row1i <= row2i < n
# 	0 <= col1i <= col2i < n
#
# Helpful references (internal KB):
# - Disjoint Sparse Table tutorial (array, ds, sparse-table, prefix-sum)
#   • When to use: Use when you need to perform O(1) range queries on a static array for an associative operation, after an O(N log N) preprocessing step.
#   • Idea: A data structure that precomputes answers for all possible range queries using an associative operation on a static array. It achieves O(1) query time and O(N log N) build time by storing prefix-like sums within logarithmically sized blocks.
#   • Invariants: For each level k, the array is partitioned into 2^k segments.; Within each segment, table[k][j] stores the result of the associative operation from j to the segment's midpoint (or midpoint to j).
#   • Tips: Ensure the operation is associative (e.g., min, max, sum, gcd, bitwise operations).; Preprocessing takes O(N log N) time and space.
#   • Pitfalls: Not suitable for mutable arrays; updates require rebuilding the table.; Requires O(N log N) memory, which can be substantial for very large N.
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
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
    def rangeAddQueries(self, n, queries):
        """
        :type n: int
        :type queries: List[List[int]]
        :rtype: List[List[int]]
        """
        # Initialize the matrix with zeros
        mat = [[0] * n for _ in range(n)]

        # Apply each query using a 2D difference array approach
        for row1, col1, row2, col2 in queries:
            mat[row1][col1] += 1
            if col2 + 1 < n:
                mat[row1][col2 + 1] -= 1
            if row2 + 1 < n:
                mat[row2 + 1][col1] -= 1
            if row2 + 1 < n and col2 + 1 < n:
                mat[row2 + 1][col2 + 1] += 1

        # Compute the prefix sums to get the final values in the matrix
        for i in range(n):
            for j in range(1, n):
                mat[i][j] += mat[i][j - 1]
        for j in range(n):
            for i in range(1, n):
                mat[i][j] += mat[i - 1][j]

        return mat