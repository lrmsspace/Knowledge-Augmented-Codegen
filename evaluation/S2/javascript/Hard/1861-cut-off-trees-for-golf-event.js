// Source: https://leetcode.com/problems/cut-off-trees-for-golf-event/   |   Difficulty: Hard
//
// Problem Description:
// You are asked to cut off all the trees in a forest for a golf event. The forest is represented as an m x n matrix. In this matrix:
//
//
// 	0 means the cell cannot be walked through.
// 	1 represents an empty cell that can be walked through.
// 	A number greater than 1 represents a tree in a cell that can be walked through, and this number is the tree's height.
//
//
// In one step, you can walk in any of the four directions: north, east, south, and west. If you are standing in a cell with a tree, you can choose whether to cut it off.
//
// You must cut off the trees in order from shortest to tallest. When you cut off a tree, the value at its cell becomes 1 (an empty cell).
//
// Starting from the point (0, 0), return the minimum steps you need to walk to cut off all the trees. If you cannot cut off all the trees, return -1.
//
// Note: The input is generated such that no two trees have the same height, and there is at least one tree needs to be cut off.
//
// Example:
// Input: forest = [[1,2,3],[0,0,4],[7,6,5]]
// Output: 6
// Explanation: Following the path above allows you to cut off the trees from shortest to tallest in 6 steps.
//
// Constraints:
// m == forest.length
// 	n == forest[i].length
// 	1 <= m, n <= 50
// 	0 <= forest[i][j] <= 109
// 	Heights of all trees are distinct.
//
// Helpful references (internal KB):
// - Finding the largest zero submatrix (matrix, array, dp-2d)
//   • When to use: When finding the maximum rectangular subregion consisting of only zeros in a binary matrix, often by transforming rows into histogram problems.
//   • Idea: This algorithm finds the largest rectangular submatrix containing only zeros by precomputing heights of consecutive zeros for each column and then applying a largest rectangle in histogram approach for each row. It has a time complexity of O(rows * cols).
//   • Invariants: After processing row `i`, `heights[j]` accurately represents the count of consecutive zeros ending at `(i, j)` in column `j`.; The `max_area` variable correctly stores the largest rectangular area of zeros found in any submatrix from rows `0` to `i`.
//   • Tips: Transform the 2D problem into a series of 1D histogram problems, one for each row.; Precompute the height of consecutive zeros ending at each cell in each column.
//   • Pitfalls: Incorrectly calculating the height array, especially at row boundaries or when encountering '1's.; Off-by-one errors when calculating rectangle areas in the histogram step.
// - Minimum spanning tree - Prim's algorithm (graph, matrix, array, mst-prim, greedy)
//   • When to use: When you need to find a minimum spanning tree in a connected, weighted graph, especially efficient for dense graphs or when starting from an arbitrary vertex.
//   • Idea: Prim's algorithm is a greedy algorithm that constructs a Minimum Spanning Tree (MST) by iteratively adding the cheapest edge connecting a vertex in the growing tree to a vertex outside it. It typically runs in O(E log V) with a priority queue or O(V^2) with an adjacency matrix.
//   • Invariants: The set of edges chosen so far forms a tree (no cycles) and connects a subset of vertices.; At each step, the chosen edge is the minimum weight edge connecting a vertex in the current MST to a vertex outside it.
//   • Tips: Initialize distances (or minimum edge weights) for all vertices not in the MST to infinity.; Use a priority queue to efficiently retrieve the minimum weight edge connecting to the current MST.
//   • Pitfalls: Failing to correctly update edge weights to neighbors when a new vertex is added to the MST.; Not handling disconnected graphs, which will result in only an MST for the starting component.
// - Finding the Eulerian path in O(M) (graph, enumeration, bfs)
//   • When to use: Use when the problem requires visiting every edge in a graph exactly once, either starting and ending at the same vertex (cycle) or at two different vertices (path).
//   • Idea: An Eulerian path is a trail in a graph which visits every edge exactly once. An Eulerian cycle is an Eulerian path that starts and ends on the same vertex.
//   • Invariants: Every edge in the graph is considered exactly once for inclusion in the path.; The current path segment always forms a valid trail in the graph.
//   • Tips: Check vertex degrees to determine path/cycle existence before attempting to find it.; For an Eulerian path, start traversal from one of the two odd-degree vertices.
//   • Pitfalls: Incorrectly handling multi-edges or self-loops can lead to errors in degree calculation or traversal.; Failing to check graph connectivity can result in incomplete paths or infinite loops.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} forest
 * @return {number}
 */
var cutOffTree = function(forest) {
    const trees = [];
    for (let i = 0; i < forest.length; i++) {
        for (let j = 0; j < forest[0].length; j++) {
            if (forest[i][j] > 1) {
                trees.push([forest[i][j], i, j]);
            }
        }
    }
    
    trees.sort((a, b) => a[0] - b[0]);
    
    let totalSteps = 0;
    let currentX = 0, currentY = 0;
    
    for (const [height, targetX, targetY] of trees) {
        const steps = bfs(forest, currentX, currentY, targetX, targetY);
        if (steps === -1) return -1;
        
        totalSteps += steps;
        currentX = targetX;
        currentY = targetY;
    }
    
    return totalSteps;
};
