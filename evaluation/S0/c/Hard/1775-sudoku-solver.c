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

void solveSudoku(char** board, int boardSize, int* boardColSize) {
    int rowUsed[9][9] = {0};
    int colUsed[9][9] = {0};
    int boxUsed[9][9] = {0};
    int emptyCells[81][2];
    int emptyCount = 0;

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            if (board[r][c] != '.') {
                int num = board[r][c] - '1';
                rowUsed[r][num] = 1;
                colUsed[c][num] = 1;
                boxUsed[(r / 3) * 3 + (c / 3)][num] = 1;
            } else {
                emptyCells[emptyCount][0] = r;
                emptyCells[emptyCount][1] = c;
                emptyCount++;
            }
        }
    }

    void backtrack(int index) {
        if (index == emptyCount) return 1;

        int r = emptyCells[index][0];
        int c = emptyCells[index][1];
        int boxIndex = (r / 3) * 3 + (c / 3);

        for (int num = 0; num < 9; num++) {
            if (!rowUsed[r][num] && !colUsed[c][num] && !boxUsed[boxIndex][num]) {
                board[r][c] = num + '1';
                rowUsed[r][num] = colUsed[c][num] = boxUsed[boxIndex][num] = 1;

                if (backtrack(index + 1)) return 1;

                board[r][c] = '.';
                rowUsed[r][num] = colUsed[c][num] = boxUsed[boxIndex][num] = 0;
            }
        }
        return 0;
    }

    backtrack(0);       
}
