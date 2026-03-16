// Source: https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/   |   Difficulty: Easy
//
// Problem Description:
// Given a m x n matrix grid which is sorted in non-increasing order both row-wise and column-wise, return the number of negative numbers in grid.
//
// Example:
// Input: grid = [[4,3,2,-1],[3,2,1,-1],[1,1,-1,-2],[-1,-1,-2,-3]]
// Output: 8
// Explanation: There are 8 negatives number in the matrix.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100
// 	-100 <= grid[i][j] <= 100
//
//
//  
// Follow up: Could you find an O(n + m) solution?
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var countNegatives = function(grid) {
    let count = 0;
    const rows = grid.length;
    const cols = grid[0].length;
    let row = 0;
    let col = cols - 1;
    while (row < rows && col >= 0) {
        if (grid[row][col] < 0) {
            count += (rows - row);
            col--;
        } else {
            row++;
        }
    }
    return count;
};
