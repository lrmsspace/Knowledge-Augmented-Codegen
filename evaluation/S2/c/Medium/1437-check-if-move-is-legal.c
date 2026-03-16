// Source: https://leetcode.com/problems/check-if-move-is-legal/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 8 x 8 grid board, where board[r][c] represents the cell (r, c) on a game board. On the board, free cells are represented by '.', white cells are represented by 'W', and black cells are represented by 'B'.
//
// Each move in this game consists of choosing a free cell and changing it to the color you are playing as (either white or black). However, a move is only legal if, after changing it, the cell becomes the endpoint of a good line (horizontal, vertical, or diagonal).
//
// A good line is a line of three or more cells (including the endpoints) where the endpoints of the line are one color, and the remaining cells in the middle are the opposite color (no cells in the line are free). You can find examples for good lines in the figure below:
//
// Given two integers rMove and cMove and a character color representing the color you are playing as (white or black), return true if changing cell (rMove, cMove) to color color is a legal move, or false if it is not legal.
//
// Example:
// Input: board = [[".",".",".","B",".",".",".","."],[".",".",".","W",".",".",".","."],[".",".",".","W",".",".",".","."],[".",".",".","W",".",".",".","."],["W","B","B",".","W","W","W","B"],[".",".",".","B",".",".",".","."],[".",".",".","B",".",".",".","."],[".",".",".","W",".",".",".","."]], rMove = 4, cMove = 3, color = "B"
// Output: true
// Explanation: '.', 'W', and 'B' are represented by the colors blue, white, and black respectively, and cell (rMove, cMove) is marked with an 'X'.
// The two good lines with the chosen cell as an endpoint are annotated above with the red rectangles.
//
// Constraints:
// board.length == board[r].length == 8
// 	0 <= rMove, cMove < 8
// 	board[rMove][cMove] == '.'
// 	color is either 'B' or 'W'.
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool checkMove(char** board, int boardSize, int* boardColSize, int rMove, int cMove, char color) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1},
                            {0, -1},           {0, 1},
                            {1, -1},  {1, 0},  {1, 1}};
    
    char oppositeColor = (color == 'B') ? 'W' : 'B';
    
    for (int i = 0; i < 8; i++) {
        int dr = directions[i][0];
        int dc = directions[i][1];
        
        int r = rMove + dr;
        int c = cMove + dc;
        
        // Check if the first cell in the direction is the opposite color
        if (r >= 0 && r < boardSize && c >= 0 && c < boardColSize[0] && board[r][c] == oppositeColor) {
            // Continue moving in the same direction
            while (r >= 0 && r < boardSize && c >= 0 && c < boardColSize[0]) {
                if (board[r][c] == '.') {
                    break; // Free cell found, not a good line
                }
                if (board[r][c] == color) {
                    return true; // Found a good line
                }
                r += dr;
                c += dc;
            }
        }
    }
    
    return false; // No good line found     
}
