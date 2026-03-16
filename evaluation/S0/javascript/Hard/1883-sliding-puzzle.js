// Source: https://leetcode.com/problems/sliding-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.
//
// The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].
//
// Given the puzzle board board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.
//
// Example:
// Input: board = [[1,2,3],[4,0,5]]
// Output: 1
// Explanation: Swap the 0 and the 5 in one move.
//
// Constraints:
// board.length == 2
// 	board[i].length == 3
// 	0 <= board[i][j] <= 5
// 	Each value board[i][j] is unique.
//

/**
 * @param {number[][]} board
 * @return {number}
 */
var slidingPuzzle = function(board) {
    


    let swaps = 0;
    let queue = [board];
    let seen = new Set();
    while (queue.length > 0) {
        let nextQueue = [];
        for (let board of queue) {
            let key = board[0].join(',') + '|' + board[1].join(',');
            if (seen.has(key)) {
                continue;
            }
            seen.add(key);
            if (key === '1,2,3|4,5,0') {
                return swaps;
            }
            let zeroPos = findZero(board);
            let neighbors = getNeighbors(zeroPos);
            for (let [dx, dy] of neighbors) {
                let newBoard = swap(board, zeroPos, [zeroPos[0] + dx, zeroPos[1] + dy]);
                nextQueue.push(newBoard);
            }
        }
        queue = nextQueue;
        swaps++;
    }
    return -1;
                
};
