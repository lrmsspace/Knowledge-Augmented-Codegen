// Source: https://leetcode.com/problems/stamping-the-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary matrix grid where each cell is either 0 (empty) or 1 (occupied).
//
// You are then given stamps of size stampHeight x stampWidth. We want to fit the stamps such that they follow the given restrictions and requirements:
//
//
// 	Cover all the empty cells.
// 	Do not cover any of the occupied cells.
// 	We can put as many stamps as we want.
// 	Stamps can overlap with each other.
// 	Stamps are not allowed to be rotated.
// 	Stamps must stay completely inside the grid.
//
//
// Return true if it is possible to fit the stamps while following the given restrictions and requirements. Otherwise, return false.
//
// Example:
// Input: grid = [[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0],[1,0,0,0]], stampHeight = 4, stampWidth = 3
// Output: true
// Explanation: We have two overlapping stamps (labeled 1 and 2 in the image) that are able to cover all the empty cells.
//
// Constraints:
// m == grid.length
// 	n == grid[r].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 2 * 105
// 	grid[r][c] is either 0 or 1.
// 	1 <= stampHeight, stampWidth <= 105
//

/**
 * @param {number[][]} grid
 * @param {number} stampHeight
 * @param {number} stampWidth
 * @return {boolean}
 */
var possibleToStamp = function(grid, stampHeight, stampWidth) {
    const m = grid.length;
    const n = grid[0].length;
    const prefixSum = new Array(m + 1).fill(0).map(() => new Array(n + 1).fill(0));
    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            prefixSum[i][j] = grid[i - 1][j - 1] + prefixSum[i - 1][j] + prefixSum[i][j - 1] - prefixSum[i - 1][j - 1];
        }
    }

    const canStamp = new Array(m).fill(0).map(() => new Array(n).fill(false));
    for (let i = stampHeight; i <= m; i++) {
        for (let j = stampWidth; j <= n; j++) {
            const totalCells = stampHeight * stampWidth;
            const occupiedCells = prefixSum[i][j] - prefixSum[i - stampHeight][j] - prefixSum[i][j - stampWidth] + prefixSum[i - stampHeight][j - stampWidth];
            if (occupiedCells === 0) {
                canStamp[i - 1][j - 1] = true;
            }
        }
    }

    const stampCoverage = new Array(m + 1).fill(0).map(() => new Array(n + 1).fill(0));
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (canStamp[i][j]) {
                stampCoverage[i + 1][j + 1] += 1;
                if (i + stampHeight <= m) {
                    stampCoverage[i + stampHeight][j + 1] -= 1;
                }
                if (j + stampWidth <= n) {
                    stampCoverage[i + 1][j + stampWidth] -= 1;
                }
                if (i + stampHeight <= m && j + stampWidth <= n) {
                    stampCoverage[i + stampHeight][j + stampWidth] += 1;
                }
            }
        }
    }

    for (let i = 1; i <= m; i++) {
        for (let j = 1; j <= n; j++) {
            stampCoverage[i][j] += stampCoverage[i - 1][j] + stampCoverage[i][j - 1] - stampCoverage[i - 1][j - 1];
            if (grid[i - 1][j - 1] === 0 && stampCoverage[i][j] <= 0) {
                return false;
            }
        }
    }
    return true;
};
