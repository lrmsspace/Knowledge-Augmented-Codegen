// Source: https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix mat and an integer target.
//
// Choose one integer from each row in the matrix such that the absolute difference between target and the sum of the chosen elements is minimized.
//
// Return the minimum absolute difference.
//
// The absolute difference between two numbers a and b is the absolute value of a - b.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]], target = 13
// Output: 0
// Explanation: One possible choice is to:
// - Choose 1 from the first row.
// - Choose 5 from the second row.
// - Choose 7 from the third row.
// The sum of the chosen elements is 13, which equals the target, so the absolute difference is 0.
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 70
// 	1 <= mat[i][j] <= 70
// 	1 <= target <= 800
//

int minimizeTheDifference(int** mat, int matSize, int* matColSize, int target) {
    int maxSum = 70 * 70; // Maximum possible sum given constraints
    bool dp[matSize + 1][maxSum + 1];
    
    // Initialize DP table
    for (int i = 0; i <= matSize; i++) {
        for (int j = 0; j <= maxSum; j++) {
            dp[i][j] = false;
        }
    }
    dp[0][0] = true; // Base case: sum of 0 with 0 rows

    // Fill the DP table
    for (int i = 1; i <= matSize; i++) {
        for (int j = 0; j <= maxSum; j++) {
            for (int k = 0; k < matColSize[i - 1]; k++) {
                int val = mat[i - 1][k];
                if (j >= val && dp[i - 1][j - val]) {
                    dp[i][j] = true;
                    break;
                }
            }
        }
    }

    // Find the minimum absolute difference
    int minDiff = target; // Start with the maximum possible difference
    for (int j = 0; j <= maxSum; j++) {
        if (dp[matSize][j]) {
            int diff = abs(j - target);
            if (diff < minDiff) {
                minDiff = diff;
            }
        }
    }

    return minDiff;     
}
