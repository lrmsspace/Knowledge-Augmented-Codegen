// Source: https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer matrix grid of size 3 * 3, representing the number of stones in each cell. The grid contains exactly 9 stones, and there can be multiple stones in a single cell.
//
// In one move, you can move a single stone from its current cell to any other cell if the two cells share a side.
//
// Return the minimum number of moves required to place one stone in each cell.
//
// Example:
// Input: grid = [[1,1,0],[1,1,1],[1,2,1]]
// Output: 3
// Explanation: One possible sequence of moves to place one stone in each cell is: 
// 1- Move one stone from cell (2,1) to cell (2,2).
// 2- Move one stone from cell (2,2) to cell (1,2).
// 3- Move one stone from cell (1,2) to cell (0,2).
// In total, it takes 3 moves to place one stone in each cell of the grid.
// It can be shown that 3 is the minimum number of moves required to place one stone in each cell.
//
// Constraints:
// grid.length == grid[i].length == 3
// 	0 <= grid[i][j] <= 9
// 	Sum of grid is equal to 9.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minimumMoves = function(grid) {
    const targetPositions = [];
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            targetPositions.push([i, j]);
        }
    }
    const stonePositions = [];
    for (let i = 0; i < 3; i++) {
        for (let j = 0; j < 3; j++) {
            for (let count = 0; count < grid[i][j]; count++) {
                stonePositions.push([i, j]);
            }
        }
    }
    let minMoves = Infinity;
    const used = new Array(9).fill(false);

    function backtrack(index, moves) {
        if (index === 9) {
            minMoves = Math.min(minMoves, moves);
            return;
        }
        for (let i = 0; i < 9; i++) {
            if (!used[i]) {
                used[i] = true;
                const dist = Math.abs(stonePositions[index][0] - targetPositions[i][0]) + Math.abs(stonePositions[index][1] - targetPositions[i][1]);
                backtrack(index + 1, moves + dist);
                used[i] = false;
            }
        }
    }

    backtrack(0, 0);
    return minMoves;
};