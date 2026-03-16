// Source: https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid where each cell is either 0 (empty) or 1 (obstacle). You can move up, down, left, or right from and to an empty cell in one step.
//
// Return the minimum number of steps to walk from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1) given that you can eliminate at most k obstacles. If it is not possible to find such walk return -1.
//
// Example:
// Input: grid = [[0,0,0],[1,1,0],[0,0,0],[0,1,1],[0,0,0]], k = 1
// Output: 6
// Explanation: 
// The shortest path without eliminating any obstacle is 10.
// The shortest path with one obstacle elimination at position (3,2) is 6. Such path is (0,0) -> (0,1) -> (0,2) -> (1,2) -> (2,2) -> (3,2) -> (4,2).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 40
// 	1 <= k <= m * n
// 	grid[i][j] is either 0 or 1.
// 	grid[0][0] == grid[m - 1][n - 1] == 0
//

/**
 * @param {number[][]} grid
 * @param {number} k
 * @return {number}
 */
var shortestPath = function(grid, k) {
    const m = grid.length;
    const n = grid[0].length;
    const queue = [];
    const visited = new Set();
    const target = (m - 1) << 16 | (n - 1);
    queue.push((0 << 16) | (0 << 8) | 0);  
    visited.add((0 << 16) | (0 << 8) | 0);
    let steps = 0;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];

    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const state = queue.shift();
            const x = (state >> 16) & 0xFF;
            const y = (state >> 8) & 0xFF;
            const obstaclesEliminated = state & 0xFF;
            if ((state >> 8) === target) {
                return steps;
            }
            for (const [dx, dy] of directions) {
                const nextX = x + dx;
                const nextY = y + dy;
                if (nextX >= 0 && nextX < m && nextY >= 0 && nextY < n) {
                    const nextObstaclesEliminated = obstaclesEliminated + grid[nextX][nextY];
                    if (nextObstaclesEliminated <= k) {
                        const nextState = (nextX << 16) | (nextY << 8) | nextObstaclesEliminated;
                        if (!visited.has(nextState)) {
                            visited.add(nextState);
                            queue.push(nextState);
                        }
                    }
                }
            }
        }
        steps++;
    }
    return -1;  
};
