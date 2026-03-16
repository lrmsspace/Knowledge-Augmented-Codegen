// Source: https://leetcode.com/problems/find-a-good-subset-of-the-matrix/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n binary matrix grid.
//
// Let us call a non-empty subset of rows good if the sum of each column of the subset is at most half of the length of the subset.
//
// More formally, if the length of the chosen subset of rows is k, then the sum of each column should be at most floor(k / 2).
//
// Return an integer array that contains row indices of a good subset sorted in ascending order.
//
// If there are multiple good subsets, you can return any of them. If there are no good subsets, return an empty array.
//
// A subset of rows of the matrix grid is any matrix that can be obtained by deleting some (possibly none or all) rows from grid.
//
// Example:
// Input: grid = [[0,1,1,0],[0,0,0,1],[1,1,1,1]]
// Output: [0,1]
// Explanation: We can choose the 0th and 1st rows to create a good subset of rows.
// The length of the chosen subset is 2.
// - The sum of the 0th column is 0 + 0 = 0, which is at most half of the length of the subset.
// - The sum of the 1st column is 1 + 0 = 1, which is at most half of the length of the subset.
// - The sum of the 2nd column is 1 + 0 = 1, which is at most half of the length of the subset.
// - The sum of the 3rd column is 0 + 1 = 1, which is at most half of the length of the subset.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m <= 104
// 	1 <= n <= 5
// 	grid[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Gauss method for solving system of linea (bitset, matrix, simulation)
//   • When to use: Use when determining the number of solutions (zero, one, or infinite) for a system of linear equations, or to find the unique solution if it exists. It is suitable for solving systems represented as an augmented matrix.
//   • Idea: Gaussian elimination systematically transforms an augmented matrix into row echelon form using elementary row operations to solve a system of linear equations. It determines the existence and values of solutions in O(N^3) time for an N x N system.
//   • Invariants: The submatrix formed by rows 0 to current_row - 1 is in row echelon form.; For the current column, all elements below the pivot in previous columns are zero.
//   • Tips: Use a small epsilon for floating-point comparisons to handle precision issues.; Implement partial pivoting to enhance numerical stability by selecting the largest absolute value.
//   • Pitfalls: Failing to account for floating-point precision errors can lead to incorrect results.; Improper handling of free variables can misrepresent infinite solution sets.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> goodSubsetofBinaryMatrix(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            bool allZero = true;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    allZero = false;
                    break;
                }
            }
            if (allZero) {
                return {i};
            }
        }
        unordered_map<int, int> maskToRow;
        for (int i = 0; i < m; ++i) {
            int mask = 0;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    mask |= (1 << j);
                }
            }
            int complement = ((1 << n) - 1) ^ mask;
            if (maskToRow.find(complement) != maskToRow.end()) {
                return {maskToRow[complement], i};
            }
            maskToRow[mask] = i;
        }
        return {};          
    }
};
