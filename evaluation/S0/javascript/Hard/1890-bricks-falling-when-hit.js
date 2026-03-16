// Source: https://leetcode.com/problems/bricks-falling-when-hit/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary grid, where each 1 represents a brick and 0 represents an empty space. A brick is stable if:
//
//
// 	It is directly connected to the top of the grid, or
// 	At least one other brick in its four adjacent cells is stable.
//
//
// You are also given an array hits, which is a sequence of erasures we want to apply. Each time we want to erase the brick at the location hits[i] = (rowi, coli). The brick on that location (if it exists) will disappear. Some other bricks may no longer be stable because of that erasure and will fall. Once a brick falls, it is immediately erased from the grid (i.e., it does not land on other stable bricks).
//
// Return an array result, where each result[i] is the number of bricks that will fall after the ith erasure is applied.
//
// Note that an erasure may refer to a location with no brick, and if it does, no bricks drop.
//
// Example:
// Input: grid = [[1,0,0,0],[1,1,1,0]], hits = [[1,0]]
// Output: [2]
// Explanation: Starting with the grid:
// [[1,0,0,0],
//  [1,1,1,0]]
// We erase the underlined brick at (1,0), resulting in the grid:
// [[1,0,0,0],
//  [0,1,1,0]]
// The two underlined bricks are no longer stable as they are no longer connected to the top nor adjacent to another stable brick, so they will fall. The resulting grid is:
// [[1,0,0,0],
//  [0,0,0,0]]
// Hence the result is [2].
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 200
// 	grid[i][j] is 0 or 1.
// 	1 <= hits.length <= 4 * 104
// 	hits[i].length == 2
// 	0 <= xi <= m - 1
// 	0 <= yi <= n - 1
// 	All (xi, yi) are unique.
//

/**
 * @param {number[][]} grid
 * @param {number[][]} hits
 * @return {number[]}
 */
var hitBricks = function(grid, hits) {
    


    let m = grid.length;
    let n = grid[0].length;
    let copy = grid.map(row => row.slice());
    for (let [x, y] of hits) {
        copy[x][y] = 0;
    }

    let uf = new UnionFind(m * n + 1);
    let top = m * n;
    for (let j = 0; j < n; j++) {
        if (copy[0][j] === 1) {
            uf.union(j, top);
        }
    }
    let directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    for (let i = 1; i < m; i++) {
        for (let j = 0; j < n; j++) {
            if (copy[i][j] === 1) {
                for (let [dx, dy] of directions) {
                    let x = i + dx;
                    let y = j + dy;
                    if (x >= 0 && x < m && y >= 0 && y < n && copy[x][y] === 1) {
                        uf.union(i * n + j, x * n + y);
                    }
                }
            }
        }
        
    }
    let heights = [];
    for (let i = hits.length - 1; i >= 0; i--) {
        let [x, y] = hits[i];
        if (grid[x][y] === 0) {
            heights.push([0, 0]);
            continue;
        }
        let currentHeight = uf.getSize(top);
        let index = x * n + y;
        for (let [dx, dy] of directions) {
            let newX = x + dx;
            let newY = y + dy;
            if (newX >= 0 && newX < m && newY >= 0 && newY < n && copy[newX][newY] === 1) {
                uf.union(index, newX * n + newY);
            }
        }
        copy[x][y] = 1;
        let newHeight = uf.getSize(top);
        heights.push([0, Math.max(0, newHeight - currentHeight - 1)]);
    }
    return heights.reverse().map(([_, height]) => height);
};
