// Source: https://leetcode.com/problems/escape-a-large-maze/   |   Difficulty: Hard
//
// Problem Description:
// There is a 1 million by 1 million grid on an XY-plane, and the coordinates of each grid square are (x, y).
//
// We start at the source = [sx, sy] square and want to reach the target = [tx, ty] square. There is also an array of blocked squares, where each blocked[i] = [xi, yi] represents a blocked square with coordinates (xi, yi).
//
// Each move, we can walk one square north, east, south, or west if the square is not in the array of blocked squares. We are also not allowed to walk outside of the grid.
//
// Return true if and only if it is possible to reach the target square from the source square through a sequence of valid moves.
//
// Example:
// Input: blocked = [[0,1],[1,0]], source = [0,0], target = [0,2]
// Output: false
// Explanation: The target square is inaccessible starting from the source square because we cannot move.
// We cannot move north or east because those squares are blocked.
// We cannot move south or west because we cannot go outside of the grid.
//
// Constraints:
// 0 <= blocked.length <= 200
// 	blocked[i].length == 2
// 	0 <= xi, yi < 106
// 	source.length == target.length == 2
// 	0 <= sx, sy, tx, ty < 106
// 	source != target
// 	It is guaranteed that source and target are not blocked.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, array, bfs, counting)
//   • When to use: Use when finding the shortest path in an unweighted graph or traversing a graph level by level to explore all reachable nodes. It is also suitable for finding connected components or checking reachability.
//   • Idea: Breadth-first search explores a graph layer by layer, finding the shortest path in terms of edges from a source node to all other reachable nodes. It typically runs in O(V + E) time, where V is the number of vertices and E is the number of edges.
//   • Invariants: All nodes currently in the queue are at the same or next level of traversal from the source.; All nodes already dequeued have been fully processed, and their unvisited neighbors have been enqueued.
//   • Tips: Use a queue to manage nodes to visit in a FIFO manner.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing and cycles.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs or incorrect path lengths.; Not handling disconnected components if the goal is to traverse the entire graph.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} blocked
 * @param {number[]} source
 * @param {number[]} target
 * @return {boolean}
 */
var isEscapePossible = function(blocked, source, target) {
    const blockedSet = new Set(blocked.map(([x, y]) => `${x},${y}`));
    const directions = [[1, 0], [-1, 0], [0, 1], [0, -1]];
    const limit = (blocked.length * (blocked.length - 1)) / 2;

    const bfs = (start, end) => {
        const queue = [start];
        const visited = new Set();
        visited.add(`${start[0]},${start[1]}`);

        while (queue.length > 0 && visited.size <= limit) {
            const [x, y] = queue.shift();

            if (x === end[0] && y === end[1]) {
                return true;
            }

            for (const [dx, dy] of directions) {
                const newX = x + dx;
                const newY = y + dy;
                const key = `${newX},${newY}`;

                if (newX < 0 || newX >= 1e6 || newY < 0 || newY >= 1e6 || blockedSet.has(key) || visited.has(key)) {
                    continue;
                }

                visited.add(key);
                queue.push([newX, newY]);
            }
        }

        return visited.size > limit; // If we explored more than the limit, we can assume it's possible to escape
    };

    return bfs(source, target) && bfs(target, source); // Check both directions to ensure neither is trapped
};
