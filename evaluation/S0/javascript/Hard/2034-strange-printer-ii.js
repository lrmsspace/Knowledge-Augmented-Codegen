// Source: https://leetcode.com/problems/strange-printer-ii/   |   Difficulty: Hard
//
// Problem Description:
// There is a strange printer with the following two special requirements:
//
//
// 	On each turn, the printer will print a solid rectangular pattern of a single color on the grid. This will cover up the existing colors in the rectangle.
// 	Once the printer has used a color for the above operation, the same color cannot be used again.
//
//
// You are given a m x n matrix targetGrid, where targetGrid[row][col] is the color in the position (row, col) of the grid.
//
// Return true if it is possible to print the matrix targetGrid, otherwise, return false.
//
// Example:
// Input: targetGrid = [[1,1,1,1],[1,2,2,1],[1,2,2,1],[1,1,1,1]]
// Output: true
//
// Constraints:
// m == targetGrid.length
// 	n == targetGrid[i].length
// 	1 <= m, n <= 60
// 	1 <= targetGrid[row][col] <= 60
//

/**
 * @param {number[][]} targetGrid
 * @return {boolean}
 */
var isPrintable = function(targetGrid) {
    const m = targetGrid.length;
    const n = targetGrid[0].length;
    const colors = new Set();
    const colorBounds = new Map();
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            const color = targetGrid[i][j];
            colors.add(color);
            if (!colorBounds.has(color)) {
                colorBounds.set(color, [i, i, j, j]);
            } else {
                const bounds = colorBounds.get(color);
                bounds[0] = Math.min(bounds[0], i);
                bounds[1] = Math.max(bounds[1], i);
                bounds[2] = Math.min(bounds[2], j);
                bounds[3] = Math.max(bounds[3], j);
            }
        }
    }
    const graph = new Map();
    for (const color of colors) {
        graph.set(color, new Set());
    }
    for (const color of colors) {
        const [top, bottom, left, right] = colorBounds.get(color);
        for (let i = top; i <= bottom; i++) {
            for (let j = left; j <= right; j++) {
                if (targetGrid[i][j] !== color) {
                    graph.get(color).add(targetGrid[i][j]);
                }
            }
        }
    }
    const visited = new Set();
    const dfs = (color) => {
        if (visited.has(color)) return false;
        visited.add(color);
        for (const neighbor of graph.get(color)) {
            if (!dfs(neighbor)) {
                return false;
            }
        }
        return true;
    };
    for (const color of colors) {
        if (!visited.has(color)) {
            if (!dfs(color)) {
                return false;
            }
        }
    }
    return true;    
};
