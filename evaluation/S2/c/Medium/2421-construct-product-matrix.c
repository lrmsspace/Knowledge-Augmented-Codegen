// Source: https://leetcode.com/problems/construct-product-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given a 0-indexed 2D integer matrix grid of size n * m, we define a 0-indexed 2D matrix p of size n * m as the product matrix of grid if the following condition is met:
//
//
// 	Each element p[i][j] is calculated as the product of all elements in grid except for the element grid[i][j]. This product is then taken modulo 12345.
//
//
// Return the product matrix of grid.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: [[24,12],[8,6]]
// Explanation: p[0][0] = grid[0][1] * grid[1][0] * grid[1][1] = 2 * 3 * 4 = 24
// p[0][1] = grid[0][0] * grid[1][0] * grid[1][1] = 1 * 3 * 4 = 12
// p[1][0] = grid[0][0] * grid[0][1] * grid[1][1] = 1 * 2 * 4 = 8
// p[1][1] = grid[0][0] * grid[0][1] * grid[1][0] = 1 * 2 * 3 = 6
// So the answer is [[24,12],[8,6]].
//
// Constraints:
// 1 <= n == grid.length <= 105
// 	1 <= m == grid[i].length <= 105
// 	2 <= n * m <= 105
// 	1 <= grid[i][j] <= 109
//
// Helpful references (internal KB):
// - N/A
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
int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int n = gridSize;
    int m = gridColSize[0];
    
    // Calculate the total product of all elements in the grid
    long long totalProduct = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            totalProduct = (totalProduct * grid[i][j]) % 12345;
        }
    }
    
    // Allocate memory for the result matrix and column sizes
    int** p = (int**)malloc(n * sizeof(int*));
    *returnColumnSizes = (int*)malloc(n * sizeof(int));
    
    for (int i = 0; i < n; i++) {
        p[i] = (int*)malloc(m * sizeof(int));
        (*returnColumnSizes)[i] = m;
        
        for (int j = 0; j < m; j++) {
            // Calculate the product for p[i][j]
            long long product = totalProduct;
            if (grid[i][j] != 0) {
                product = (product * modInverse(grid[i][j], 12345)) % 12345;
            } else {
                product = 0; // If the element is zero, the product will be zero
            }
            p[i][j] = (int)product;
        }
    }
    
    *returnSize = n;
    return p;       
}
