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

/**
 * @param {number} kx
 * @param {number} ky
 * @param {number[][]} positions
 * @return {number}
 */
var maxMoves = function(kx, ky, positions) {
    const directions = [[2, 1], [2, -1], [-2, 1], [-2, -1],
                        [1, 2], [1, -2], [-1, 2], [-1, -2]];
    const memo = new Map();

    const bfs = (startX, startY, targetX, targetY) => {
        const queue = [[startX, startY, 0]];
        const visited = new Set();
        visited.add(`${startX},${startY}`);
        while (queue.length > 0) {
            const [x, y, moves] = queue.shift();
            if (x === targetX && y === targetY) {
                return moves;
            }
            for (const [dx, dy] of directions) {
                const newX = x + dx;
                const newY = y + dy;
                if (newX >= 0 && newX < 50 && newY >= 0 && newY < 50) {
                    const key = `${newX},${newY}`;
                    if (!visited.has(key)) {
                        visited.add(key);
                        queue.push([newX, newY, moves + 1]);
                    }
                }
            }
        }
        return Infinity;
    }
    const getDistance = (x1, y1, x2, y2) => {
        const key = `${x1},${y1},${x2},${y2}`;
        if (!memo.has(key)) {
            const dist = bfs(x1, y1, x2, y2);
            memo.set(key, dist);
        }
        return memo.get(key);
    }
    const n = positions.length;
    const dp = Array.from({ length: 1 << n }, () => Array(n).fill(0));
    for (let mask = 1; mask < (1 << n); mask++) {
        for (let i = 0; i < n; i++) {
            if ((mask & (1 << i)) === 0) continue;
            const prevMask = mask ^ (1 << i);
            const distToPawn = getDistance(kx, ky, positions[i][0], positions[i][1]);
            if (prevMask === 0) {
                dp[mask][i] = distToPawn;
            }   
            else {
                let maxMovesForThisPawn = 0;
                for (let j = 0; j < n; j++) {
                    if ((prevMask & (1 << j)) === 0) continue;
                    const distBetweenPawns = getDistance(positions[j][0], positions[j][1], positions[i][0], positions[i][1]);
                    const totalMoves = dp[prevMask][j] + distBetweenPawns;
                    maxMovesForThisPawn = Math.max(maxMovesForThisPawn, totalMoves);
                }
                dp[mask][i] = maxMovesForThisPawn;
            }
        }
    }
    let result = 0;
    for (let i = 0; i < n; i++) {
        result = Math.max(result, dp[(1 << n) - 1][i]);
    }
    return result;  
};
