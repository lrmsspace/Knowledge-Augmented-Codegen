// Source: https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.
//
// Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell. Since the answer may be very large, return it modulo 109 + 7.
//
// Two paths are considered different if they do not have exactly the same sequence of visited cells.
//
// Example:
// Input: grid = [[1,1],[3,4]]
// Output: 8
// Explanation: The strictly increasing paths are:
// - Paths with length 1: [1], [1], [3], [4].
// - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
// - Paths with length 3: [1 -> 3 -> 4].
// The total number of paths is 4 + 3 + 1 = 8.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

class Solution {
    public int countPaths(int[][] grid) {
        int MOD = 1_000_000_007;
        int m = grid.length;
        int n = grid[0].length;
        Integer[][] memo = new Integer[m][n];

        int totalPaths = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                totalPaths = (totalPaths + dfs(grid, i, j, memo, MOD)) % MOD;
            }
        }

        return totalPaths;          
    }
}
