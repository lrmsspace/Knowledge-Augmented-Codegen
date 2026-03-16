// Source: https://leetcode.com/problems/number-of-valid-move-combinations-on-chessboard/   |   Difficulty: Hard
//
// Problem Description:
// There is an 8 x 8 chessboard containing n pieces (rooks, queens, or bishops). You are given a string array pieces of length n, where pieces[i] describes the type (rook, queen, or bishop) of the ith piece. In addition, you are given a 2D integer array positions also of length n, where positions[i] = [ri, ci] indicates that the ith piece is currently at the 1-based coordinate (ri, ci) on the chessboard.
//
// When making a move for a piece, you choose a destination square that the piece will travel toward and stop on.
//
//
// 	A rook can only travel horizontally or vertically from (r, c) to the direction of (r+1, c), (r-1, c), (r, c+1), or (r, c-1).
// 	A queen can only travel horizontally, vertically, or diagonally from (r, c) to the direction of (r+1, c), (r-1, c), (r, c+1), (r, c-1), (r+1, c+1), (r+1, c-1), (r-1, c+1), (r-1, c-1).
// 	A bishop can only travel diagonally from (r, c) to the direction of (r+1, c+1), (r+1, c-1), (r-1, c+1), (r-1, c-1).
//
//
// You must make a move for every piece on the board simultaneously. A move combination consists of all the moves performed on all the given pieces. Every second, each piece will instantaneously travel one square towards their destination if they are not already at it. All pieces start traveling at the 0th second. A move combination is invalid if, at a given time, two or more pieces occupy the same square.
//
// Return the number of valid move combinations​​​​​.
//
//
// Example:
// Input: pieces = ["rook"], positions = [[1,1]]
// Output: 15
// Explanation: The image above shows the possible squares the piece can move to.
//
// Constraints:
// n == pieces.length 
// 	n == positions.length
// 	1 <= n <= 4
// 	pieces only contains the strings "rook", "queen", and "bishop".
// 	There will be at most one queen on the chessboard.
// 	1 <= ri, ci <= 8
// 	Each positions[i] is distinct.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} pieces
 * @param {number[][]} positions
 * @return {number}
 */
var countCombinations = function(pieces, positions) {
    const n = pieces.length;
    const moves = [];
    for (let i = 0; i < n; i++) {
        const [r, c] = positions[i];
        const pieceMoves = [];
        if (pieces[i] === "rook" || pieces[i] === "queen") {
            for (let j = 1; j <= 8; j++) {
                if (j !== c) pieceMoves.push([r, j]);
                if (j !== r) pieceMoves.push([j, c]);
            }
        }
        if (pieces[i] === "bishop" || pieces[i] === "queen") {
            for (let j = 1; j <= 8; j++) {
                if (r + j <= 8 && c + j <= 8) pieceMoves.push([r + j, c + j]);
                if (r + j <= 8 && c - j >= 1) pieceMoves.push([r + j, c - j]);
                if (r - j >= 1 && c + j <= 8) pieceMoves.push([r - j, c + j]);
                if (r - j >= 1 && c - j >= 1) pieceMoves.push([r - j, c - j]);
            }
        }
        moves.push(pieceMoves);
    }
    let count = 0;
    const backtrack = (index, destinations) => {
        if (index === n) {
            const positionsAtTime = new Map();
            for (let t = 0; t <= 8; t++) {
                positionsAtTime.clear();
                for (let i = 0; i < n; i++) {
                    const [r, c] = positions[i];
                    const [dr, dc] = destinations[i];
                    const nr = r + Math.sign(dr - r) * Math.min(t, Math.abs(dr - r));
                    const nc = c + Math.sign(dc - c) * Math.min(t, Math.abs(dc - c));
                    const posKey = `${nr},${nc}`;
                    if (positionsAtTime.has(posKey)) {
                        return;
                    }
                    positionsAtTime.set(posKey, true);
                }
            }
            count++;
            return;
        }
        for (const dest of moves[index]) {
            destinations.push(dest);
            backtrack(index + 1, destinations);
            destinations.pop();
        }
    };
    backtrack(0, []);
    return count;
};
