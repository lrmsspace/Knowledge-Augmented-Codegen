// Source: https://leetcode.com/problems/score-after-flipping-matrix/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid.
//
// A move consists of choosing any row or column and toggling each value in that row or column (i.e., changing all 0's to 1's, and all 1's to 0's).
//
// Every row of the matrix is interpreted as a binary number, and the score of the matrix is the sum of these numbers.
//
// Return the highest possible score after making any number of moves (including zero moves).
//
// Example:
// Input: grid = [[0,0,1,1],[1,0,1,0],[1,1,0,0]]
// Output: 39
// Explanation: 0b1111 + 0b1001 + 0b1111 = 15 + 9 + 15 = 39
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	grid[i][j] is either 0 or 1.
//

class Solution {
    public int matrixScore(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        // Step 1: Ensure the first column has all 1's
        for (int i = 0; i < m; i++) {
            if (grid[i][0] == 0) {
                for (int j = 0; j < n; j++) {
                    grid[i][j] ^= 1; // Toggle the entire row
                }
            }
        }

        int totalScore = 0;

        // Step 2: Calculate the score column by column
        for (int j = 0; j < n; j++) {
            int countOnes = 0;
            for (int i = 0; i < m; i++) {
                if (grid[i][j] == 1) {
                    countOnes++;
                }
            }

            // Maximize the number of 1's in the current column
            int maxOnes = Math.max(countOnes, m - countOnes);
            totalScore += maxOnes * (1 << (n - j - 1)); // Add to total score
        }

        return totalScore;          
    }
}
