// Source: https://leetcode.com/problems/prison-cells-after-n-days/   |   Difficulty: Medium
//
// Problem Description:
// There are 8 prison cells in a row and each cell is either occupied or vacant.
//
// Each day, whether the cell is occupied or vacant changes according to the following rules:
//
//
// 	If a cell has two adjacent neighbors that are both occupied or both vacant, then the cell becomes occupied.
// 	Otherwise, it becomes vacant.
//
//
// Note that because the prison is a row, the first and the last cells in the row can't have two adjacent neighbors.
//
// You are given an integer array cells where cells[i] == 1 if the ith cell is occupied and cells[i] == 0 if the ith cell is vacant, and you are given an integer n.
//
// Return the state of the prison after n days (i.e., n such changes described above).
//
// Example:
// Input: cells = [0,1,0,1,1,0,0,1], n = 7
// Output: [0,0,1,1,0,0,0,0]
// Explanation: The following table summarizes the state of the prison on each day:
// Day 0: [0, 1, 0, 1, 1, 0, 0, 1]
// Day 1: [0, 1, 1, 0, 0, 0, 0, 0]
// Day 2: [0, 0, 0, 0, 1, 1, 1, 0]
// Day 3: [0, 1, 1, 0, 0, 1, 0, 0]
// Day 4: [0, 0, 0, 0, 0, 1, 0, 0]
// Day 5: [0, 1, 1, 1, 0, 1, 0, 0]
// Day 6: [0, 0, 1, 0, 1, 1, 0, 0]
// Day 7: [0, 0, 1, 1, 0, 0, 0, 0]
//
// Constraints:
// cells.length == 8
// 	cells[i] is either 0 or 1.
// 	1 <= n <= 109
//

/**
 * @param {number[]} cells
 * @param {number} n
 * @return {number[]}
 */
var prisonAfterNDays = function(cells, n) {
    const seen = new Map();
    let isCycleDetected = false;
    let cycleLength = 0;
    for (let day = 0; day < n; day++) {
        const nextCells = new Array(8).fill(0);
        for (let i = 1; i < 7; i++) {
            nextCells[i] = cells[i - 1] === cells[i + 1] ? 1 : 0;
        }
        const stateKey = nextCells.join('');
        if (seen.has(stateKey)) {
            isCycleDetected = true;
            cycleLength = day - seen.get(stateKey);
            break;
        } else {
            seen.set(stateKey, day);
            cells = nextCells;
        }
    }
    if (isCycleDetected) {
        const remainingDays = (n - seen.size) % cycleLength;
        for (let day = 0; day < remainingDays; day++) {
            const nextCells = new Array(8).fill(0);
            for (let i = 1; i < 7; i++) {
                nextCells[i] = cells[i - 1] === cells[i + 1] ? 1 : 0;
            }
            cells = nextCells;
        }
    }
    return cells;
        
};
