// Source: https://leetcode.com/problems/minesweeper/   |   Difficulty: Medium
//
// Problem Description:
// Let's play the minesweeper game (Wikipedia, online game)!
//
// You are given an m x n char matrix board representing the game board where:
//
//
// 	'M' represents an unrevealed mine,
// 	'E' represents an unrevealed empty square,
// 	'B' represents a revealed blank square that has no adjacent mines (i.e., above, below, left, right, and all 4 diagonals),
// 	digit ('1' to '8') represents how many mines are adjacent to this revealed square, and
// 	'X' represents a revealed mine.
//
//
// You are also given an integer array click where click = [clickr, clickc] represents the next click position among all the unrevealed squares ('M' or 'E').
//
// Return the board after revealing this position according to the following rules:
//
//
// 	If a mine 'M' is revealed, then the game is over. You should change it to 'X'.
// 	If an empty square 'E' with no adjacent mines is revealed, then change it to a revealed blank 'B' and all of its adjacent unrevealed squares should be revealed recursively.
// 	If an empty square 'E' with at least one adjacent mine is revealed, then change it to a digit ('1' to '8') representing the number of adjacent mines.
// 	Return the board when no more squares will be revealed.
//
// Example:
// Input: board = [["E","E","E","E","E"],["E","E","M","E","E"],["E","E","E","E","E"],["E","E","E","E","E"]], click = [3,0]
// Output: [["B","1","E","1","B"],["B","1","M","1","B"],["B","1","1","1","B"],["B","B","B","B","B"]]
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 50
// 	board[i][j] is either 'M', 'E', 'B', or a digit from '1' to '8'.
// 	click.length == 2
// 	0 <= clickr < m
// 	0 <= clickc < n
// 	board[clickr][clickc] is either 'M' or 'E'.
//

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char** updateBoard(char** board, int boardSize, int* boardColSize, int* click, int clickSize, int* returnSize, int** returnColumnSizes) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    int rows = boardSize;
    int cols = boardColSize[0];
    int clickRow = click[0];
    int clickCol = click[1];

    if (board[clickRow][clickCol] == 'M') {
        board[clickRow][clickCol] = 'X';
        *returnSize = boardSize;
        *returnColumnSizes = boardColSize;
        return board;
    }

    void dfs(int row, int col) {
        if (row < 0 || row >= rows || col < 0 || col >= cols || board[row][col] != 'E') {
            return;
        }

        int mineCount = 0;
        for (int i = 0; i < 8; i++) {
            int newRow = row + directions[i][0];
            int newCol = col + directions[i][1];
            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols && board[newRow][newCol] == 'M') {
                mineCount++;
            }
        }

        if (mineCount > 0) {
            board[row][col] = '0' + mineCount;
        } else {
            board[row][col] = 'B';
            for (int i = 0; i < 8; i++) {
                dfs(row + directions[i][0], col + directions[i][1]);
            }
        }
    }

    dfs(clickRow, clickCol);

    *returnSize = boardSize;
    *returnColumnSizes = boardColSize;
    return board;       
}
