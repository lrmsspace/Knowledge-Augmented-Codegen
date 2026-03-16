// Source: https://leetcode.com/problems/transpose-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given a 2D integer array matrix, return the transpose of matrix.
//
// The transpose of a matrix is the matrix flipped over its main diagonal, switching the matrix's row and column indices.
//
// Example:
// Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [[1,4,7],[2,5,8],[3,6,9]]
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	-109 <= matrix[i][j] <= 109
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int row = matrixSize;
    int col = matrixColSize[0];
    
    // Allocate
    int** transposed = (int**)malloc(col * sizeof(int*));
    for (int i = 0; i < col; i++) {
        transposed[i] = (int*)malloc(row * sizeof(int));
    }   
         
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    *returnSize = col;
    *returnColumnSizes = (int*)malloc(col * sizeof(int));
    for (int i = 0; i < col; i++) {
        (*returnColumnSizes)[i] = row;
    }

    return transposed;
}