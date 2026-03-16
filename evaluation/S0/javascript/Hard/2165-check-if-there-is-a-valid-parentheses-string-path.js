// Source: https://leetcode.com/problems/check-if-there-is-a-valid-parentheses-string-path/   |   Difficulty: Hard
//
// Problem Description:
// A parentheses string is a non-empty string consisting only of '(' and ')'. It is valid if any of the following conditions is true:
//
//
// 	It is ().
// 	It can be written as AB (A concatenated with B), where A and B are valid parentheses strings.
// 	It can be written as (A), where A is a valid parentheses string.
//
//
// You are given an m x n matrix of parentheses grid. A valid parentheses string path in the grid is a path satisfying all of the following conditions:
//
//
// 	The path starts from the upper left cell (0, 0).
// 	The path ends at the bottom-right cell (m - 1, n - 1).
// 	The path only ever moves down or right.
// 	The resulting parentheses string formed by the path is valid.
//
//
// Return true if there exists a valid parentheses string path in the grid. Otherwise, return false.
//
// Example:
// Input: grid = [["(","(","("],[")","(",")"],["(","(",")"],["(","(",")"]]
// Output: true
// Explanation: The above diagram shows two possible paths that form valid parentheses strings.
// The first path shown results in the valid parentheses string "()(())".
// The second path shown results in the valid parentheses string "((()))".
// Note that there may be other valid parentheses string paths.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 100
// 	grid[i][j] is either '(' or ')'.
//

/**
 * @param {character[][]} grid
 * @return {boolean}
 */
var hasValidPath = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const dp = new Array(m).fill(0).map(() => new Array(n).fill(new Set()));
    dp[0][0].add(grid[0][0] === '(' ? 1 : -1);
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (i === 0 && j === 0) continue;
            const currentSet = new Set();
            if (i > 0) {
                for (const count of dp[i - 1][j]) {
                    const newCount = count + (grid[i][j] === '(' ? 1 : -1);
                    if (newCount >= 0) {
                        currentSet.add(newCount);
                    }
                }
            }
            if (j > 0) {
                for (const count of dp[i][j - 1]) {
                    const newCount = count + (grid[i][j] === '(' ? 1 : -1);
                    if (newCount >= 0) {
                        currentSet.add(newCount);
                    }
                }
            }
            dp[i][j] = currentSet;
        }
    }
    return dp[m - 1][n - 1].has(0);
};
