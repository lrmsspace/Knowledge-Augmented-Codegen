// Source: https://leetcode.com/problems/maximum-trailing-zeros-in-a-cornered-path/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array grid of size m x n, where each cell contains a positive integer.
//
// A cornered path is defined as a set of adjacent cells with at most one turn. More specifically, the path should exclusively move either horizontally or vertically up to the turn (if there is one), without returning to a previously visited cell. After the turn, the path will then move exclusively in the alternate direction: move vertically if it moved horizontally, and vice versa, also without returning to a previously visited cell.
//
// The product of a path is defined as the product of all the values in the path.
//
// Return the maximum number of trailing zeros in the product of a cornered path found in grid.
//
// Note:
//
//
// 	Horizontal movement means moving in either the left or right direction.
// 	Vertical movement means moving in either the up or down direction.
//
// Example:
// Input: grid = [[23,17,15,3,20],[8,1,20,27,11],[9,4,6,2,21],[40,9,1,10,6],[22,7,4,5,3]]
// Output: 3
// Explanation: The grid on the left shows a valid cornered path.
// It has a product of 15 * 20 * 6 * 1 * 10 = 18000 which has 3 trailing zeros.
// It can be shown that this is the maximum trailing zeros in the product of a cornered path.
//
// The grid in the middle is not a cornered path as it has more than one turn.
// The grid on the right is not a cornered path as it requires a return to a previously visited cell.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 1000
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxTrailingZeros = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const countFactors = (num, factor) => {
        let count = 0;
        while (num % factor === 0) {
            count++;
            num /= factor;
        }
        return count;
    }
    const prefix2 = Array.from({ length: m + 1 }, () => Array(n + 1).fill(0));
    const prefix5 = Array.from({ length: m + 1 }, () => Array(n + 1).fill(0));
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const count2 = countFactors(grid[i][j], 2);
            const count5 = countFactors(grid[i][j], 5);
            prefix2[i + 1][j + 1] = prefix2[i + 1][j] + count2;
            prefix5[i + 1][j + 1] = prefix5[i + 1][j] + count5;
        }
    }
    for (let j = 0; j < n; j++) {
        for (let i = 0; i < m; i++) {
            prefix2[i + 1][j + 1] += prefix2[i][j + 1];
            prefix5[i + 1][j + 1] += prefix5[i][j + 1];
        }
    }
    let maxZeros = 0;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const count2 = countFactors(grid[i][j], 2);
            const count5 = countFactors(grid[i][j], 5);
            const top2 = prefix2[i][j + 1];
            const top5 = prefix5[i][j + 1];
            const bottom2 = prefix2[m][j + 1] - prefix2[i + 1][j + 1];
            const bottom5 = prefix5[m][j + 1] - prefix5[i + 1][j + 1];
            const left2 = prefix2[i + 1][j];
            const left5 = prefix5[i + 1][j];
            const right2 = prefix2[i + 1][n] - prefix2[i + 1][j + 1];
            const right5 = prefix5[i + 1][n] - prefix5[i + 1][j + 1];   
            const paths = [
                [top2 + left2 + count2, top5 + left5 + count5],
                [top2 + right2 + count2, top5 + right5 + count5],
                [bottom2 + left2 + count2, bottom5 + left5 + count5],
                [bottom2 + right2 + count2, bottom5 + right5 + count5],
            ];
            for (const [total2, total5] of paths) {
                maxZeros = Math.max(maxZeros, Math.min(total2, total5));
            }
        }
    }
    return maxZeros;    
};
