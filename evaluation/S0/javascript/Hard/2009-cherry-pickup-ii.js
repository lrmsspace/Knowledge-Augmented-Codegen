// Source: https://leetcode.com/problems/cherry-pickup-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a rows x cols matrix grid representing a field of cherries where grid[i][j] represents the number of cherries that you can collect from the (i, j) cell.
//
// You have two robots that can collect cherries for you:
//
//
// 	Robot #1 is located at the top-left corner (0, 0), and
// 	Robot #2 is located at the top-right corner (0, cols - 1).
//
//
// Return the maximum number of cherries collection using both robots by following the rules below:
//
//
// 	From a cell (i, j), robots can move to cell (i + 1, j - 1), (i + 1, j), or (i + 1, j + 1).
// 	When any robot passes through a cell, It picks up all cherries, and the cell becomes an empty cell.
// 	When both robots stay in the same cell, only one takes the cherries.
// 	Both robots cannot move outside of the grid at any moment.
// 	Both robots should reach the bottom row in grid.
//
// Example:
// Input: grid = [[3,1,1],[2,5,1],[1,5,5],[2,1,1]]
// Output: 24
// Explanation: Path of robot #1 and #2 are described in color green and blue respectively.
// Cherries taken by Robot #1, (3 + 2 + 5 + 2) = 12.
// Cherries taken by Robot #2, (1 + 5 + 5 + 1) = 12.
// Total of cherries: 12 + 12 = 24.
//
// Constraints:
// rows == grid.length
// 	cols == grid[i].length
// 	2 <= rows, cols <= 70
// 	0 <= grid[i][j] <= 100
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var cherryPickup = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;
    const dp = new Array(rows).fill(0).map(() => new Array(cols).fill(0).map(() => new Array(cols).fill(0)));
    for (let j1 = 0; j1 < cols; j1++) {
        for (let j2 = 0; j2 < cols; j2++) {
            dp[0][j1][j2] = grid[0][j1] + (j1 === j2 ? 0 : grid[0][j2]);
        }
    }
    for (let i = 1; i < rows; i++) {
        for (let j1 = 0; j1 < cols; j1++) {
            for (let j2 = 0; j2 < cols; j2++) {
                let maxCherries = 0;
                for (let dj1 = -1; dj1 <= 1; dj1++) {
                    for (let dj2 = -1; dj2 <= 1; dj2++) {
                        const prevJ1 = j1 + dj1;
                        const prevJ2 = j2 + dj2;
                        if (prevJ1 >= 0 && prevJ1 < cols && prevJ2 >= 0 && prevJ2 < cols) {
                            maxCherries = Math.max(maxCherries, dp[i - 1][prevJ1][prevJ2]);
                        }
                    }
                }
                dp[i][j1][j2] = maxCherries + grid[i][j1] + (j1 === j2 ? 0 : grid[i][j2]);
            }
        }
    }
    let result = 0;
    for (let j1 = 0; j1 < cols; j1++) {
        for (let j2 = 0; j2 < cols; j2++) {
            result = Math.max(result, dp[rows - 1][j1][j2]);
        }
    }
    return result;
};
