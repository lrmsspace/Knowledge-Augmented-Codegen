// Source: https://leetcode.com/problems/spiral-matrix-iii/   |   Difficulty: Medium
//
// Problem Description:
// You start at the cell (rStart, cStart) of an rows x cols grid facing east. The northwest corner is at the first row and column in the grid, and the southeast corner is at the last row and column.
//
// You will walk in a clockwise spiral shape to visit every position in this grid. Whenever you move outside the grid's boundary, we continue our walk outside the grid (but may return to the grid boundary later.). Eventually, we reach all rows * cols spaces of the grid.
//
// Return an array of coordinates representing the positions of the grid in the order you visited them.
//
// Example:
// Input: rows = 1, cols = 4, rStart = 0, cStart = 0
// Output: [[0,0],[0,1],[0,2],[0,3]]
//
// Constraints:
// 1 <= rows, cols <= 100
// 	0 <= rStart < rows
// 	0 <= cStart < cols
//

/**
 * @param {number} rows
 * @param {number} cols
 * @param {number} rStart
 * @param {number} cStart
 * @return {number[][]}
 */
var spiralMatrixIII = function(rows, cols, rStart, cStart) {
    const result = [];
    const totalCells = rows * cols;
    let directions = [[0,1], [1,0], [0,-1], [-1,0]]; // right, down, left, up
    let stepSize = 1;
    let r = rStart;
    let c = cStart;
    let dirIndex = 0;
    result.push([r, c]);
    while (result.length < totalCells) {
        for (let i = 0; i < 2; i++) { // two directions for each step size
            for (let j = 0; j < stepSize; j++) {   
                r += directions[dirIndex][0];
                c += directions[dirIndex][1];
                if (r >= 0 && r < rows && c >= 0 && c < cols) {
                    result.push([r, c]);
                }
            }
            dirIndex = (dirIndex + 1) % 4;
        }
        stepSize++;
    }
    return result;
};  