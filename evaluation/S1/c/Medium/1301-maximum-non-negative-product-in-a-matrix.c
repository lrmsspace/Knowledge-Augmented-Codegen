// Source: https://leetcode.com/problems/maximum-non-negative-product-in-a-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given a m x n matrix grid. Initially, you are located at the top-left corner (0, 0), and in each step, you can only move right or down in the matrix.
//
// Among all possible paths starting from the top-left corner (0, 0) and ending in the bottom-right corner (m - 1, n - 1), find the path with the maximum non-negative product. The product of a path is the product of all integers in the grid cells visited along the path.
//
// Return the maximum non-negative product modulo 109 + 7. If the maximum product is negative, return -1.
//
// Notice that the modulo is performed after getting the maximum product.
//
// Example:
// Input: grid = [[-1,-2,-3],[-2,-3,-3],[-3,-3,-2]]
// Output: -1
// Explanation: It is not possible to get non-negative product in the path from (0, 0) to (2, 2), so return -1.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	-4 <= grid[i][j] <= 4
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Floyd-Warshall Algorithm (graph, matrix, floyd-warshall, dp-2d)
//   • When to use: Use when needing to find the shortest paths between all pairs of vertices in a weighted graph, especially if negative edge weights are present but no negative cycles.
//   • Idea: The Floyd-Warshall algorithm is a dynamic programming approach that finds the shortest paths between all pairs of vertices in a weighted graph. It iteratively considers all possible intermediate vertices to update path lengths, achieving an O(N^3) time complexity.
//   • Invariants: After k iterations, d[i][j] stores the shortest path from i to j using only vertices {1, ..., k} as intermediate nodes.; d[i][j] always represents a valid path length or infinity, never an invalid negative value unless a negative cycle is detected.
//   • Tips: Initialize direct edge weights and infinity for non-existent edges.; Set distance from a vertex to itself to zero initially.
//   • Pitfalls: Incorrect loop order (k must be outermost) will yield incorrect results.; Improper handling of 'infinity' values can lead to overflow or incorrect comparisons.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxProductPath(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = gridColSize[0];
    long long mod = 1000000007;

    long long max_dp[m][n];
    long long min_dp[m][n];

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0) {
                max_dp[i][j] = grid[i][j];
                min_dp[i][j] = grid[i][j];
            } else if (i == 0) {
                max_dp[i][j] = max_dp[i][j - 1] * grid[i][j];
                min_dp[i][j] = max_dp[i][j];
            } else if (j == 0) {
                max_dp[i][j] = max_dp[i - 1][j] * grid[i][j];
                min_dp[i][j] = max_dp[i][j];
            } else {
                long long a = max_dp[i - 1][j] * grid[i][j];
                long long b = max_dp[i][j - 1] * grid[i][j];
                long long c = min_dp[i - 1][j] * grid[i][j];
                long long d = min_dp[i][j - 1] * grid[i][j];

                max_dp[i][j] = fmax(fmax(a, b), fmax(c, d));
                min_dp[i][j] = fmin(fmin(a, b), fmin(c, d));
            }
        }
    }

    if (max_dp[m - 1][n - 1] < 0) {
        return -1;
    } else {
        return (int)(max_dp[m - 1][n - 1] % mod);
    }       
}
