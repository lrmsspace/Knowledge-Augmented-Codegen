// Source: https://leetcode.com/problems/sudoku-solver/   |   Difficulty: Hard
//
// Problem Description:
// Write a program to solve a Sudoku puzzle by filling the empty cells.
//
// A sudoku solution must satisfy all of the following rules:
//
//
// 	Each of the digits 1-9 must occur exactly once in each row.
// 	Each of the digits 1-9 must occur exactly once in each column.
// 	Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
//
//
// The '.' character indicates empty cells.
//
// Example:
// Input: board = [["5","3",".",".","7",".",".",".","."],["6",".",".","1","9","5",".",".","."],[".","9","8",".",".",".",".","6","."],["8",".",".",".","6",".",".",".","3"],["4",".",".","8",".","3",".",".","1"],["7",".",".",".","2",".",".",".","6"],[".","6",".",".",".",".","2","8","."],[".",".",".","4","1","9",".",".","5"],[".",".",".",".","8",".",".","7","9"]]
// Output: [["5","3","4","6","7","8","9","1","2"],["6","7","2","1","9","5","3","4","8"],["1","9","8","3","4","2","5","6","7"],["8","5","9","7","6","1","4","2","3"],["4","2","6","8","5","3","7","9","1"],["7","1","3","9","2","4","8","5","6"],["9","6","1","5","3","7","2","8","4"],["2","8","7","4","1","9","6","3","5"],["3","4","5","2","8","6","1","7","9"]]
// Explanation: The input board is shown above and the only valid solution is shown below:
//
// Constraints:
// board.length == 9
// 	board[i].length == 9
// 	board[i][j] is a digit or '.'.
// 	It is guaranteed that the input board has only one solution.
//

/**
 * @param {character[][]} board
 * @return {void} Do not return anything, modify board in-place instead.
 */
var solveSudoku = function(board) {
    const rows = Array.from({ length: 9 }, () => new Set());
    const cols = Array.from({ length: 9 }, () => new Set());
    const boxes = Array.from({ length: 9 }, () => new Set());
    const emptyCells = [];
    for (let r = 0; r < 9; r++) {
        for (let c = 0; c < 9; c++) {
            const val = board[r][c];
            if (val === '.') {
                emptyCells.push([r, c]);
            } else {
                rows[r].add(val);
                cols[c].add(val);
                const boxIndex = Math.floor(r / 3) * 3 + Math.floor(c / 3);
                boxes[boxIndex].add(val);
            }
        }
    }
    const backtrack = (index) => {
        if (index === emptyCells.length) {
            return true;
        }
        const [r, c] = emptyCells[index];
        const boxIndex = Math.floor(r / 3) * 3 + Math.floor(c / 3);
        for (let num = 1; num <= 9; num++) {
            const charNum = num.toString();
            if (!rows[r].has(charNum) && !cols[c].has(charNum) && !boxes[boxIndex].has(charNum)) {
                board[r][c] = charNum;
                rows[r].add(charNum);
                cols[c].add(charNum);
                boxes[boxIndex].add(charNum);
                if (backtrack(index + 1)) {
                    return true;
                }
                board[r][c] = '.';
                rows[r].delete(charNum);
                cols[c].delete(charNum);
                boxes[boxIndex].delete(charNum);
            }
        }
        return false;
    }
    backtrack(0);   

    
                
};
