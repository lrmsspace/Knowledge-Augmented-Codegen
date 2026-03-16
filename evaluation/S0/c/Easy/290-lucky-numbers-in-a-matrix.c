// Source: https://leetcode.com/problems/lucky-numbers-in-a-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given an m x n matrix of distinct numbers, return all lucky numbers in the matrix in any order.
//
// A lucky number is an element of the matrix such that it is the minimum element in its row and maximum in its column.
//
// Example:
// Input: matrix = [[3,7,8],[9,11,13],[15,16,17]]
// Output: [15]
// Explanation: 15 is the only lucky number since it is the minimum in its row and the maximum in its column.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= n, m <= 50
// 	1 <= matrix[i][j] <= 105.
// 	All elements in the matrix are distinct.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* luckyNumbers(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {
    int *rowMins = (int *)malloc(matrixSize * sizeof(int));
    int *colMaxs = (int *)malloc((*matrixColSize) * sizeof(int));
    int *luckyNumbers = (int *)malloc((matrixSize < *matrixColSize ? matrixSize : *matrixColSize) * sizeof(int));
    *returnSize = 0;

    // Find the minimum of each row
    for (int i = 0; i < matrixSize; i++) {
        int minVal = matrix[i][0];
        for (int j = 1; j < *matrixColSize; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        rowMins[i] = minVal;
    }

    // Find the maximum of each column
    for (int j = 0; j < *matrixColSize; j++) {
        int maxVal = matrix[0][j];
        for (int i = 1; i < matrixSize; i++) {
            if (matrix[i][j] > maxVal) {
                maxVal = matrix[i][j];
            }
        }
        colMaxs[j] = maxVal;
    }

    // Find lucky numbers
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < *matrixColSize; j++) {
            if (matrix[i][j] == rowMins[i] && matrix[i][j] == colMaxs[j]) {
                luckyNumbers[*returnSize] = matrix[i][j];
                (*returnSize)++;
            }
        }
    }

    free(rowMins);
    free(colMaxs);

    return luckyNumbers;        
}
