// Source: https://leetcode.com/problems/check-if-every-row-and-column-contains-all-numbers/   |   Difficulty: Easy
//
// Problem Description:
// An n x n matrix is valid if every row and every column contains all the integers from 1 to n (inclusive).
//
// Given an n x n integer matrix matrix, return true if the matrix is valid. Otherwise, return false.
//
// Example:
// Input: matrix = [[1,2,3],[3,1,2],[2,3,1]]
// Output: true
// Explanation: In this case, n = 3, and every row and column contains the numbers 1, 2, and 3.
// Hence, we return true.
//
// Constraints:
// n == matrix.length == matrix[i].length
// 	1 <= n <= 100
// 	1 <= matrix[i][j] <= n
//

class Solution {
    public boolean checkValid(int[][] matrix) {
        int n = matrix.length;

        // Check each row
        for (int i = 0; i < n; i++) {
            boolean[] seenRow = new boolean[n + 1];
            for (int j = 0; j < n; j++) {
                int num = matrix[i][j];
                if (seenRow[num]) {
                    return false; // Duplicate found in row
                }
                seenRow[num] = true;
            }
        }

        // Check each column
        for (int j = 0; j < n; j++) {
            boolean[] seenCol = new boolean[n + 1];
            for (int i = 0; i < n; i++) {
                int num = matrix[i][j];
                if (seenCol[num]) {
                    return false; // Duplicate found in column
                }
                seenCol[num] = true;
            }
        }

        return true; // All rows and columns are valid          
    }
}
