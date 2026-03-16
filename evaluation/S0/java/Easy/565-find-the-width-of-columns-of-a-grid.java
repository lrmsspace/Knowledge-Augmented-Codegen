// Source: https://leetcode.com/problems/find-the-width-of-columns-of-a-grid/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid. The width of a column is the maximum length of its integers.
//
//
// 	For example, if grid = [[-10], [3], [12]], the width of the only column is 3 since -10 is of length 3.
//
//
// Return an integer array ans of size n where ans[i] is the width of the ith column.
//
// The length of an integer x with len digits is equal to len if x is non-negative, and len + 1 otherwise.
//
// Example:
// Input: grid = [[1],[22],[333]]
// Output: [3]
// Explanation: In the 0th column, 333 is of length 3.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100 
// 	-109 <= grid[r][c] <= 109
//

class Solution {
    public int[] findColumnWidth(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;
        int[] result = new int[n];

        for (int col = 0; col < n; col++) {
            int maxWidth = 0;
            for (int row = 0; row < m; row++) {
                int length = String.valueOf(grid[row][col]).length();
                maxWidth = Math.max(maxWidth, length);
            }
            result[col] = maxWidth;
        }

        return result;          
    }
}
