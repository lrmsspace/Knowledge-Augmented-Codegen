// Source: https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:
//
//
// 	1 which means a street connecting the left cell and the right cell.
// 	2 which means a street connecting the upper cell and the lower cell.
// 	3 which means a street connecting the left cell and the lower cell.
// 	4 which means a street connecting the right cell and the lower cell.
// 	5 which means a street connecting the left cell and the upper cell.
// 	6 which means a street connecting the right cell and the upper cell.
//
//
// You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.
//
// Notice that you are not allowed to change any street.
//
// Return true if there is a valid path in the grid or false otherwise.
//
// Example:
// Input: grid = [[2,4,3],[6,5,2]]
// Output: true
// Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 300
// 	1 <= grid[i][j] <= 6
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean hasValidPath(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        return dfs(grid, visited, 0, 0);            
    }
}
