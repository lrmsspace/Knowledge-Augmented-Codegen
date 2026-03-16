// Source: https://leetcode.com/problems/check-if-there-is-a-valid-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid. Each cell of grid represents a street. The street of grid[i][j] can be:
//
//
// 	1 which means a street connecting the left cell and the right cell.
// 	2 which means a street connecting the upper cell and the lower cell.
// 	3 which means a street connecting the left cell and the lower cell.
// 	4 which means a street connecting the right cell and the lower cell.
// 	5 which means a street connecting the left cell and the upper cell.
// 	6 which means a street connecting the right cell and the upper cell.
//
//
// You will initially start at the street of the upper-left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should only follow the streets.
//
// Notice that you are not allowed to change any street.
//
// Return true if there is a valid path in the grid or false otherwise.
//
// Example:
// Input: grid = [[2,4,3],[6,5,2]]
// Output: true
// Explanation: As shown you can start at cell (0, 0) and visit all the cells of the grid to reach (m - 1, n - 1).
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 300
// 	1 <= grid[i][j] <= 6
//

/**
 * @param {number[][]} grid
 * @return {boolean}
 */
var hasValidPath = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const directions = {
        1: [[0, -1], [0, 1]],
        2: [[-1, 0], [1, 0]],
        3: [[0, -1], [1, 0]],
        4: [[0, 1], [1, 0]],
        5: [[0, -1], [-1, 0]],
        6: [[0, 1], [-1, 0]],
    };
    const opposite = {
        '0,1': [0, -1],
        '0,-1': [0, 1],
        '1,0': [-1, 0],
        '-1,0': [1, 0],
    };
    const visited = Array.from({ length: m }, () => Array(n).fill(false));
    const dfs = (x, y) => {
        if (x === m - 1 && y === n - 1) return true;
        visited[x][y] = true;
        for (const [dx, dy] of directions[grid[x][y]]) {
            const nx = x + dx;
            const ny = y + dy;
            if (nx >= 0 && nx < m && ny >= 0 && ny < n && !visited[nx][ny]) {
                const [odx, ody] = opposite[`${-dx},${-dy}`];
                if (directions[grid[nx][ny]].some(([ddx, ddy]) => ddx === odx && ddy === ody)) {
                    if (dfs(nx, ny)) return true;
                }
            }
        }
        return false;
    }   
    return dfs(0, 0);   
            
};
