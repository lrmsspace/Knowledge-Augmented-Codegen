// Source: https://leetcode.com/problems/transform-to-chessboard/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary grid board. In each move, you can swap any two rows with each other, or any two columns with each other.
//
// Return the minimum number of moves to transform the board into a chessboard board. If the task is impossible, return -1.
//
// A chessboard board is a board where no 0's and no 1's are 4-directionally adjacent.
//
// Example:
// Input: board = [[0,1,1,0],[0,1,1,0],[1,0,0,1],[1,0,0,1]]
// Output: 2
// Explanation: One potential sequence of moves is shown.
// The first move swaps the first and second column.
// The second move swaps the second and third row.
//
// Constraints:
// n == board.length
//  n == board[i].length
//  2 <= n <= 30
//  board[i][j] is either 0 or 1.
//

/**
 * @param {number[][]} board
 * @return {number}
 */
var movesToChessboard = function(board) {
    


    let n = board.length;
    let rowSum = new Array(n).fill(0);
    let colSum = new Array(n).fill(0);
    let rowSwap = 0;
    let colSwap = 0;

    for (let i = 0; i < n; i++) {
        for (let j = 0; j < n; j++) {
            if (board[i][j] === 1) {
                rowSum[i]++;
                colSum[j]++;
            }
            if (board[i][j] === board[0][0]) {
                if (i % 2 === j % 2) {
                    rowSwap++;
                    colSwap++;
                }
            } else {
                if (i % 2 !== j % 2) {
                    rowSwap++;
                    colSwap++;
                }
            }
        }
    }

    if (rowSum.some(sum => sum !== rowSum[0]) || colSum.some(sum => sum !== colSum[0])) {
        
        return -1;
    }
    if (n % 2 === 0) {
        rowSwap = Math.min(rowSwap, n - rowSwap);
        colSwap = Math.min(colSwap, n - colSwap);
    }
        else {  
        if (rowSwap % 2 === 1) {
            rowSwap = n - rowSwap;
        }
        if (colSwap % 2 === 1) {
            colSwap = n - colSwap;
        }
    }
    return (rowSwap + colSwap) / 2;
};
