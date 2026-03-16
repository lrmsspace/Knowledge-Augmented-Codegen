// Source: https://leetcode.com/problems/image-smoother/   |   Difficulty: Easy
//
// Problem Description:
// An image smoother is a filter of the size 3 x 3 that can be applied to each cell of an image by rounding down the average of the cell and the eight surrounding cells (i.e., the average of the nine cells in the blue smoother). If one or more of the surrounding cells of a cell is not present, we do not consider it in the average (i.e., the average of the four cells in the red smoother).
//
// Given an m x n integer matrix img representing the grayscale of an image, return the image after applying the smoother on each cell of it.
//
// Example:
// Input: img = [[1,1,1],[1,0,1],[1,1,1]]
// Output: [[0,0,0],[0,0,0],[0,0,0]]
// Explanation:
// For the points (0,0), (0,2), (2,0), (2,2): floor(3/4) = floor(0.75) = 0
// For the points (0,1), (1,0), (1,2), (2,1): floor(5/6) = floor(0.83333333) = 0
// For the point (1,1): floor(8/9) = floor(0.88888889) = 0
//
// Constraints:
// m == img.length
// 	n == img[i].length
// 	1 <= m, n <= 200
// 	0 <= img[i][j] <= 255
//
// Helpful references (internal KB):
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - Integration by Simpson's formula (number, interval, enumeration, simulation)
//   • When to use: Use when approximating definite integrals of functions that are sufficiently smooth over a given interval. It is effective for achieving good accuracy with a moderate number of subintervals.
//   • Idea: Simpson's formula approximates a definite integral by dividing the integration interval into an even number of subintervals and approximating the function over each pair of subintervals with a parabola. This method offers a higher order of accuracy compared to simpler rules, typically achieving O(N^4) accuracy for N subintervals.
//   • Invariants: The sum accumulates weighted function values for all processed subintervals.; The subinterval width 'h' remains constant across the entire integration range.
//   • Tips: Ensure the total number of subintervals (2n) is always even for the composite rule.; The weights for function evaluations follow a specific 1-4-2-4-...-2-4-1 pattern.
//   • Pitfalls: Incorrectly applying the weighting coefficients, especially at the boundaries or interior points.; Using an odd number of subintervals, which invalidates the parabolic approximation for the composite rule.
// - Gauss method for solving system of linea (matrix, number, simulation)
//   • When to use: Use when solving systems of linear equations, including those over finite fields (modulo p), to find unique, multiple, or no solutions.
//   • Idea: Gauss-Jordan elimination systematically transforms a system of linear equations into an equivalent, simpler form (row echelon or reduced row echelon) using elementary row operations to find solutions. This process typically has a time complexity of O(N^2 * M) for an N x M matrix.
//   • Invariants: After k steps, the first k columns form an identity submatrix (or a column with 1 at pivot and 0s elsewhere) in the upper-left kxk block.; The system of equations represented by the augmented matrix remains equivalent to the original system.
//   • Tips: Always perform row operations on the augmented matrix (A|b) to ensure consistency.; Choose a pivot with the largest absolute value to improve numerical stability and reduce error propagation.
//   • Pitfalls: Division by zero if a pivot element is zero and no suitable row swap is found.; Numerical instability with floating-point numbers if pivots are very small, leading to precision issues.
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
int** imageSmoother(int** img, int imgSize, int* imgColSize, int* returnSize, int** returnColumnSizes) {
    int** result = (int**)malloc(imgSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(imgSize * sizeof(int));
    for (int i = 0; i < imgSize; i++) {
        result[i] = (int*)malloc(imgColSize[i] * sizeof(int));
        (*returnColumnSizes)[i] = imgColSize[i];
    }

    for (int i = 0; i < imgSize; i++) {
        for (int j = 0; j < imgColSize[i]; j++) {
            int sum = 0, count = 0;
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    int ni = i + x, nj = j + y;
                    if (ni >= 0 && ni < imgSize && nj >= 0 && nj < imgColSize[i]) {
                        sum += img[ni][nj];
                        count++;
                    }
                }
            }
            result[i][j] = sum / count;
        }
    }

    *returnSize = imgSize;
    return result;      
}
