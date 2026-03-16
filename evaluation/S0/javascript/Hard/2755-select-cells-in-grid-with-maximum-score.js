// Source: https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D matrix grid consisting of positive integers.
//
// You have to select one or more cells from the matrix such that the following conditions are satisfied:
//
//
// 	No two selected cells are in the same row of the matrix.
// 	The values in the set of selected cells are unique.
//
//
// Your score will be the sum of the values of the selected cells.
//
// Return the maximum score you can achieve.
//
// Example:
// Input: grid = [[1,2,3],[4,3,2],[1,1,1]]
//
// Output: 8
//
// Explanation:
//
//
//
// We can select the cells with values 1, 3, and 4 that are colored above.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 10
// 	1 <= grid[i][j] <= 100
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxScore = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    let maxScore = 0;
    const backtrack = (row, usedValues, currentScore) => {
        if (row === m) {
            maxScore = Math.max(maxScore, currentScore);
            return;
        }
        for (let col = 0; col < n; col++) {
            const value = grid[row][col];
            if (!usedValues.has(value)) {
                usedValues.add(value);
                backtrack(row + 1, usedValues, currentScore + value);
                usedValues.delete(value);
            }
        }
        // Also consider the case of skipping the current row
        backtrack(row + 1, usedValues, currentScore);
    }
    backtrack(0, new Set(), 0);
    return maxScore;
};
