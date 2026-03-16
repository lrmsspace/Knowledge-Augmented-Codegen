// Source: https://leetcode.com/problems/minimum-falling-path-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
//
// A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
//
// Example:
// Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
// Output: 13
// Explanation: There are two falling paths with a minimum sum as shown.
//
// Constraints:
// n == matrix.length == matrix[i].length
// 	1 <= n <= 100
// 	-100 <= matrix[i][j] <= 100
//

int minFallingPathSum(int** matrix, int matrixSize, int* matrixColSize) {
    int n = matrixSize;
    int dp[n][n];
    
    // Initialize the first row of dp with the first row of matrix
    for (int j = 0; j < n; j++) {
        dp[0][j] = matrix[0][j];
    }
    
    // Fill the dp table
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int left = (j > 0) ? dp[i - 1][j - 1] : INT_MAX;
            int up = dp[i - 1][j];
            int right = (j < n - 1) ? dp[i - 1][j + 1] : INT_MAX;
            dp[i][j] = matrix[i][j] + fmin(fmin(left, up), right);
        }
    }
    
    // Find the minimum value in the last row of dp
    int minSum = INT_MAX;
    for (int j = 0; j < n; j++) {
        if (dp[n - 1][j] < minSum) {
            minSum = dp[n - 1][j];
        }
    }
    
    return minSum;      
}
