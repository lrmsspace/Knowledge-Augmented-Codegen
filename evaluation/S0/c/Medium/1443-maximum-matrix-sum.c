// Source: https://leetcode.com/problems/maximum-matrix-sum/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n integer matrix. You can do the following operation any number of times:
//
//
// 	Choose any two adjacent elements of matrix and multiply each of them by -1.
//
//
// Two elements are considered adjacent if and only if they share a border.
//
// Your goal is to maximize the summation of the matrix's elements. Return the maximum sum of the matrix's elements using the operation mentioned above.
//
// Example:
// Input: matrix = [[1,-1],[-1,1]]
// Output: 4
// Explanation: We can follow the following steps to reach sum equals 4:
// - Multiply the 2 elements in the first row by -1.
// - Multiply the 2 elements in the first column by -1.
//
// Constraints:
// n == matrix.length == matrix[i].length
// 	2 <= n <= 250
// 	-105 <= matrix[i][j] <= 105
//

long long maxMatrixSum(int** matrix, int matrixSize, int* matrixColSize) {
    long long totalSum = 0;
    int minAbsValue = 100001; // Since -10^5 <= matrix[i][j] <= 10^5
    int negativeCount = 0;

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixColSize[i]; j++) {
            int value = matrix[i][j];
            totalSum += llabs(value);
            if (llabs(value) < minAbsValue) {
                minAbsValue = llabs(value);
            }
            if (value < 0) {
                negativeCount++;
            }
        }
    }

    // If the count of negative numbers is odd, we need to subtract twice the smallest absolute value
    if (negativeCount % 2 != 0) {
        totalSum -= 2 * minAbsValue;
    }

    return totalSum;        
}
