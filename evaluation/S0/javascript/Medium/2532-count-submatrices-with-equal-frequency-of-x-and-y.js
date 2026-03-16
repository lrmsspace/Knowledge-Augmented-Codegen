// Source: https://leetcode.com/problems/count-submatrices-with-equal-frequency-of-x-and-y/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D character matrix grid, where grid[i][j] is either 'X', 'Y', or '.', return the number of submatrices that contain:
//
//
// 	grid[0][0]
// 	an equal frequency of 'X' and 'Y'.
// 	at least one 'X'.
//
// Example:
// Input: grid = [["X","Y","."],["Y",".","."]]
//
// Output: 3
//
// Explanation:
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 1000
// 	grid[i][j] is either 'X', 'Y', or '.'.
//

/**
 * @param {character[][]} grid
 * @return {number}
 */
var numberOfSubmatrices = function(grid) {
    const rows = grid.length;
    const cols = grid[0].length;
    let count = 0;
    for (let top = 0; top < rows; top++) {
        const freq = new Map();
        for (let bottom = top; bottom < rows; bottom++) {   
            for (let col = 0; col < cols; col++) {
                const char = grid[bottom][col];
                if (char === 'X' || char === 'Y') {
                    freq.set(char, (freq.get(char) || 0) + 1);
                }
            }   
            if (freq.get('X') > 0 && freq.get('X') === freq.get('Y')) {
                count++;
            }
        }
    }
    return count;
};
