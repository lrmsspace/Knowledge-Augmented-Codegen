// Source: https://leetcode.com/problems/queens-that-can-attack-the-king/   |   Difficulty: Medium
//
// Problem Description:
// On a 0-indexed 8 x 8 chessboard, there can be multiple black queens and one white king.
//
// You are given a 2D integer array queens where queens[i] = [xQueeni, yQueeni] represents the position of the ith black queen on the chessboard. You are also given an integer array king of length 2 where king = [xKing, yKing] represents the position of the white king.
//
// Return the coordinates of the black queens that can directly attack the king. You may return the answer in any order.
//
// Example:
// Input: queens = [[0,1],[1,0],[4,0],[0,4],[3,3],[2,4]], king = [0,0]
// Output: [[0,1],[1,0],[3,3]]
// Explanation: The diagram above shows the three queens that can directly attack the king and the three queens that cannot attack the king (i.e., marked with red dashes).
//
// Constraints:
// 1 <= queens.length < 64
// 	queens[i].length == king.length == 2
// 	0 <= xQueeni, yQueeni, xKing, yKing < 8
// 	All the given positions are unique.
//

/**
 * @param {number[][]} queens
 * @param {number[]} king
 * @return {number[][]}
 */
var queensAttacktheKing = function(queens, king) {
    const board = Array.from({ length: 8 }, () => Array(8).fill(false));
    for (const [x, y] of queens) {
        board[x][y] = true;
    }
    const directions = [
        [0, 1], [1, 0], [0, -1], [-1, 0],
        [1, 1], [1, -1], [-1, 1], [-1, -1]
    ];
    const result = [];
    for (const [dx, dy] of directions) {
        let x = king[0] + dx;
        let y = king[1] + dy;
        while (x >= 0 && x < 8 && y >= 0 && y < 8) {
            if (board[x][y]) {
                result.push([x, y]);
                break;
            }
            x += dx;
            y += dy;
        }
    }
    return result;
        
};
