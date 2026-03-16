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

/**
 * @param {number[][]} grid
 * @return {number}
 */
var matrixScore = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    for (let i = 0; i < m; i++) {
        if (grid[i][0] === 0) {
            for (let j = 0; j < n; j++) {
                grid[i][j] ^= 1;
            }
        }
    }
    let score = 0;
    for (let j = 0; j < n; j++) {
        let countOnes = 0;  
        for (let i = 0; i < m; i++) {
            countOnes += grid[i][j];
        }
        const maxOnes = Math.max(countOnes, m - countOnes);
        score += maxOnes * (1 << (n - j - 1));
    }
    return score;   
};
