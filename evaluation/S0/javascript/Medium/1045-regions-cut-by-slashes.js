// Source: https://leetcode.com/problems/regions-cut-by-slashes/   |   Difficulty: Medium
//
// Problem Description:
// An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
//
// Given the grid grid represented as a string array, return the number of regions.
//
// Note that backslash characters are escaped, so a '\' is represented as '\\'.
//
// Example:
// Input: grid = [" /","/ "]
// Output: 2
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 30
// 	grid[i][j] is either '/', '\', or ' '.
//

/**
 * @param {string[]} grid
 * @return {number}
 */
var regionsBySlashes = function(grid) {
    const n = grid.length;
        
    const parent = new Array(4 * n * n).fill(0).map((_, index) => index);
    const find = (x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };
    const union = (x, y) => {
        const rootX = find(x);
        const rootY = find(y);
        if (rootX !== rootY) {
            parent[rootX] = rootY;
        }
    };
    for (let r = 0; r < n; r++) {
        for (let c = 0; c < n; c++) {
            const index = 4 * (r * n + c);
            const val = grid[r][c];
            if (val === ' ') {
                union(index + 0, index + 1);
                union(index + 1, index + 2);
                union(index + 2, index + 3);
            }
            else if (val === '/') {
                union(index + 0, index + 3);
                union(index + 1, index + 2);
            }
            else if (val === '\\') {
                union(index + 0, index + 1);
                union(index + 2, index + 3);
            }
            if (c + 1 < n) {
                union(index + 1, 4 * (r * n + (c + 1)) + 3);
            }
            if (r + 1 < n) {
                union(index + 2, 4 * ((r + 1) * n + c) + 0);
            }
        }
    }
    const uniqueParents = new Set();    
    for (let i = 0; i < 4 * n * n; i++) {   
        uniqueParents.add(find(i));
    }
    return uniqueParents.size;            
};