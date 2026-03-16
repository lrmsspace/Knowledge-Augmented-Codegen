// Source: https://leetcode.com/problems/count-servers-that-communicate/   |   Difficulty: Medium
//
// Problem Description:
// You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server. Two servers are said to communicate if they are on the same row or on the same column.
//
// Return the number of servers that communicate with any other server.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 0
// Explanation: No servers can communicate with others.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m <= 250
// 	1 <= n <= 250
// 	grid[i][j] == 0 or 1
//

/**
 * @param {number[][]} grid
 * @return {number}
 */
var countServers = function(grid) {
    
    const rows = new Array(grid.length).fill(0);
    const cols = new Array(grid[0].length).fill(0);
    let count = 0;
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            if (grid[i][j] === 1) {
                rows[i]++;
                cols[j]++;
                count++;
            }
        }
    }
    for (let i = 0; i < grid.length; i++) {
        for (let j = 0; j < grid[0].length; j++) {
            if (grid[i][j] === 1 && rows[i] === 1 && cols[j] === 1) {
                count--;
            }
        }
    }
    return count;
    
};
