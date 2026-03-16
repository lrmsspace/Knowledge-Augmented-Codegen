// Source: https://leetcode.com/problems/cherry-pickup/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n grid representing a field of cherries, each cell is one of three possible integers.
//
//
// 	0 means the cell is empty, so you can pass through,
// 	1 means the cell contains a cherry that you can pick up and pass through, or
// 	-1 means the cell contains a thorn that blocks your way.
//
//
// Return the maximum number of cherries you can collect by following the rules below:
//
//
// 	Starting at the position (0, 0) and reaching (n - 1, n - 1) by moving right or down through valid path cells (cells with value 0 or 1).
// 	After reaching (n - 1, n - 1), returning to (0, 0) by moving left or up through valid path cells.
// 	When passing through a path cell containing a cherry, you pick it up, and the cell becomes an empty cell 0.
// 	If there is no valid path between (0, 0) and (n - 1, n - 1), then no cherries can be collected.
//
// Example:
// Input: grid = [[0,1,-1],[1,0,-1],[1,1,1]]
// Output: 5
// Explanation: The player started at (0, 0) and went down, down, right right to reach (2, 2).
// 4 cherries were picked up during this single trip, and the matrix becomes [[0,1,-1],[0,0,-1],[0,0,0]].
// Then, the player went left, up, up, left to return home, picking up one more cherry.
// The total number of cherries picked up is 5, and this is the maximum possible.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 50
// 	grid[i][j] is -1, 0, or 1.
// 	grid[0][0] != -1
// 	grid[n - 1][n - 1] != -1
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var cherryPickup = function(grid) {
    const n = grid.length;
    const dp = Array.from({ length: n }, () => Array(n).fill(-Infinity));
    dp[0][0] = grid[0][0];
    for (let k = 1; k < 2 * n - 1; k++) {
        const currentDP = Array.from({ length: n }, () => Array(n).fill(-Infinity));                                            
        for (let x1 = Math.max(0, k - n + 1); x1 <= Math.min(n - 1, k); x1++) {
            for (let x2 = Math.max(0, k - n + 1); x2 <= Math.min(n - 1, k); x2++) {
                const y1 = k - x1;
                const y2 = k - x2;
                if (y1 >= n || y2 >= n || grid[x1][y1] === -1 || grid[x2][y2] === -1) {
                    continue;
                }
                let cherries = grid[x1][y1];
                if (x1 !== x2 || y1 !== y2) {
                    cherries += grid[x2][y2];
                }
                currentDP[x1][x2] = Math.max(currentDP[x1][x2], dp[x1][x2] + cherries);
                if (x1 > 0) {
                    currentDP[x1][x2] = Math.max(currentDP[x1][x2], dp[x1 - 1][x2] + cherries);
                }
                if (x2 > 0) {
                    currentDP[x1][x2] = Math.max(currentDP[x1][x2], dp[x1][x2 - 1] + cherries);
                }
                if (x1 > 0 && x2 > 0) {
                    currentDP[x1][x2] = Math.max(currentDP[x1][x2], dp[x1 - 1][x2 - 1] + cherries);
                }
            }
        }
        for (let x1 = 0; x1 < n; x1++) {
            for (let x2 = 0; x2 < n; x2++) {
                dp[x1][x2] = currentDP[x1][x2];
            }
        }
    }
    return Math.max(0, dp[n - 1][n - 1]);   
    
};
