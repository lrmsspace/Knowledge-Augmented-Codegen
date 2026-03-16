// Source: https://leetcode.com/problems/largest-magic-square/   |   Difficulty: Medium
//
// Problem Description:
// A k x k magic square is a k x k grid filled with integers such that every row sum, every column sum, and both diagonal sums are all equal. The integers in the magic square do not have to be distinct. Every 1 x 1 grid is trivially a magic square.
//
// Given an m x n integer grid, return the size (i.e., the side length k) of the largest magic square that can be found within this grid.
//
// Example:
// Input: grid = [[7,1,4,5,6],[2,5,1,6,4],[1,5,4,3,2],[1,2,7,3,4]]
// Output: 3
// Explanation: The largest magic square has a size of 3.
// Every row sum, column sum, and diagonal sum of this magic square is equal to 12.
// - Row sums: 5+1+6 = 5+4+3 = 2+7+3 = 12
// - Column sums: 5+5+2 = 1+4+7 = 6+3+3 = 12
// - Diagonal sums: 5+4+3 = 6+4+2 = 12
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j] <= 106
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var largestMagicSquare = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    let maxSize = 1;

    // Precompute prefix sums for rows and columns
    const rowPrefixSums = Array.from({ length: m }, () => Array(n + 1).fill(0));
    const colPrefixSums = Array.from({ length: m + 1 }, () => Array(n).fill(0));
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            rowPrefixSums[i][j + 1] = rowPrefixSums[i][j] + grid[i][j];
            colPrefixSums[i + 1][j] = colPrefixSums[i][j] + grid[i][j];
        }
    }

    const isMagicSquare = (x, y, size) => {
        const targetSum = rowPrefixSums[x][y + size] - rowPrefixSums[x][y];
        let diagSum1 = 0;
        let diagSum2 = 0;
        for (let i = 0; i < size; i++) {
            const rowSum = rowPrefixSums[x + i][y + size] - rowPrefixSums[x + i][y];
            const colSum = colPrefixSums[x + size][y + i] - colPrefixSums[x][y + i];
            if (rowSum !== targetSum || colSum !== targetSum) return false;
            diagSum1 += grid[x + i][y + i];
            diagSum2 += grid[x + i][y + size - 1 - i];
        }
        return diagSum1 === targetSum && diagSum2 === targetSum;
    };
    for (let size = 2; size <= Math.min(m, n); size++) {    
        for (let i = 0; i <= m - size; i++) {
            for (let j = 0; j <= n - size; j++) {
                if (isMagicSquare(i, j, size)) {
                    maxSize = size;
                }
            }
        }
    }
    return maxSize; 
};
