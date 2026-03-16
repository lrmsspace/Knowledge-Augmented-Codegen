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
// - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
//   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
//   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
//   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
//   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
//   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
// - Calculating the determinant of a matrix by Gauss (matrix, number, simulation, counting)
//   • When to use: When needing to compute the determinant of a square matrix, especially when Gaussian elimination is a familiar or efficient approach. It is suitable for matrices where direct cofactor expansion is computationally too expensive.
//   • Idea: This algorithm computes the determinant of a square matrix by transforming it into an upper triangular form using Gaussian elimination. The determinant is the product of diagonal elements, adjusted by a sign factor from row swaps, with O(N^3) complexity.
//   • Invariants: Before processing column 'k', all elements A[i][j] where i > j and j < k are zero.; The determinant of the current matrix, multiplied by (-1)^swaps, equals the original matrix's determinant.
//   • Tips: Track the number of row swaps to correctly determine the determinant's sign.; Pivot selection can improve numerical stability, especially with floating-point numbers.
//   • Pitfalls: Forgetting to adjust the sign after row exchanges.; Division by zero if a pivot element is zero, requiring a row swap.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
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
    if (matSize == 0 || matColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int m = matSize;
    int n = matColSize[0];
    int* result = (int*)malloc(m * n * sizeof(int));
    *returnSize = m * n;

    int index = 0;
    for (int d = 0; d < m + n - 1; d++) {
        if (d % 2 == 0) {
            // Traverse from bottom-left to top-right
            for (int i = (d < m ? d : m - 1), j = (d < m ? 0 : d - m + 1); i >= 0 && j < n; i--, j++) {
                result[index++] = mat[i][j];
            }
        } else {
            // Traverse from top-right to bottom-left
            for (int i = (d < n ? 0 : d - n + 1), j = (d < n ? d : n - 1); i < m && j >= 0; i++, j--) {
                result[index++] = mat[i][j];
            }
        }
    }

    return result;      
}
