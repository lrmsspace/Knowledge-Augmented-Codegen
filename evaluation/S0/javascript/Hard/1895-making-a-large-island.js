// Source: https://leetcode.com/problems/making-a-large-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
//
// Return the size of the largest island in grid after applying this operation.
//
// An island is a 4-directionally connected group of 1s.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 500
// 	grid[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var largestIsland = function(grid) {
    const n = grid.length;
    const islandSize = new Map();
    let islandId = 2;
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const dfs = (x, y, id) => {
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] !== 1) {
            return 0;
        }
        grid[x][y] = id;
        let size = 1;
        for (const [dx, dy] of directions) {
            size += dfs(x + dx, y + dy, id);
        }
        return size;
    }
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                const size = dfs(i, j, islandId);
                islandSize.set(islandId, size);
                islandId++;
            }
        }
    }
    let maxSize = 0;
    for (const size of islandSize.values()) {
        maxSize = Math.max(maxSize, size);
    }
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 0) {
                const seen = new Set();
                let size = 1;
                for (const [dx, dy] of directions) {
                    const x = i + dx;
                    const y = j + dy;
                    if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] > 1) {
                        const id = grid[x][y];
                        if (!seen.has(id)) {
                            seen.add(id);
                            size += islandSize.get(id);
                        }
                    }
                }
                maxSize = Math.max(maxSize, size);
            }
        }
    }
    return maxSize;
};
