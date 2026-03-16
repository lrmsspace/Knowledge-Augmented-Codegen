// Source: https://leetcode.com/problems/get-biggest-three-rhombus-sums-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​.
//
// A rhombus sum is the sum of the elements that form the border of a regular rhombus shape in grid​​​. The rhombus must have the shape of a square rotated 45 degrees with each of the corners centered in a grid cell. Below is an image of four valid rhombus shapes with the corresponding colored cells that should be included in each rhombus sum:
//
// Note that the rhombus can have an area of 0, which is depicted by the purple rhombus in the bottom right corner.
//
// Return the biggest three distinct rhombus sums in the grid in descending order. If there are less than three distinct values, return all of them.
//
// Example:
// Input: grid = [[3,4,5,1,3],[3,3,4,2,3],[20,30,200,40,10],[1,5,5,4,1],[4,3,2,2,5]]
// Output: [228,216,211]
// Explanation: The rhombus shapes for the three biggest distinct rhombus sums are depicted above.
// - Blue: 20 + 3 + 200 + 5 = 228
// - Red: 200 + 2 + 10 + 4 = 216
// - Green: 5 + 200 + 4 + 2 = 211
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j] <= 105
//

/**
 * @param {number[][]} grid
 * @return {number[]}
 */
var getBiggestThree = function(grid) {
    const m = grid.length;
    const n = grid[0].length;
    const rhombusSums = new Set();
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            rhombusSums.add(grid[i][j]);
            for (let size = 1; i - size >= 0 && i + size < m && j - size >= 0 && j + size < n; size++) {
                let sum = 0;
                for (let k = 0; k < size; k++) {
                    sum += grid[i - k][j + k];
                    sum += grid[i + k][j + k];
                    sum += grid[i + k][j - k];
                    sum += grid[i - k][j - k];
                }
                sum -= grid[i - size][j] + grid[i + size][j];
                rhombusSums.add(sum);
            }
        }
    }
    const result = Array.from(rhombusSums).sort((a, b) => b - a);
    return result.slice(0, 3);  
};
