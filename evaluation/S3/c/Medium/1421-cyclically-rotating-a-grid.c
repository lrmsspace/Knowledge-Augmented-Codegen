// Source: https://leetcode.com/problems/cyclically-rotating-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
//
// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
//
//
//
// A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:
//
// Return the matrix after applying k cyclic rotations to it.
//
// Example:
// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 50
// 	Both m and n are even integers.
// 	1 <= grid[i][j] <= 5000
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
//   • When to use: Use this method to compute the determinant of a square matrix efficiently by decomposing it into lower and upper triangular matrices. It is suitable for problems requiring O(N^3) complexity for matrix operations.
//   • Idea: The Kraut method computes the determinant of a square matrix by first decomposing it into a lower triangular matrix (L) and an upper triangular matrix (U), such that A = LU. The determinant is then the product of the diagonal elements of L and U, achieving O(N^3) time complexity.
//   • Invariants: After processing column k, the first k columns of L and first k rows of U are correctly computed.; For any i <= k and j <= k, the partial sum for A[i][j] from L and U elements up to index min(i,j) is maintained.
//   • Tips: Ensure the input matrix is square for determinant calculation.; The determinant of a triangular matrix is the product of its diagonal elements.
//   • Pitfalls: Division by zero can occur if a pivot element is zero, requiring pivoting strategies.; Floating-point precision issues can accumulate, especially for large matrices.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
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

int** rotateGrid(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes){
    int m = gridSize;
    int n = gridColSize[0];
    int layers = (m < n ? m : n) / 2;
    
    // Allocate memory for the result
    int** result = (int**)malloc(m * sizeof(int*));
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    
    for (int i = 0; i < m; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
        (*returnColumnSizes)[i] = n;
        for (int j = 0; j < n; j++) {
            result[i][j] = grid[i][j]; // Initialize result with original grid
        }
    }
    
    // Rotate each layer
    for (int layer = 0; layer < layers; layer++) {
        int top = layer, left = layer, bottom = m - 1 - layer, right = n - 1 - layer;
        int perimeter = 2 * (bottom - top + right - left);
        int rotations = k % perimeter; // Effective rotations needed
        
        for (int r = 0; r < rotations; r++) {
            int temp = result[top][left]; // Store the first element of the layer
            
            // Move left column up
            for (int i = top; i < bottom; i++) {
                result[i][left] = result[i + 1][left];
            }
            // Move bottom row left
            for (int j = left; j < right; j++) {
                result[bottom][j] = result[bottom][j + 1];
            }
            // Move right column down
            for (int i = bottom; i > top; i--) {
                result[i][right] = result[i - 1][right];
            }
            // Move top row right
            for (int j = right; j > left + 1; j--) {
                result[top][j] = result[top][j - 1];
            }
            result[top][left + 1] = temp; // Place the stored element in its new position
        }
    }
    *returnSize = m;
    return result;
}
