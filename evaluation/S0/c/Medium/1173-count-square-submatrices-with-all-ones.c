// Source: https://leetcode.com/problems/count-square-submatrices-with-all-ones/   |   Difficulty: Medium
//
// Problem Description:
// Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.
//
// Example:
// Input: matrix =
// [
//   [0,1,1,1],
//   [1,1,1,1],
//   [0,1,1,1]
// ]
// Output: 15
// Explanation: 
// There are 10 squares of side 1.
// There are 4 squares of side 2.
// There is  1 square of side 3.
// Total number of squares = 10 + 4 + 1 = 15.
//
// Constraints:
// 1 <= arr.length <= 300
// 	1 <= arr[0].length <= 300
// 	0 <= arr[i][j] <= 1
//

int countSquares(int** matrix, int matrixSize, int* matrixColSize) {
    int rows = matrixSize;
    int cols = matrixColSize[0];
    int count = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] == 1 && i > 0 && j > 0) {
                matrix[i][j] += fmin(fmin(matrix[i - 1][j], matrix[i][j - 1]), matrix[i - 1][j - 1]);
            }
            count += matrix[i][j];
        }
    }

    return count;       
}
