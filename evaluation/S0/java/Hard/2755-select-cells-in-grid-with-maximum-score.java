// Source: https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D matrix grid consisting of positive integers.
//
// You have to select one or more cells from the matrix such that the following conditions are satisfied:
//
//
// 	No two selected cells are in the same row of the matrix.
// 	The values in the set of selected cells are unique.
//
//
// Your score will be the sum of the values of the selected cells.
//
// Return the maximum score you can achieve.
//
// Example:
// Input: grid = [[1,2,3],[4,3,2],[1,1,1]]
//
// Output: 8
//
// Explanation:
//
//
//
// We can select the cells with values 1, 3, and 4 that are colored above.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 10
// 	1 <= grid[i][j] <= 100
//

class Solution {
    public int maxScore(List<List<Integer>> grid) {
        int rows = grid.size();
        int cols = grid.get(0).size();
        int maxMask = 1 << cols;
        int[][] dp = new int[rows + 1][maxMask];

        for (int r = rows - 1; r >= 0; r--) {
            for (int mask = 0; mask < maxMask; mask++) {
                dp[r][mask] = dp[r + 1][mask]; // Skip current row
                for (int c = 0; c < cols; c++) {
                    int val = grid.get(r).get(c);
                    if ((mask & (1 << c)) == 0) { // If column c is not used
                        dp[r][mask] = Math.max(dp[r][mask],
                                val + dp[r + 1][mask | (1 << c)]);
                    }
                }
            }
        }

        return dp[0][0];            
    }
}
