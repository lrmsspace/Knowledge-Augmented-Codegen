// Source: https://leetcode.com/problems/equal-sum-grid-partition-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
//
//
// 	Each of the two resulting sections formed by the cut is non-empty.
// 	The sum of the elements in both sections is equal.
//
//
// Return true if such a partition exists; otherwise return false.
//
// Example:
// Input: grid = [[1,4],[2,3]]
//
// Output: true
//
// Explanation:
//
//
//
// A horizontal cut between row 0 and row 1 results in two non-empty sections, each with a sum of 5. Thus, the answer is true.
//
// Constraints:
// 1 <= m == grid.length <= 105
// 	1 <= n == grid[i].length <= 105
// 	2 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

/**
 * @param {number[][]} grid
 * @return {boolean}
 */
var canPartitionGrid = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const totalSum = grid.reduce((sum, row) => sum + row.reduce((rowSum, num) => rowSum + num, 0), 0);
    if (totalSum % 2 !== 0) {
        return false;
    }
    const halfSum = totalSum / 2;
    let rowSum = 0;
    for (let i = 0; i < m; i++) {
        rowSum += grid[i].reduce((sum, num) => sum + num, 0);
        if (rowSum === halfSum) {
            return true;
        }
    }
    let colSum = 0;
    for (let j = 0; j < n; j++) {
        colSum += grid.reduce((sum, row) => sum + row[j], 0);
        if (colSum === halfSum) {
            return true;
        }
    }
    return false;   
};
