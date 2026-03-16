// Source: https://leetcode.com/problems/find-the-safest-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:
//
//
// 	A cell containing a thief if grid[r][c] = 1
// 	An empty cell if grid[r][c] = 0
//
//
// You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.
//
// The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.
//
// Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).
//
// An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.
//
// The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.
//
// Example:
// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
// Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
//
// Constraints:
// 1 <= grid.length == n <= 400
// 	grid[i].length == n
// 	grid[i][j] is either 0 or 1.
// 	There is at least one thief in the grid.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maximumSafenessFactor = function(grid) {
    const n = grid.length;
    const directions = [
        [0, 1],
        [1, 0],
        [0, -1],
        [-1, 0]
    ];
    const distanceGrid = Array.from({ length: n }, () => Array(n).fill(Infinity));
    const queue = [];
    for (let r = 0; r < n; r++) {
        for (let c = 0; c < n; c++) {
            if (grid[r][c] === 1) {
                distanceGrid[r][c] = 0;
                queue.push([r, c]);
            }
        }
    }
    while (queue.length) {
        const [r, c] = queue.shift();
        for (const [dr, dc] of directions) {
            const nr = r + dr;
            const nc = c + dc;
            if (nr >= 0 && nr < n && nc >= 0 && nc < n) {
                if (distanceGrid[nr][nc] > distanceGrid[r][c] + 1) {
                    distanceGrid[nr][nc] = distanceGrid[r][c] + 1;
                    queue.push([nr, nc]);
                }
            }
        }   
    }
    const maxHeap = [[distanceGrid[0][0], 0, 0]];
    const visited = Array.from({ length: n }, () => Array(n).fill(false));
    visited[0][0] = true;
    while (maxHeap.length) {
        maxHeap.sort((a, b) => b[0] - a[0]);
        const [safeness, r, c] = maxHeap.shift();
        if (r === n - 1 && c === n - 1) {
            return safeness;
        }
        for (const [dr, dc] of directions) {
            const nr = r + dr;
            const nc = c + dc;
            if (nr >= 0 && nr < n && nc >= 0 && nc < n && !visited[nr][nc]) {
                visited[nr][nc] = true;
                maxHeap.push([Math.min(safeness, distanceGrid[nr][nc]), nr, nc]);
            }
        }   
    }
    return -1;  
};
