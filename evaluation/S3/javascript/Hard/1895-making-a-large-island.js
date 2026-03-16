// Source: https://leetcode.com/problems/making-a-large-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
//
// Return the size of the largest island in grid after applying this operation.
//
// An island is a 4-directionally connected group of 1s.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 500
// 	grid[i][j] is either 0 or 1.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Search for connected components in a graph (graph, dfs, bfs, enumeration)
//   • When to use: Use when you need to partition an undirected graph into maximal connected subgraphs where every node is reachable from every other node within its subgraph.
//   • Idea: This algorithm identifies all connected components in an undirected graph by iteratively performing graph traversals (DFS or BFS) from unvisited nodes. It has a time complexity of O(V + E) for adjacency list representation.
//   • Invariants: All nodes visited so far belong to an identified connected component.; Any node currently being visited is part of the current connected component being explored.
//   • Tips: Maintain a visited array or set to track processed nodes.; Iterate through all nodes, starting a new traversal if a node is unvisited.
//   • Pitfalls: Failing to iterate through all nodes to find all components in a disconnected graph.; Not correctly marking nodes as visited during traversal, leading to infinite loops or re-processing.
// - Finding the largest zero submatrix (array, stack, monotonic-stack, max-window)
//   • When to use: This algorithm is used to find the largest rectangular submatrix composed entirely of zeros within a binary matrix. It efficiently reduces the 2D problem to a series of 1D largest rectangle in histogram problems.
//   • Idea: The algorithm transforms a 2D matrix problem into a series of 1D 'largest rectangle in histogram' problems, one for each row. It uses a monotonic stack to find the nearest smaller elements for each bar in O(N) time, leading to an overall O(N*M) complexity for the 2D problem.
//   • Invariants: The stack always stores indices of elements in strictly increasing order of their corresponding heights.; When an element is popped from the stack, the element below it is its nearest smaller element to the left.
//   • Tips: Precompute heights for each column, representing consecutive zeros upwards from the current row.; The 2D problem is effectively reduced to finding the largest rectangle in a histogram for each row.
//   • Pitfalls: Incorrectly handling boundary conditions when using the stack (e.g., empty stack, end of array).; Off-by-one errors when calculating the width of the rectangle (k2 - k1 - 1).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} grid
 * @return {number}
 */
var largestIsland = function(grid) {
    const n = grid.length;
    const islandSizes = new Map();
    let islandId = 2; // Start from 2 to avoid confusion with 0 and 1
        
    // DFS to find the size of each island and mark them with a unique ID
    const dfs = (x, y, id) => {
        if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] !== 1) {
            return 0;
        }   
        grid[x][y] = id; // Mark the cell with the island ID
        return 1 + dfs(x - 1, y, id) + dfs(x + 1, y, id) + dfs(x, y - 1, id) + dfs(x, y + 1, id);
    }
    // First pass to identify islands and their sizes
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 1) {
                const size = dfs(i, j, islandId);
                islandSizes.set(islandId, size);
                islandId++;
            }
        }
    }
    let maxIsland = 0;
    // Second pass to check each zero cell and calculate potential island size
    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (grid[i][j] === 0) {
                const seenIslands = new Set();
                let potentialSize = 1;
                // Check the four directions for adjacent islands
                const directions = [[-1, 0], [1, 0], [0, -1], [0, 1]];
                for (const [dx, dy] of directions) {
                    const x = i + dx;
                    const y = j + dy;
                    if (x >= 0 && x < n && y >= 0 && y < n && grid[x][y] > 1) {
                        const id = grid[x][y];
                        if (!seenIslands.has(id)) {
                            seenIslands.add(id);
                            potentialSize += islandSizes.get(id);
                        }
                    }
                }
                maxIsland = Math.max(maxIsland, potentialSize);
            }
        }
    }
    // If there are no zeros, return the size of the largest existing island
    if (maxIsland === 0) {
        for (const size of islandSizes.values()) {
            maxIsland = Math.max(maxIsland, size);
        }
    }
    return maxIsland;
            
};
