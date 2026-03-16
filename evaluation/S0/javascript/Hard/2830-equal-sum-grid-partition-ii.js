// Source: https://leetcode.com/problems/equal-sum-grid-partition-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n matrix grid of positive integers. Your task is to determine if it is possible to make either one horizontal or one vertical cut on the grid such that:
//
//
// 	Each of the two resulting sections formed by the cut is non-empty.
// 	The sum of elements in both sections is equal, or can be made equal by discounting at most one single cell in total (from either section).
// 	If a cell is discounted, the rest of the section must remain connected.
//
//
// Return true if such a partition exists; otherwise, return false.
//
// Note: A section is connected if every cell in it can be reached from any other cell by moving up, down, left, or right through other cells in the section.
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
//
// 	A horizontal cut after the first row gives sums 1 + 4 = 5 and 2 + 3 = 5, which are equal. Thus, the answer is true.
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
    const totalSum = grid.flat().reduce((a, b) => a + b, 0);
    const canPartition = (isHorizontal) => {
        let prefixSum = 0;
        for (let i = 0; i < (isHorizontal ? m : n) - 1; i++) {
            prefixSum += isHorizontal ? grid[i].reduce((a, b) => a + b, 0) : grid.reduce((a, b) => a + b[i], 0);
            const otherSum = totalSum - prefixSum;
            if (prefixSum === otherSum) {
                return true;
            }
            if (Math.abs(prefixSum - otherSum) <= Math.max(...(isHorizontal ? grid[i] : grid.map(row => row[i])))) {
                return true;
            }
        }
        return false;
    }
    return canPartition(true) || canPartition(false);
};
