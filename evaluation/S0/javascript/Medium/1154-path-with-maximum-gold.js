// Source: https://leetcode.com/problems/path-with-maximum-gold/   |   Difficulty: Medium
//
// Problem Description:
// In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
//
// Return the maximum amount of gold you can collect under the conditions:
//
//
// 	Every time you are located in a cell you will collect all the gold in that cell.
// 	From your position, you can walk one step to the left, right, up, or down.
// 	You can't visit the same cell more than once.
// 	Never visit a cell with 0 gold.
// 	You can start and stop collecting gold from any position in the grid that has some gold.
//
// Example:
// Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
// Output: 24
// Explanation:
// [[0,6,0],
//  [5,8,7],
//  [0,9,0]]
// Path to get the maximum gold, 9 -> 8 -> 7.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	0 <= grid[i][j] <= 100
// 	There are at most 25 cells containing gold.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var getMaximumGold = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;
    let maxGold = 0;
    const directions = [
        [0, 1],  // right
        [1, 0],  // down
        [0, -1], // left
        [-1, 0]  // up
    ];
    const dfs = (x, y, currentGold) => {
        maxGold = Math.max(maxGold, currentGold);
        const temp = grid[x][y];
        grid[x][y] = 0; // mark as visited
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && grid[newX][newY] > 0) {
                dfs(newX, newY, currentGold + grid[newX][newY]);
            }
        }
        grid[x][y] = temp; // backtrack
    };
    for (let i = 0; i < rows; i++) {
        for (let j = 0; j < cols; j++) {
            if (grid[i][j] > 0) {
                dfs(i, j, grid[i][j]);
            }
        }
    }
    return maxGold;
        
};
