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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public void gameOfLife(int[][] board) {
        int m = board.length;
        int n = board[0].length;
        int[][] copy = new int[m][n];
        for (int i = 0; i < m; i++) {
            copy[i] = board[i].clone();
        }

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                int liveNeighbors = countLiveNeighbors(copy, i, j);
                if (copy[i][j] == 1) {
                    if (liveNeighbors < 2 || liveNeighbors > 3) {
                        board[i][j] = 0;
                    }
                } else {
                    if (liveNeighbors == 3) {
                        board[i][j] = 1;
                    }
                }
            }
        }           
    }
}
