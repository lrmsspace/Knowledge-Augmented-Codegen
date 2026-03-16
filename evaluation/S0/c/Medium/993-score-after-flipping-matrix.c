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

int matrixScore(int** grid, int gridSize, int* gridColSize) {
    int m = gridSize;
    int n = *gridColSize;
    int score = 0;

    // Ensure the first column has all 1s by flipping rows if necessary
    for (int i = 0; i < m; i++) {
        if (grid[i][0] == 0) {
            for (int j = 0; j < n; j++) {
                grid[i][j] ^= 1; // Flip the row
            }
        }
    }

    // Calculate the score
    for (int j = 0; j < n; j++) {
        int countOnes = 0;
        for (int i = 0; i < m; i++) {
            countOnes += grid[i][j];
        }
        // Maximize the number of 1s in the column
        countOnes = countOnes > m / 2 ? countOnes : m - countOnes;
        score += countOnes * (1 << (n - j - 1)); // Add to score based on binary position
    }

    return score;       
}
