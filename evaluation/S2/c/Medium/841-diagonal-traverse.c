// Source: https://leetcode.com/problems/diagonal-traverse/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,4,7,5,3,6,8,9]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	-105 <= mat[i][j] <= 105
//
// Helpful references (internal KB):
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
//   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
//   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
//   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
//   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
//   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
// - Search the subarray with the maximum/minimum sum (matrix, array, dp-2d)
//   • When to use: Use this when you need to find a submatrix within a 2D array that yields the maximum or minimum possible sum of its elements. It's applicable when the problem can be reduced to multiple 1D maximum/minimum subarray sum problems.
//   • Idea: This technique extends the 1D maximum/minimum subarray sum problem to two dimensions. It typically involves iterating over all possible pairs of row (or column) boundaries, reducing the problem to a 1D array, and then applying a 1D dynamic programming approach like Kadane's algorithm, resulting in an O(N^3) time complexity for an N x N matrix.
//   • Invariants: For any fixed pair of top and bottom row indices (r1, r2), the temporary 1D array correctly represents the sum of elements in columns between r1 and r2.; Kadane's algorithm, when applied to the temporary 1D array, correctly finds the maximum/minimum subarray sum for that specific row range.
//   • Tips: Precompute prefix sums for rows to efficiently calculate column sums between fixed row boundaries.; The 2D problem can be reduced to multiple 1D problems by fixing two row indices and creating a temporary 1D array of column sums.
//   • Pitfalls: Incorrectly handling negative numbers when searching for maximum sum; Kadane's algorithm correctly handles this, but custom logic might fail.; Off-by-one errors when defining submatrix boundaries or calculating sums for the 1D reduction.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findDiagonalOrder(int** mat, int matSize, int* matColSize, int* returnSize) {
    int m = matSize, n = matColSize[0];
    int* result = (int*)malloc(m * n * sizeof(int));
    int idx = 0;

    for (int d = 0; d < m + n - 1; d++) {
        if (d % 2 == 0) {
            // Traverse upwards
            for (int i = d < n ? 0 : d - n + 1, j = d < n ? d : n - 1; i < m && j >= 0; i++, j--) {
                result[idx++] = mat[i][j];
            }
        } else {
            // Traverse downwards
            for (int i = d < m ? d : m - 1, j = d < m ? 0 : d - m + 1; i >= 0 && j < n; i--, j++) {
                result[idx++] = mat[i][j];
            }
        }
    }

    *returnSize = m * n;
    return result;      
}
