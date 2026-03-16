// Source: https://leetcode.com/problems/diagonal-traverse/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n matrix mat, return an array of all the elements of the array in a diagonal order.
//
// Example:
// Input: mat = [[1,2,3],[4,5,6],[7,8,9]]
// Output: [1,2,4,7,5,3,6,8,9]
//
// Constraints:
// m == mat.length
// 	n == mat[i].length
// 	1 <= m, n <= 104
// 	1 <= m * n <= 104
// 	-105 <= mat[i][j] <= 105
//

class Solution {
    public int[] findDiagonalOrder(int[][] mat) {
        if (mat == null || mat.length == 0) {
            return new int[0];
        }

        int m = mat.length;
        int n = mat[0].length;
        int[] result = new int[m * n];
        int row = 0, col = 0;

        for (int i = 0; i < m * n; i++) {
            result[i] = mat[row][col];

            // Determine the direction of movement
            if ((row + col) % 2 == 0) { // Moving up
                if (col == n - 1) { // Hit the right boundary
                    row++;
                } else if (row == 0) { // Hit the top boundary
                    col++;
                } else { // Move up diagonally
                    row--;
                    col++;
                }
            } else { // Moving down
                if (row == m - 1) { // Hit the bottom boundary
                    col++;
                } else if (col == 0) { // Hit the left boundary
                    row++;
                } else { // Move down diagonally
                    row++;
                    col--;
                }
            }
        }

        return result;          
    }
}
