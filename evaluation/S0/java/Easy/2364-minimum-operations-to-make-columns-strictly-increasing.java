// Source: https://leetcode.com/problems/minimum-operations-to-make-columns-strictly-increasing/   |   Difficulty: Easy
//
// Problem Description:
// You are given a m x n matrix grid consisting of non-negative integers.
//
// In one operation, you can increment the value of any grid[i][j] by 1.
//
// Return the minimum number of operations needed to make all columns of grid strictly increasing.
//
// Example:
// Input: grid = [[3,2],[1,3],[3,4],[0,1]]
//
// Output: 15
//
// Explanation:
//
//
// 	To make the 0th column strictly increasing, we can apply 3 operations on grid[1][0], 2 operations on grid[2][0], and 6 operations on grid[3][0].
// 	To make the 1st column strictly increasing, we can apply 4 operations on grid[3][1].
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	0 <= grid[i][j] < 2500
//

class Solution {
    public int minimumOperations(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int totalOperations = 0;

        for (int col = 0; col < n; col++) {
            int prevValue = -1; // Initialize to a value less than any possible grid value

            for (int row = 0; row < m; row++) {
                if (grid[row][col] <= prevValue) {
                    int requiredValue = prevValue + 1;
                    totalOperations += requiredValue - grid[row][col];
                    grid[row][col] = requiredValue; // Update the cell to the required value
                }
                prevValue = grid[row][col]; // Update prevValue for the next row
            }
        }

        return totalOperations;         
    }
}
