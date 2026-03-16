// Source: https://leetcode.com/problems/shortest-bridge/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n binary matrix grid where 1 represents land and 0 represents water.
//
// An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.
//
// You may change 0's to 1's to connect the two islands to form one island.
//
// Return the smallest number of 0's you must flip to connect the two islands.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 1
//
// Constraints:
// n == grid.length == grid[i].length
// 	2 <= n <= 100
// 	grid[i][j] is either 0 or 1.
// 	There are exactly two islands in grid.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var shortestBridge = function(grid) {
    const n = grid.length;
    const directions = [[1,0], [-1,0], [0,1], [0,-1]];
    const visited = Array.from({ length: n }, () => Array(n).fill(false));
    const queue = [];
    let found = false;
    const dfs = (x, y) => {
        if (x < 0 || x >= n || y < 0 || y >= n || visited[x][y] || grid[x][y] === 0) {
            return;
                

       
        visited[x][y] = true;
        queue.push([x, y]);
        for (const [dx, dy] of directions) {
            dfs(x + dx, y + dy);
        }
    };

    for (let i = 0; i < n; i++) {
        if (found) break;
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                dfs(i, j);
                found = true;
                break;
            }
        }
    }
    let steps = 0;
    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const [x, y] = queue.shift();
            for (const [dx, dy] of directions) {    
                const nx = x + dx;
                const ny = y + dy;  
                if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny]) {
                    if (grid[nx][ny] === 1) {
                        return steps;
                    }
                    visited[nx][ny] = true;
                    queue.push([nx, ny]);
                }
            }
        }
        steps++;
    }
    return -1;
}

};
