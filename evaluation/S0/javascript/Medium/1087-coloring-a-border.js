// Source: https://leetcode.com/problems/coloring-a-border/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid, and three integers row, col, and color. Each value in the grid represents the color of the grid square at that location.
//
// Two squares are called adjacent if they are next to each other in any of the 4 directions.
//
// Two squares belong to the same connected component if they have the same color and they are adjacent.
//
// The border of a connected component is all the squares in the connected component that are either adjacent to (at least) a square not in the component, or on the boundary of the grid (the first or last row or column).
//
// You should color the border of the connected component that contains the square grid[row][col] with color.
//
// Return the final grid.
//
// Example:
// Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
// Output: [[3,3],[3,2]]
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j], color <= 1000
// 	0 <= row < m
// 	0 <= col < n
//

/**
 * @param {number[][]} grid
 * @param {number} row
 * @param {number} col
 * @param {number} color
 * @return {number[][]}
 */
var colorBorder = function(grid, row, col, color) {
    const m = grid.length;
    const n = grid[0].length;
    const originalColor = grid[row][col];
    const visited = Array.from({ length: m }, () => Array(n).fill(false));
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const borderCells = [];
    function isBorder(r, c) {
        if (r === 0 || r === m - 1 || c === 0 || c === n - 1) {
            return true;
        }
        for (const [dr, dc] of directions) {
            const newRow = r + dr;
            const newCol = c + dc;
            if (newRow < 0 || newRow >= m || newCol < 0 || newCol >= n ||
                grid[newRow][newCol] !== originalColor) {
                return true;
            }
        }
        return false;
    }
    function dfs(r, c) {
        visited[r][c] = true;
        if (isBorder(r, c)) {
            borderCells.push([r, c]);
        }
        for (const [dr, dc] of directions) {
            const newRow = r + dr;
            const newCol = c + dc;
            if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n &&
                !visited[newRow][newCol] && grid[newRow][newCol] === originalColor) {
                dfs(newRow, newCol);
            }
        }   
    }
    dfs(row, col);
    for (const [r, c] of borderCells) {
        grid[r][c] = color;
    }
    return grid;
                
};
