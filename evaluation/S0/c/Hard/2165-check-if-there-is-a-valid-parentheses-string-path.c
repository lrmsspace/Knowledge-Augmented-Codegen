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

bool hasValidPath(char** grid, int gridSize, int* gridColSize) {
    if (!grid || gridSize == 0 || !gridColSize || gridColSize[0] == 0) return false;
    int m = gridSize, n = gridColSize[0];
    if ((m + n - 1) % 2 != 0) return false; /* odd length cannot be valid */

    /* dp[i][j]: bitmask of possible open counts at (i,j) */
    unsigned short dp[m][n];
    memset(dp, 0, sizeof(dp));
    dp[0][0] = (grid[0][0] == '(') ? 1 : 0;

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == 0 && j == 0) continue;
            unsigned short bits = 0;
            if (i > 0) bits |= dp[i - 1][j];
            if (j > 0) bits |= dp[i][j - 1];
            unsigned short newBits = 0;
            for (int k = 0; k <= m + n - 2; ++k) {
                if ((bits & (1 << k)) != 0) {
                    if (grid[i][j] == '(') {
                        newBits |= (1 << (k + 1));
                    } else {
                        if (k > 0) newBits |= (1 << (k - 1));
                    }
                }
            }
            dp[i][j] = newBits;
        }
    }
    return (dp[m - 1][n - 1] & 1) != 0;     
}
