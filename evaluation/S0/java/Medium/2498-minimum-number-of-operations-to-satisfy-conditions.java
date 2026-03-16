// Source: https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D matrix grid of size m x n. In one operation, you can change the value of any cell to any non-negative number. You need to perform some operations such that each cell grid[i][j] is:
//
//
// 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
// 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
//
//
// Return the minimum number of operations needed.
//
// Example:
// Input: grid = [[1,0,2],[1,0,2]]
//
// Output: 0
//
// Explanation:
//
//
//
// All the cells in the matrix already satisfy the properties.
//
// Constraints:
// 1 <= n, m <= 1000
// 	0 <= grid[i][j] <= 9
//

class Solution {
    public int minimumOperations(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int operations = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // Check the cell below
                if (i + 1 < m && grid[i][j] != grid[i + 1][j]) {
                    operations++;
                    grid[i + 1][j] = grid[i][j]; // Make them equal
                }
                // Check the cell to the right
                if (j + 1 < n && grid[i][j] == grid[i][j + 1]) {
                    operations++;
                    grid[i][j + 1] = (grid[i][j] + 1) % 10; // Change to a different value
                }
            }
        }

        return operations;          
    }
}
