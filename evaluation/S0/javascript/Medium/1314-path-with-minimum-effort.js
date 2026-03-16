// Source: https://leetcode.com/problems/path-with-minimum-effort/   |   Difficulty: Medium
//
// Problem Description:
// You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
//
// A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
//
// Return the minimum effort required to travel from the top-left cell to the bottom-right cell.
//
// Example:
// Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
// Output: 2
// Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
// This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.
//
// Constraints:
// rows == heights.length
// 	columns == heights[i].length
// 	1 <= rows, columns <= 100
// 	1 <= heights[i][j] <= 106
//

/**
 * @param {number[][]} heights
 * @return {number}
 */
var minimumEffortPath = function(heights) {
    const rows = heights.length;
    const cols = heights[0].length;
    const directions = [[0,1],[1,0],[0,-1],[-1,0]];
    const canReach = (effort) => {
        const visited = Array.from({ length: rows }, () => Array(cols).fill(false));
        const queue = [[0, 0]];
        visited[0][0] = true;
        while (queue.length) {
            const [x, y] = queue.shift();
            if (x === rows - 1 && y === cols - 1) return true;
            for (const [dx, dy] of directions) {
                const nx = x + dx;
                const ny = y + dy;
                if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny]) {
                    const diff = Math.abs(heights[nx][ny] - heights[x][y]);
                    if (diff <= effort) {
                        visited[nx][ny] = true;
                        queue.push([nx, ny]);
                    }
                }
            }
        }
        return false;
    };
    let left = 0;
    let right = 1e6;
    let result = 0;
    while (left <= right) {
        const mid = Math.floor((left + right) / 2);
        if (canReach(mid)) {
            result = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return result;
};  