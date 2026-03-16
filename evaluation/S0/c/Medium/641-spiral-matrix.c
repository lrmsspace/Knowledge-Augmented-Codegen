// Source: https://leetcode.com/problems/spiral-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n matrix, return all elements of the matrix in spiral order.
//
// Example:
// Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,3,6,9,8,7,4,5]
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m, n <= 10
// 	-100 <= matrix[i][j] <= 100
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    if (matrixSize == 0 || matrixColSize[0] == 0) {
        *returnSize = 0;
        return NULL;
    }

    int rows = matrixSize;
    int cols = matrixColSize[0];
    int totalElements = rows * cols;
    int* result = (int*)malloc(totalElements * sizeof(int));
    *returnSize = totalElements;

    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;
    int index = 0;

    while (top <= bottom && left <= right) {
        // Traverse from left to right
        for (int col = left; col <= right; col++) {
            result[index++] = matrix[top][col];
        }
        top++;

        // Traverse from top to bottom
        for (int row = top; row <= bottom; row++) {
            result[index++] = matrix[row][right];
        }
        right--;

        if (top <= bottom) {
            // Traverse from right to left
            for (int col = right; col >= left; col--) {
                result[index++] = matrix[bottom][col];
            }
            bottom--;
        }

        if (left <= right) {
            // Traverse from bottom to top
            for (int row = bottom; row >= top; row--) {
                result[index++] = matrix[row][left];
            }
            left++;
        }
    }

    return result;      
}
