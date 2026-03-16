// Source: https://leetcode.com/problems/cyclically-rotating-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid​​​, where m and n are both even integers, and an integer k.
//
// The matrix is composed of several layers, which is shown in the below image, where each color is its own layer:
//
//
//
// A cyclic rotation of the matrix is done by cyclically rotating each layer in the matrix. To cyclically rotate a layer once, each element in the layer will take the place of the adjacent element in the counter-clockwise direction. An example rotation is shown below:
//
// Return the matrix after applying k cyclic rotations to it.
//
// Example:
// Input: grid = [[40,10],[30,20]], k = 1
// Output: [[10,20],[40,30]]
// Explanation: The figures above represent the grid at every state.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 50
// 	Both m and n are even integers.
// 	1 <= grid[i][j] <= 5000
// 	1 <= k <= 109
//

/**

 * @param {number[][]} grid

 * @param {number} k

 * @return {number[][]}

 */

var rotateGrid = function(grid, k) {

    const m = grid.length;

    const n = grid[0].length;
    const layers = Math.min(m, n) / 2;

    const result = Array.from({ length: m }, () => Array(n).fill(0));
    for (let layer = 0; layer < layers; layer++) {
        const elements = [];
        for (let j = layer; j < n - layer; j++) {
            elements.push(grid[layer][j]);
        }
        for (let i = layer + 1; i < m - layer - 1; i++) {
            elements.push(grid[i][n - layer - 1]);
        }
        for (let j = n - layer - 1; j >= layer; j--) {
            elements.push(grid[m - layer - 1][j]);
        }
        for (let i = m - layer - 2; i > layer; i--) {
            elements.push(grid[i][layer]);
        }
        const len = elements.length;
        const rotation = k % len;
        const rotatedElements = elements.slice(rotation).concat(elements.slice(0, rotation));
        let index = 0;
        for (let j = layer; j < n - layer; j++) {
            result[layer][j] = rotatedElements[index++];
        }
        for (let i = layer + 1; i < m - layer - 1; i++) {
            result[i][n - layer - 1] = rotatedElements[index++];
        }
        for (let j = n - layer - 1; j >= layer; j--) {
            result[m - layer - 1][j] = rotatedElements[index++];
        }
        for (let i = m - layer - 2; i > layer; i--) {
            result[i][layer] = rotatedElements[index++];
        }
    }
    return result;  
};
