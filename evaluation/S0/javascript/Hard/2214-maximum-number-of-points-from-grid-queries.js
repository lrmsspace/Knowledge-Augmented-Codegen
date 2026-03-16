// Source: https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid and an array queries of size k.
//
// Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:
//
//
// 	If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
// 	Otherwise, you do not get any points, and you end this process.
//
//
// After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.
//
// Return the resulting array answer.
//
// Example:
// Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
// Output: [5,8,1]
// Explanation: The diagrams above show which cells we visit to get points for each query.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	k == queries.length
// 	1 <= k <= 104
// 	1 <= grid[i][j], queries[i] <= 106
//

/**
 * @param {number[][]} grid
 * @param {number[]} queries
 * @return {number[]}
 */
var maxPoints = function(grid, queries) {
    const m = grid.length;
    const n = grid[0].length;
    const points = [];
    for (let i = 0; i < m; i++) {
        for (let j = 0; j < n; j++) {
            points.push({ value: grid[i][j], x: i, y: j });
        }
    }
    points.sort((a, b) => a.value - b.value);
    const uf = new UnionFind(m * n);
    const visited = new Array(m).fill(0).map(() => new Array(n).fill(false));
    const result = new Array(queries.length).fill(0);
    let pointIndex = 0;
    for (let i = 0; i < queries.length; i++) {
        while (pointIndex < points.length && points[pointIndex].value < queries[i]) {
            const { x, y } = points[pointIndex];
            visited[x][y] = true;
            const index = x * n + y;
            if (x > 0 && visited[x - 1][y]) {
                uf.union(index, (x - 1) * n + y);
            }
            if (x < m - 1 && visited[x + 1][y]) {
                uf.union(index, (x + 1) * n + y);
            }
            if (y > 0 && visited[x][y - 1]) {
                uf.union(index, x * n + y - 1);
            }
            if (y < n - 1 && visited[x][y + 1]) {
                uf.union(index, x * n + y + 1);
            }
            pointIndex++;
        }
        if (visited[0][0]) {
            result[i] = uf.getSize(0);
        }
    }
    return result;
        
};
