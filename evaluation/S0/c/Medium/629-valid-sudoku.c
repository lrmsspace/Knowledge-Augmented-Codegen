// Source: https://leetcode.com/problems/valid-sudoku/   |   Difficulty: Medium
//
// Problem Description:
// Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
//
//
// 	Each row must contain the digits 1-9 without repetition.
// 	Each column must contain the digits 1-9 without repetition.
// 	Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.
//
//
// Note:
//
//
// 	A Sudoku board (partially filled) could be valid but is not necessarily solvable.
// 	Only the filled cells need to be validated according to the mentioned rules.
//
// Example:
// Input: board = 
// [["5","3",".",".","7",".",".",".","."]
// ,["6",".",".","1","9","5",".",".","."]
// ,[".","9","8",".",".",".",".","6","."]
// ,["8",".",".",".","6",".",".",".","3"]
// ,["4",".",".","8",".","3",".",".","1"]
// ,["7",".",".",".","2",".",".",".","6"]
// ,[".","6",".",".",".",".","2","8","."]
// ,[".",".",".","4","1","9",".",".","5"]
// ,[".",".",".",".","8",".",".","7","9"]]
// Output: true
//
// Constraints:
// board.length == 9
// 	board[i].length == 9
// 	board[i][j] is a digit 1-9 or '.'.
//

bool isValidSudoku(char** board, int boardSize, int* boardColSize) {
    int row[9][9] = {0};
    int col[9][9] = {0};
    int box[9][9] = {0};
    
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] != '.') {
                int num = board[i][j] - '1';
                int k = (i / 3) * 3 + (j / 3);
                
                if (row[i][num] || col[j][num] || box[k][num]) {
                    return false;
                }
                
                row[i][num] = 1;
                col[j][num] = 1;
                box[k][num] = 1;
            }
        }
    }
    
    return true;        
}
