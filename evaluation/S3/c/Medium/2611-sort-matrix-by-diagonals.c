// Source: https://leetcode.com/problems/sort-matrix-by-diagonals/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n square matrix of integers grid. Return the matrix such that:
//
//
// 	The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
// 	The diagonals in the top-right triangle are sorted in non-decreasing order.
//
// Example:
// Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
//
// Output: [[8,2,3],[9,6,7],[4,5,1]]
//
// Explanation:
//
//
//
// The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
//
//
// 	[1, 8, 6] becomes [8, 6, 1].
// 	[9, 5] and [4] remain unchanged.
//
//
// The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
//
//
// 	[7, 2] becomes [2, 7].
// 	[3] remains unchanged.
//
// Constraints:
// grid.length == grid[i].length == n
// 	1 <= n <= 10
// 	-105 <= grid[i][j] <= 105
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
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
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** sortMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int** result = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
    }

    // Sort diagonals in the bottom-left triangle
    for (int d = 0; d < n; d++) {
        int* diagonal = (int*)malloc((n - d) * sizeof(int));
        int idx = 0;
        for (int i = d, j = 0; i < n && j < n; i++, j++) {
            diagonal[idx++] = grid[i][j];
        }
        qsort(diagonal, idx, sizeof(int), (int(*)(const void*, const void*))cmp_desc);
        idx = 0;
        for (int i = d, j = 0; i < n && j < n; i++, j++) {
            result[i][j] = diagonal[idx++];
        }
        free(diagonal);
    }

    // Sort diagonals in the top-right triangle
    for (int d = 1; d < n; d++) {
        int* diagonal = (int*)malloc((n - d) * sizeof(int));
        int idx = 0;
        for (int i = 0, j = d; i < n && j < n; i++, j++) {
            diagonal[idx++] = grid[i][j];
        }
        qsort(diagonal, idx, sizeof(int), (int(*)(const void*, const void*))cmp_asc);
        idx = 0;
        for (int i = 0, j = d; i < n && j < n; i++, j++) {
            result[i][j] = diagonal[idx++];
        }
        free(diagonal);
    }

    *returnSize = n;
    return result;      
}
