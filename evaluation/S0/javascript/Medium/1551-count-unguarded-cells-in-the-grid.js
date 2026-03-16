// Source: https://leetcode.com/problems/count-unguarded-cells-in-the-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.
//
// A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.
//
// Return the number of unoccupied cells that are not guarded.
//
// Example:
// Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
// Output: 7
// Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
// There are a total of 7 unguarded cells, so we return 7.
//
// Constraints:
// 1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	1 <= guards.length, walls.length <= 5 * 104
// 	2 <= guards.length + walls.length <= m * n
// 	guards[i].length == walls[j].length == 2
// 	0 <= rowi, rowj < m
// 	0 <= coli, colj < n
// 	All the positions in guards and walls are unique.
//

/**
 * @param {number} m
 * @param {number} n
 * @param {number[][]} guards
 * @param {number[][]} walls
 * @return {number}
 */
var countUnguarded = function(m, n, guards, walls) {
    const grid = Array.from({ length: m }, () => Array(n).fill(0));
    for (const [x, y] of walls) {
        grid[x][y] = -1; // wall
    }
    for (const [x, y] of guards) {
        grid[x][y] = 1; // guard
    }
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    for (const [gx, gy] of guards) {
        for (const [dx, dy] of directions) {
            let x = gx + dx;
            let y = gy + dy;
            while (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] === 0) {
                grid[x][y] = 2; // guarded
                x += dx;
                y += dy;
            }
        }
    }
    let count = 0;
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 0) {
                count++;
            }
        }
    }
    return count;
};