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

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** constructProductMatrix(int** grid, int gridSize, int* gridColSize, int* returnSize, int** returnColumnSizes) {
    int mod = 12345;
    long long total_product = 1;
    int zero_count = 0;
    int zero_row = -1, zero_col = -1;

    // First pass: calculate the total product and count zeros
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 0) {
                zero_count++;
                zero_row = i;
                zero_col = j;
            } else {
                total_product = (total_product * (grid[i][j] % mod)) % mod;
            }
        }
    }

    // Allocate result matrix
    int** result = (int**)malloc(gridSize * sizeof(int*));
    *returnColumnSizes = (int*)malloc(gridSize * sizeof(int));
    for (int i = 0; i < gridSize; i++) {
        result[i] = (int*)malloc(gridColSize[i] * sizeof(int));
        (*returnColumnSizes)[i] = gridColSize[i];
    }
    *returnSize = gridSize;

    // Second pass: fill the result matrix based on zero count
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (zero_count > 1) {
                result[i][j] = 0;
            } else if (zero_count == 1) {
                if (i == zero_row && j == zero_col) {
                    result[i][j] = (int)(total_product % mod);
                } else {
                    result[i][j] = 0;
                }
            } else {
                long long inv = 1;
                // Calculate modular inverse using Fermat's Little Theorem
                int a = grid[i][j] % mod;
                for (int k = 0; k < mod - 2; k++) {
                    inv = (inv * a) % mod;
                }
                result[i][j] = (int)((total_product * inv) % mod);
            }
        }
    }

    return result;      
}
