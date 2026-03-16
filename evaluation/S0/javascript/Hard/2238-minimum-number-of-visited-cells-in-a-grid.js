// Source: https://leetcode.com/problems/minimum-number-of-visited-cells-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed m x n integer matrix grid. Your initial position is at the top-left cell (0, 0).
//
// Starting from the cell (i, j), you can move to one of the following cells:
//
//
// 	Cells (i, k) with j < k <= grid[i][j] + j (rightward movement), or
// 	Cells (k, j) with i < k <= grid[i][j] + i (downward movement).
//
//
// Return the minimum number of cells you need to visit to reach the bottom-right cell (m - 1, n - 1). If there is no valid path, return -1.
//
// Example:
// Input: grid = [[3,4,2,1],[4,2,3,1],[2,1,0,0],[2,4,0,0]]
// Output: 4
// Explanation: The image above shows one of the paths that visits exactly 4 cells.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 105
// 	1 <= m * n <= 105
// 	0 <= grid[i][j] < m * n
// 	grid[m - 1][n - 1] == 0
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var minimumVisitedCells = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const directions = [[1, 0], [0, 1]];
    const visited = Array.from({ length: m }, () => new Array(n).fill(false));
    const pq = new MinPriorityQueue({ priority: x => x[2] });
    pq.enqueue([0, 0, 1]);
    visited[0][0] = true;
    while (!pq.isEmpty()) {
        const [x, y, steps] = pq.dequeue().element;
        if (x === m - 1 && y === n - 1) {
            return steps;
        }
        for (const [dx, dy] of directions) {
            const newX = x + dx;
            const newY = y + dy;
            if (newX < m && newY < n && !visited[newX][newY]) {
                const maxSteps = grid[x][y];
                if (dx === 1) {
                    for (let k = y + 1; k <= Math.min(n - 1, y + maxSteps); k++) {
                        if (!visited[x][k]) {
                            pq.enqueue([x, k, steps + 1]);
                            visited[x][k] = true;
                        }
                    }
                } else {
                    for (let k = x + 1; k <= Math.min(m - 1, x + maxSteps); k++) {
                        if (!visited[k][y]) {
                            pq.enqueue([k, y, steps + 1]);
                            visited[k][y] = true;
                        }
                    }
                }
            }
        }
    }
    return -1;
};
