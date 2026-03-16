# Source: https://leetcode.com/problems/minimum-falling-path-sum/   |   Difficulty: Medium
#
# Problem Description:
# Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
#
# A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
#
# Example:
# Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
# Output: 13
# Explanation: There are two falling paths with a minimum sum as shown.
#
# Constraints:
# n == matrix.length == matrix[i].length
# 	1 <= n <= 100
# 	-100 <= matrix[i][j] <= 100
#
# Helpful references (internal KB):
# - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
#   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
#   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
#   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
#   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
#   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
# - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
#   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
#   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
#   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
#   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
#   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
# - Floyd-Warshall Algorithm (matrix, graph, recursion, dp-2d)
#   • When to use: Use when you need to find the shortest paths between all pairs of vertices in a weighted graph. It is suitable for graphs with negative edge weights but no negative cycles.
#   • Idea: The Floyd-Warshall algorithm finds all-pairs shortest paths in a weighted graph using dynamic programming. It iteratively considers all possible intermediate vertices, updating path lengths in O(V^3) time.
#   • Invariants: After k iterations, dist[i][j] contains the shortest path from i to j using only vertices 0 to k-1 as intermediate nodes.; dist[i][j] is always non-increasing with each iteration of k.
#   • Tips: Initialize distances with edge weights or infinity, and 0 for self-loops.; The outermost loop iterates through intermediate vertices (k).
#   • Pitfalls: Incorrectly handling infinity values, especially with negative weights (e.g., infinity - 1).; Not checking for negative cycles, which can lead to incorrect shortest path values.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def minFallingPathSum(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: int
        """
        n = len(matrix)
        dp = [[0] * n for _ in range(n)]
        
        # Initialize the first row of dp with the first row of the matrix
        for j in range(n):
            dp[0][j] = matrix[0][j]
        
        # Fill the dp table
        for i in range(1, n):
            for j in range(n):
                # Get the values from the previous row (directly above, diagonally left, diagonally right)
                up = dp[i-1][j]
                left_diag = dp[i-1][j-1] if j > 0 else float('inf')
                right_diag = dp[i-1][j+1] if j < n - 1 else float('inf')
                
                # Calculate the minimum path sum to reach (i, j)
                dp[i][j] = matrix[i][j] + min(up, left_diag, right_diag)
        
        # The answer is the minimum value in the last row of dp
        return min(dp[-1])