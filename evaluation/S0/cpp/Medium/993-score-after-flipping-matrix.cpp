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
public:
    int matrixScore(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();

        // Step 1: Ensure the first column is all 1s
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 0) {
                for (int j = 0; j < n; ++j) {
                    grid[i][j] ^= 1; // Flip the row
                }
            }
        }

        // Step 2: Maximize the number of 1s in each column
        for (int j = 1; j < n; ++j) {
            int countOnes = 0;
            for (int i = 0; i < m; ++i) {
                if (grid[i][j] == 1) {
                    countOnes++;
                }
            }
            if (countOnes < (m + 1) / 2) { // More 0s than 1s
                for (int i = 0; i < m; ++i) {
                    grid[i][j] ^= 1; // Flip the column
                }
            }
        }

        // Step 3: Calculate the final score
        int totalScore = 0;
        for (int i = 0; i < m; ++i) {
            int rowValue = 0;
            for (int j = 0; j < n; ++j) {
                rowValue = (rowValue << 1) | grid[i][j];
            }
            totalScore += rowValue;
        }

        return totalScore;          
    }
};
