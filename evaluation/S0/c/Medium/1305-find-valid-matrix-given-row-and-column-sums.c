// Source: https://leetcode.com/problems/find-valid-matrix-given-row-and-column-sums/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays rowSum and colSum of non-negative integers where rowSum[i] is the sum of the elements in the ith row and colSum[j] is the sum of the elements of the jth column of a 2D matrix. In other words, you do not know the elements of the matrix, but you do know the sums of each row and column.
//
// Find any matrix of non-negative integers of size rowSum.length x colSum.length that satisfies the rowSum and colSum requirements.
//
// Return a 2D array representing any matrix that fulfills the requirements. It's guaranteed that at least one matrix that fulfills the requirements exists.
//
// Example:
// Input: rowSum = [3,8], colSum = [4,7]
// Output: [[3,0],
//          [1,7]]
// Explanation: 
// 0th row: 3 + 0 = 3 == rowSum[0]
// 1st row: 1 + 7 = 8 == rowSum[1]
// 0th column: 3 + 1 = 4 == colSum[0]
// 1st column: 0 + 7 = 7 == colSum[1]
// The row and column sums match, and all matrix elements are non-negative.
// Another possible matrix is: [[1,2],
//                              [3,5]]
//
// Constraints:
// 1 <= rowSum.length, colSum.length <= 500
// 	0 <= rowSum[i], colSum[i] <= 108
// 	sum(rowSum) == sum(colSum)
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** restoreMatrix(int* rowSum, int rowSumSize, int* colSum, int colSumSize, int* returnSize, int** returnColumnSizes) {
    int** matrix = (int**)malloc(sizeof(int*) * rowSumSize);
    *returnColumnSizes = (int*)malloc(sizeof(int) * rowSumSize);
    for (int i = 0; i < rowSumSize; i++) {
        matrix[i] = (int*)calloc(colSumSize, sizeof(int));
        (*returnColumnSizes)[i] = colSumSize;
    }
    *returnSize = rowSumSize;

    for (int i = 0; i < rowSumSize; i++) {
        for (int j = 0; j < colSumSize; j++) {
            int val = (rowSum[i] < colSum[j]) ? rowSum[i] : colSum[j];
            matrix[i][j] = val;
            rowSum[i] -= val;
            colSum[j] -= val;
        }
    }

    return matrix;      
}
