// Source: https://leetcode.com/problems/path-with-maximum-gold/   |   Difficulty: Medium
//
// Problem Description:
// In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
//
// Return the maximum amount of gold you can collect under the conditions:
//
//
// 	Every time you are located in a cell you will collect all the gold in that cell.
// 	From your position, you can walk one step to the left, right, up, or down.
// 	You can't visit the same cell more than once.
// 	Never visit a cell with 0 gold.
// 	You can start and stop collecting gold from any position in the grid that has some gold.
//
// Example:
// Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
// Output: 24
// Explanation:
// [[0,6,0],
//  [5,8,7],
//  [0,9,0]]
// Path to get the maximum gold, 9 -> 8 -> 7.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	0 <= grid[i][j] <= 100
// 	There are at most 25 cells containing gold.
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
    public int getMaximumGold(int[][] grid) {
        int maxGold = 0;
        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] > 0) {
                    maxGold = Math.max(maxGold, dfs(grid, i, j));
                }
            }
        }
        return maxGold;         
    }
}
