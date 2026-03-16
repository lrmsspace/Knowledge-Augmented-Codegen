// Source: https://leetcode.com/problems/largest-submatrix-with-rearrangements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
//
// Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.
//
// Example:
// Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
// Output: 4
// Explanation: You can rearrange the columns as shown above.
// The largest submatrix of 1s, in bold, has an area of 4.
//
// Constraints:
// m == matrix.length
// 	n == matrix[i].length
// 	1 <= m * n <= 105
// 	matrix[i][j] is either 0 or 1.
//

class Solution {
    public int largestSubmatrix(int[][] matrix) {
        int m = matrix.length;
        int n = matrix[0].length;
        int[][] dp = new int[m][n];
        
        // Build the dp array to store heights of consecutive 1s in each column
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                if (matrix[i][j] == 1) {
                    dp[i][j] = (i == 0) ? 1 : dp[i - 1][j] + 1;
                } else {
                    dp[i][j] = 0;
                }
            }
        }
        
        int maxArea = 0;
        
        // For each row, sort the heights and calculate the maximum area
        for (int i = 0; i < m; i++) {
            int[] sortedHeights = dp[i].clone();
            Arrays.sort(sortedHeights);
            for (int j = 0; j < n; j++) {
                int height = sortedHeights[n - 1 - j];
                int width = j + 1;
                maxArea = Math.max(maxArea, height * width);
            }
        }
        
        return maxArea;         
    }
}
