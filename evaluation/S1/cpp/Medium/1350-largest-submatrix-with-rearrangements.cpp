// Source: https://leetcode.com/problems/largest-submatrix-with-rearrangements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
//
// Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.
//
// Example:
// Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m * n <= 105
// 	matrix[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Hungarian algorithm for solving the assignment problem (matrix, graph, array, greedy, bfs, enumeration)
//   • When to use: Use when finding a minimum cost perfect matching in a bipartite graph, typically represented as an N x N cost matrix, where each row must be assigned to exactly one column.
//   • Idea: The Hungarian algorithm finds a minimum weight perfect matching in a bipartite graph, solving the assignment problem for an N x N cost matrix. It iteratively finds augmenting paths in an equality graph and adjusts potentials, achieving O(N^3) time complexity.
//   • Invariants: For all i, j, u[i] + v[j] <= A[i][j] (potential condition).; The current matching is always valid (each row/column used at most once).
//   • Tips: Understand the concept of potentials and their role in maintaining the equality graph.; The algorithm can be adapted for maximum profit problems by negating costs.
//   • Pitfalls: Incorrectly updating potentials can lead to non-optimal solutions or infinite loops.; Handling non-square matrices requires careful padding with dummy values.
// - Fibonacci Numbers (matrix, matrix-exp)
//   • When to use: Use when needing to compute the N-th Fibonacci number or similar linear recurrence relations for very large N efficiently, typically in logarithmic time.
//   • Idea: This method computes the N-th Fibonacci number by transforming the linear recurrence into a matrix multiplication, then using binary exponentiation (matrix exponentiation) to raise the transformation matrix to the N-th power. It achieves O(log N) time complexity.
//   • Invariants: The base matrix M = [[1, 1], [1, 0]] correctly transforms (F_k, F_{k-1}) to (F_{k+1}, F_k).; After k matrix multiplications, the accumulated matrix represents M^k.
//   • Tips: Understand binary exponentiation for matrices to efficiently compute powers.; The base transformation matrix for Fibonacci is typically [[1, 1], [1, 0]].
//   • Pitfalls: Incorrectly setting up the base matrix or initial vector.; Forgetting to apply modulo operations, leading to integer overflow for large numbers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int largestSubmatrix(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        vector<int> heights(n, 0);
        int maxArea = 0;

        for (int i = 0; i < m; ++i) {
            // Update heights
            for (int j = 0; j < n; ++j) {
                if (matrix[i][j] == 1) {
                    heights[j] += 1;
                } else {
                    heights[j] = 0;
                }
            }

            // Copy and sort heights to simulate column rearrangement
            vector<int> sortedHeights = heights;
            sort(sortedHeights.begin(), sortedHeights.end(), greater<int>());

            // Calculate max area for this row
            for (int j = 0; j < n; ++j) {
                int area = sortedHeights[j] * (j + 1);
                if (area > maxArea) {
                    maxArea = area;
                }
            }
        }

        return maxArea;         
    }
};
