// Source: https://leetcode.com/problems/game-of-life/   |   Difficulty: Medium
//
// Problem Description:
// According to Wikipedia's article: "The Game of Life, also known simply as Life, is a cellular automaton devised by the British mathematician John Horton Conway in 1970."
//
// The board is made up of an m x n grid of cells, where each cell has an initial state: live (represented by a 1) or dead (represented by a 0). Each cell interacts with its eight neighbors (horizontal, vertical, diagonal) using the following four rules (taken from the above Wikipedia article):
//
//
// 	Any live cell with fewer than two live neighbors dies as if caused by under-population.
// 	Any live cell with two or three live neighbors lives on to the next generation.
// 	Any live cell with more than three live neighbors dies, as if by over-population.
// 	Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
//
//
// The next state of the board is determined by applying the above rules simultaneously to every cell in the current state of the m x n grid board. In this process, births and deaths occur simultaneously.
//
// Given the current state of the board, update the board to reflect its next state.
//
// Note that you do not need to return anything.
//
// Example:
// Input: board = [[0,1,0],[0,0,1],[1,1,1],[0,0,0]]
// Output: [[0,0,0],[1,0,1],[0,1,1],[0,1,0]]
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 25
// 	board[i][j] is 0 or 1.
//
//
//  
// Follow up:
//
//
// 	Could you solve it in-place? Remember that the board needs to be updated simultaneously: You cannot update some cells first and then use their updated values to update other cells.
// 	In this question, we represent the board using a 2D array. In principle, the board is infinite, which would cause problems when the active area encroaches upon the border of the array (i.e., live cells reach the border). How would you address these problems?
//

void gameOfLife(int** board, int boardSize, int* boardColSize) {
    int directions[8][2] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[0]; j++) {
            int liveNeighbors = 0;
            for (int d = 0; d < 8; d++) {
                int ni = i + directions[d][0];
                int nj = j + directions[d][1];
                if (ni >= 0 && ni < boardSize && nj >= 0 && nj < boardColSize[0]) {
                    liveNeighbors += board[ni][nj] & 1;
                }
            }
            if (board[i][j] == 1 && (liveNeighbors == 2 || liveNeighbors == 3)) {
                board[i][j] = 3; // 11 in binary: live to live
            }
            if (board[i][j] == 0 && liveNeighbors == 3) {
                board[i][j] = 2; // 10 in binary: dead to live
            }
        }
    }
    for (int i = 0; i < boardSize; i++) {
        for (int j = 0; j < boardColSize[0]; j++) {
            board[i][j] >>= 1; // Update to the next state
        }
    }       
}
