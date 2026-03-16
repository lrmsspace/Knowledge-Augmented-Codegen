// Source: https://leetcode.com/problems/sort-matrix-by-diagonals/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n square matrix of integers grid. Return the matrix such that:
//
//
// 	The diagonals in the bottom-left triangle (including the middle diagonal) are sorted in non-increasing order.
// 	The diagonals in the top-right triangle are sorted in non-decreasing order.
//
// Example:
// Input: grid = [[1,7,3],[9,8,2],[4,5,6]]
//
// Output: [[8,2,3],[9,6,7],[4,5,1]]
//
// Explanation:
//
//
//
// The diagonals with a black arrow (bottom-left triangle) should be sorted in non-increasing order:
//
//
// 	[1, 8, 6] becomes [8, 6, 1].
// 	[9, 5] and [4] remain unchanged.
//
//
// The diagonals with a blue arrow (top-right triangle) should be sorted in non-decreasing order:
//
//
// 	[7, 2] becomes [2, 7].
// 	[3] remains unchanged.
//
// Constraints:
// grid.length == grid[i].length == n
// 	1 <= n <= 10
// 	-105 <= grid[i][j] <= 105
//

class Solution {
    public int[][] sortMatrix(int[][] grid) {
        int n = grid.length;

        // Sort bottom-left diagonals in non-increasing order
        for (int col = 0; col < n; col++) {
            sortDiagonal(grid, 0, col, false);
        }
        for (int row = 1; row < n; row++) {
            sortDiagonal(grid, row, 0, false);
        }

        // Sort top-right diagonals in non-decreasing order
        for (int col = 0; col < n; col++) {
            sortDiagonal(grid, 0, col, true);
        }
        for (int row = 1; row < n; row++) {
            sortDiagonal(grid, row, n - 1, true);
        }

        return grid;            
    }
}
