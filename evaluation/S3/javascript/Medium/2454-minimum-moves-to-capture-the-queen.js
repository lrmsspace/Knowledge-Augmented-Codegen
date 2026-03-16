// Source: https://leetcode.com/problems/minimum-moves-to-capture-the-queen/   |   Difficulty: Medium
//
// Problem Description:
// There is a 1-indexed 8 x 8 chessboard containing 3 pieces.
//
// You are given 6 integers a, b, c, d, e, and f where:
//
//
// 	(a, b) denotes the position of the white rook.
// 	(c, d) denotes the position of the white bishop.
// 	(e, f) denotes the position of the black queen.
//
//
// Given that you can only move the white pieces, return the minimum number of moves required to capture the black queen.
//
// Note that:
//
//
// 	Rooks can move any number of squares either vertically or horizontally, but cannot jump over other pieces.
// 	Bishops can move any number of squares diagonally, but cannot jump over other pieces.
// 	A rook or a bishop can capture the queen if it is located in a square that they can move to.
// 	The queen does not move.
//
// Example:
// Input: a = 1, b = 1, c = 8, d = 8, e = 2, f = 3
// Output: 2
// Explanation: We can capture the black queen in two moves by moving the white rook to (1, 3) then to (2, 3).
// It is impossible to capture the black queen in less than two moves since it is not being attacked by any of the pieces at the beginning.
//
// Constraints:
// 1 <= a, b, c, d, e, f <= 8
// 	No two pieces are on the same square.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, multi-source-bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes layer by layer from one or more starting points. It's ideal for problems requiring minimum steps or level-order processing.
//   • Idea: Multi-source BFS explores a graph layer by layer, starting from multiple initial nodes simultaneously, to find the shortest path (in terms of edges) to all reachable nodes. It operates in O(V + E) time and O(V) space for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at the same distance from one of the source nodes.; Every node added to the queue has been marked as visited.
//   • Tips: Initialize distances for all source nodes to zero and add them to the queue.; Mark nodes as visited immediately upon adding them to the queue to prevent redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops in cyclic graphs.; Incorrectly initializing distances or the queue for multiple sources.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - Breadth-first search (graph, array, bfs)
//   • When to use: Use when finding the shortest path or minimum number of edges between nodes in an unweighted graph, or to explore a graph layer by layer. It is also suitable for finding shortest cycles or identifying all components of shortest paths.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring the shortest path in terms of edges is found from a source node to all reachable nodes. It operates in O(V + E) time complexity for adjacency list representation.
//   • Invariants: All nodes currently in the queue are at depth `k` or `k+1` from the source.; The distance recorded for any visited node is its shortest path length from the source.
//   • Tips: Run multiple BFS from different sources to find global properties like shortest cycles.; Maintain a distance array to record the shortest path length from the source to each node.
//   • Pitfalls: Applying BFS directly to weighted graphs will not yield shortest paths.; Failing to mark visited nodes can lead to infinite loops in cyclic graphs or incorrect path lengths.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} a
 * @param {number} b
 * @param {number} c
 * @param {number} d
 * @param {number} e
 * @param {number} f
 * @return {number}
 */
var minMovesToCaptureTheQueen = function(a, b, c, d, e, f) {
    const directions = [
        [1, 0], [-1, 0], [0, 1], [0, -1], // Rook moves
        [1, 1], [1, -1], [-1, 1], [-1, -1] // Bishop moves
    ];

    const isValid = (x, y) => x >= 1 && x <= 8 && y >= 1 && y <= 8;

    const queue = [];
    const visited = new Set();

    // Add initial positions of rook and bishop to the queue
    queue.push([a, b, 'R', 0]); // Rook
    queue.push([c, d, 'B', 0]); // Bishop
    visited.add(`${a},${b},R`);
    visited.add(`${c},${d},B`);

    while (queue.length > 0) {
        const [x, y, piece, moves] = queue.shift();

        if (x === e && y === f) {
            return moves;
        }

        for (const [dx, dy] of directions) {
            let step = 1;
            while (true) {
                const newX = x + dx * step;
                const newY = y + dy * step;

                if (!isValid(newX, newY)) break;

                // Check if the move is valid for the piece
                if ((piece === 'R' && (dx === 0 || dy === 0)) || 
                    (piece === 'B' && Math.abs(dx) === Math.abs(dy))) {
                    
                    const stateKey = `${newX},${newY},${piece}`;
                    if (!visited.has(stateKey)) {
                        visited.add(stateKey);
                        queue.push([newX, newY, piece, moves + 1]);
                    }
                } else {
                    break; // If it's not a valid move for the piece, stop in this direction
                }
                step++;
            }
        }
    }

    return -1; // If the queen cannot be captured
};
