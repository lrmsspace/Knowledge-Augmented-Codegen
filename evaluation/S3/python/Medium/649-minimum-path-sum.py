# Source: https://leetcode.com/problems/minimum-path-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
#
# Note: You can only move either down or right at any point in time.
#
# Example:
# Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
# Output: 7
# Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
#
# Constraints:
# m == grid.length
# 	n == grid[i].length
# 	1 <= m, n <= 200
# 	0 <= grid[i][j] <= 200
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# - Floyd-Warshall Algorithm (number, simulation)
#   • When to use: When you need to find the shortest paths between all possible pairs of vertices in a graph. It is particularly suitable for dense graphs or when negative edge weights are present, as long as no negative cycles are reachable.
#   • Idea: Floyd-Warshall is a dynamic programming algorithm that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path distances, achieving an O(V^3) time complexity.
#   • Invariants: After the k-th iteration, dist[i][j] contains the shortest path from i to j considering only vertices 0 to k-1 as intermediate nodes.; For any pair (i, j), dist[i][j] is always greater than or equal to the true shortest path distance from i to j (or infinity if unreachable).
#   • Tips: Initialize distances: direct edge weights, infinity for no direct edge, zero for self-loops.; The outermost loop must iterate through intermediate vertices (k).
#   • Pitfalls: Incorrect loop order (k not outermost) leads to incorrect results.; Integer overflow with large path sums if not using appropriate data types.
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
    def minPathSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """
        if not grid or not grid[0]:
            return 0
        
        m, n = len(grid), len(grid[0])
        
        # Create a dp array to store the minimum path sum to each cell
        dp = [[0] * n for _ in range(m)]
        
        # Initialize the top-left corner
        dp[0][0] = grid[0][0]
        
        # Fill the first row
        for j in range(1, n):
            dp[0][j] = dp[0][j-1] + grid[0][j]
        
        # Fill the first column
        for i in range(1, m):
            dp[i][0] = dp[i-1][0] + grid[i][0]
        
        # Fill the rest of the dp array
        for i in range(1, m):
            for j in range(1, n):
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
        
        return dp[m-1][n-1]