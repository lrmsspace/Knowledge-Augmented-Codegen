// Source: https://leetcode.com/problems/construct-2d-grid-matching-graph-layout/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array edges representing an undirected graph having n nodes, where edges[i] = [ui, vi] denotes an edge between nodes ui and vi.
//
// Construct a 2D grid that satisfies these conditions:
//
//
// 	The grid contains all nodes from 0 to n - 1 in its cells, with each node appearing exactly once.
// 	Two nodes should be in adjacent grid cells (horizontally or vertically) if and only if there is an edge between them in edges.
//
//
// It is guaranteed that edges can form a 2D grid that satisfies the conditions.
//
// Return a 2D integer array satisfying the conditions above. If there are multiple solutions, return any of them.
//
// Example:
// Input: n = 4, edges = [[0,1],[0,2],[1,3],[2,3]]
//
// Output: [[3,1],[2,0]]
//
// Explanation:
//
// Constraints:
// 2 <= n <= 5 * 104
// 	1 <= edges.length <= 105
// 	edges[i] = [ui, vi]
// 	0 <= ui < vi < n
// 	All the edges are distinct.
// 	The input is generated such that edges can form a 2D grid that satisfies the conditions.
//

/**
 * @param {number} n
 * @param {number[][]} edges
 * @return {number[][]}
 */
var constructGridLayout = function(n, edges) {
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const visited = Array(n).fill(false);
    const grid = [];
    const queue = [];
    visited[0] = true;
    queue.push([0, 0, 0]);
    let minRow = 0;
    let maxRow = 0;
    let minCol = 0;
    let maxCol = 0;
    const positionMap = new Map();
    while (queue.length > 0) {
        const [node, row, col] = queue.shift();
        positionMap.set(node, [row, col]);
        minRow = Math.min(minRow, row);
        maxRow = Math.max(maxRow, row);
        minCol = Math.min(minCol, col);
        maxCol = Math.max(maxCol, col);
        for (const neighbor of graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                if (positionMap.has(node)) {
                    const [r, c] = positionMap.get(node);
                    if (!positionMap.has(neighbor)) {
                        queue.push([neighbor, r + 1, c]);
                    }
                }
            }
        }
    }
    const numRows = maxRow - minRow + 1;
    const numCols = maxCol - minCol + 1;
    for (let i = 0; i < numRows; i++) {
        grid.push(new Array(numCols).fill(-1));
    }
    for (const [node, [row, col]] of positionMap.entries()) {
        grid[row - minRow][col - minCol] = node;
    }
    return grid;
        
};
