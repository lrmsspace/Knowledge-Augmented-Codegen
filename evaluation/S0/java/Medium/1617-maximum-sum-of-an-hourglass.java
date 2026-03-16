// Source: https://leetcode.com/problems/maximum-sum-of-an-hourglass/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid.
//
// We define an hourglass as a part of the matrix with the following form:
//
// Return the maximum sum of the elements of an hourglass.
//
// Note that an hourglass cannot be rotated and must be entirely contained within the matrix.
//
// Example:
// Input: grid = [[6,2,1,3],[4,2,1,5],[9,2,8,7],[4,1,2,9]]
// Output: 30
// Explanation: The cells shown above represent the hourglass with the maximum sum: 6 + 2 + 1 + 2 + 9 + 2 + 8 = 30.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	3 <= m, n <= 150
// 	0 <= grid[i][j] <= 106
//

class Solution {
    public int maxSum(int[][] grid) {
        int maxSum = 0;
        int rows = grid.length;
        int cols = grid[0].length;

        for (int i = 0; i <= rows - 3; i++) {
            for (int j = 0; j <= cols - 3; j++) {
                int currentSum = grid[i][j] + grid[i][j + 1] + grid[i][j + 2]
                               + grid[i + 1][j + 1]
                               + grid[i + 2][j] + grid[i + 2][j + 1] + grid[i + 2][j + 2];

                maxSum = Math.max(maxSum, currentSum);
            }
        }

        return maxSum;          
    }
}
