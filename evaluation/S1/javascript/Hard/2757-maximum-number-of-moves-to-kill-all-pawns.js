// Source: https://leetcode.com/problems/maximum-number-of-moves-to-kill-all-pawns/   |   Difficulty: Hard
//
// Problem Description:
// There is a 50 x 50 chessboard with one knight and some pawns on it. You are given two integers kx and ky where (kx, ky) denotes the position of the knight, and a 2D array positions where positions[i] = [xi, yi] denotes the position of the pawns on the chessboard.
//
// Alice and Bob play a turn-based game, where Alice goes first. In each player's turn:
//
//
// 	The player selects a pawn that still exists on the board and captures it with the knight in the fewest possible moves. Note that the player can select any pawn, it might not be one that can be captured in the least number of moves.
// 	In the process of capturing the selected pawn, the knight may pass other pawns without capturing them. Only the selected pawn can be captured in this turn.
//
//
// Alice is trying to maximize the sum of the number of moves made by both players until there are no more pawns on the board, whereas Bob tries to minimize them.
//
// Return the maximum total number of moves made during the game that Alice can achieve, assuming both players play optimally.
//
// Note that in one move, a chess knight has eight possible positions it can move to, as illustrated below. Each move is two cells in a cardinal direction, then one cell in an orthogonal direction.
//
// Example:
// Input: kx = 1, ky = 1, positions = [[0,0]]
//
// Output: 4
//
// Explanation:
//
//
//
// The knight takes 4 moves to reach the pawn at (0, 0).
//
// Constraints:
// 0 <= kx, ky <= 49
// 	1 <= positions.length <= 15
// 	positions[i].length == 2
// 	0 <= positions[i][0], positions[i][1] <= 49
// 	All positions[i] are unique.
// 	The input is generated such that positions[i] != [kx, ky] for all 0 <= i < positions.length.
//
// Helpful references (internal KB):
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Placing Bishops on a Chessboard (array, matrix, dp-2d, recursion)
//   • When to use: Use this approach for counting arrangements of non-attacking pieces on a grid, particularly when piece movement is restricted to specific geometric lines like diagonals. It is effective when constraints allow for independent processing of subsets of the grid.
//   • Idea: This method employs 2D dynamic programming to count the number of ways to place bishops on a chessboard such that no two bishops attack each other. It leverages the property that bishops only attack along diagonals of the same color, processing diagonals iteratively to build up solutions in polynomial time.
//   • Invariants: All bishops placed on diagonals with index less than `i` do not attack each other.; The count `D[i][j]` correctly reflects all valid placements of `j` bishops on diagonals up to `i` of the same color.
//   • Tips: Exploit problem-specific constraints, such as bishop movement along diagonals, to simplify state definitions.; Decompose the problem by processing diagonals of the same color independently to avoid complex interactions.
//   • Pitfalls: Incorrectly handling diagonal numbering or miscalculating the number of squares in a diagonal.; Off-by-one errors when determining the number of available squares for placing a bishop on a diagonal.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} kx
 * @param {number} ky
 * @param {number[][]} positions
 * @return {number}
 */
var maxMoves = function(kx, ky, positions) {
    const knightMoves = [[2, 1], [2, -1], [-2, 1], [-2, -1], [1, 2], [1, -2], [-1, 2], [-1, -2]];
    const n = positions.length;
    const dist = Array(n).fill(Infinity);
    const queue = [];   
    for (let i = 0; i < n; i++) {
        const [px, py] = positions[i];
        dist[i] = bfs(kx, ky, px, py, knightMoves);
        queue.push(i);
    }
    let totalMoves = 0;

    while (queue.length) {
        const i = queue.shift();
        if (dist[i] === Infinity) continue;
        totalMoves += dist[i];
        for (let j = 0; j < n; j++) {
            if (i !== j) {
                const [px, py] = positions[j];
                const newDist = bfs(positions[i][0], positions[i][1], px, py, knightMoves);
                if (newDist < dist[j]) {
                    dist[j] = newDist;
                    queue.push(j);
                }
            }
        }
    }
    return totalMoves;

    function bfs(sx, sy, ex, ey, moves) {
        const visited = Array.from({ length: 50 }, () => Array(50).fill(false));
        const q = [[sx, sy, 0]];
        visited[sx][sy] = true;
        while (q.length) {
            const [x, y, d] = q.shift();
            if (x === ex && y === ey) return d;
            for (const [dx, dy] of moves) {
                const nx = x + dx, ny = y + dy;
                if (nx >= 0 && nx < 50 && ny >= 0 && ny < 50 && !visited[nx][ny]) {
                    visited[nx][ny] = true;
                    q.push([nx, ny, d + 1]);
                }
            }
        }
        return Infinity;
    }
};
