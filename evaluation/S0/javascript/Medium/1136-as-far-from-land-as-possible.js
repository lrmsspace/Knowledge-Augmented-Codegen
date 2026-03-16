// Source: https://leetcode.com/problems/as-far-from-land-as-possible/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.
//
// The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
//
// Example:
// Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
// Output: 2
// Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var maxDistance = function(grid) {
    const n = grid.length;
    const queue = [];
    const directions = [[1,0], [-1,0], [0,1], [0,-1]];
    const visited = Array.from({ length: n }, () => Array(n).fill(false));
        
    // Enqueue all land cells
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                queue.push([i, j]);
                visited[i][j] = true;
            }
        }
    }
    if (queue.length === 0 || queue.length === n * n) return -1;
    let distance = -1;
    while (queue.length > 0) {
        const size = queue.length;
        distance++;
        for (let i = 0; i < size; i++) {
            const [x, y] = queue.shift();
            for (const [dx, dy] of directions) {
                const newX = x + dx;
                const newY = y + dy;
                if (newX >= 0 && newX < n && newY >= 0 && newY < n && !visited[newX][newY] && grid[newX][newY] === 0) {
                    visited[newX][newY] = true;
                    queue.push([newX, newY]);
                }
            }
        }
    }
    return distance;    
        
};
