// Source: https://leetcode.com/problems/modify-the-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed m x n integer matrix matrix, create a new 0-indexed matrix called answer. Make answer equal to matrix, then replace each element with the value -1 with the maximum element in its respective column.
//
// Return the matrix answer.
//
// Example:
// Input: matrix = [[1,2,-1],[4,-1,6],[7,8,9]]
// Output: [[1,2,9],[4,8,6],[7,8,9]]
// Explanation: The diagram above shows the elements that are changed (in blue).
// - We replace the value in the cell [1][1] with the maximum value in the column 1, that is 8.
// - We replace the value in the cell [0][2] with the maximum value in the column 2, that is 9.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	2 <= m, n <= 50
// 	-1 <= matrix[i][j] <= 100
// 	The input is generated such that each column contains at least one non-negative integer.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** modifiedMatrix(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int m = matrixSize;
    int n = matrixColSize[0];
    
    // Allocate memory for the answer matrix
    int** answer = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        answer[i] = (int*)malloc(n * sizeof(int));
    }
    
    // Create an array to store the maximum values of each column
    int* maxInColumn = (int*)malloc(n * sizeof(int));
    for (int j = 0; j < n; j++) {
        maxInColumn[j] = -1; // Initialize with -1
        for (int i = 0; i < m; i++) {
            if (matrix[i][j] > maxInColumn[j]) {
                maxInColumn[j] = matrix[i][j];
            }
        }
    }
    
    // Fill the answer matrix
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == -1) {
                answer[i][j] = maxInColumn[j];
            } else {
                answer[i][j] = matrix[i][j];
            }
        }
    }
    
    // Set return size and column sizes
    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
    }
    
    // Free the maxInColumn array
    free(maxInColumn);
    
    return answer;      
}
