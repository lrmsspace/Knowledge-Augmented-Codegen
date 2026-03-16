// Source: https://leetcode.com/problems/largest-1-bordered-square/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
//
// Example:
// Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
// Output: 9
//
// Constraints:
// 1 <= grid.length <= 100
// 	1 <= grid[0].length <= 100
// 	grid[i][j] is 0 or 1
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var largest1BorderedSquare = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const right = Array.from({ length: m }, () => Array(n).fill(0));
    const down = Array.from({ length: m }, () => Array(n).fill(0));
    let maxSide = 0;
    for (let i = m - 1; i >= 0; i--) {
        for (let j = n - 1; j >= 0; j--) {
            if (grid[i][j] === 1) {
                right[i][j] = (j + 1 < n ? right[i][j + 1] : 0) + 1;
                down[i][j] = (i + 1 < m ? down[i + 1][j] : 0) + 1;
                const possibleSide = Math.min(right[i][j], down[i][j]);
                for (let side = possibleSide; side > 0; side--) {
                    if (right[i + side - 1][j] >= side && down[i][j + side - 1] >= side) {
                        maxSide = Math.max(maxSide, side);
                        break;
                    }
                }
            }
        }
    }
    return maxSide * maxSide;
        
};
