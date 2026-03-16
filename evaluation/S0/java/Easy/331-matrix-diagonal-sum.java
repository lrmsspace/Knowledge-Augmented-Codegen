// Source: https://leetcode.com/problems/matrix-diagonal-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given a square matrix mat, return the sum of the matrix diagonals.
//
// Only include the sum of all the elements on the primary diagonal and all the elements on the secondary diagonal that are not part of the primary diagonal.
//
// Example:
// Input: mat = [[1,2,3],
//               [4,5,6],
//               [7,8,9]]
// Output: 25
// Explanation: Diagonals sum: 1 + 5 + 9 + 3 + 7 = 25
// Notice that element mat[1][1] = 5 is counted only once.
//
// Constraints:
// n == mat.length == mat[i].length
// 	1 <= n <= 100
// 	1 <= mat[i][j] <= 100
//

class Solution {
    public int diagonalSum(int[][] mat) {
        int n = mat.length;
        int sum = 0;

        for (int i = 0; i < n; i++) {
            sum += mat[i][i]; // Primary diagonal
            sum += mat[i][n - 1 - i]; // Secondary diagonal
        }

        // If n is odd, subtract the middle element which was added twice
        if (n % 2 == 1) {
            sum -= mat[n / 2][n / 2];
        }

        return sum;         
    }
}
