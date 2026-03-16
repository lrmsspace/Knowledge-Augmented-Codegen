// Source: https://leetcode.com/problems/surrounded-regions/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n matrix board containing letters 'X' and 'O', capture regions that are surrounded:
//
//
// 	Connect: A cell is connected to adjacent cells horizontally or vertically.
// 	Region: To form a region connect every 'O' cell.
// 	Surround: The region is surrounded with 'X' cells if you can connect the region with 'X' cells and none of the region cells are on the edge of the board.
//
//
// To capture a surrounded region, replace all 'O's with 'X's in-place within the original board. You do not need to return anything.
//
// Example:
// Input: board = [["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]
//
// Output: [["X","X","X","X"],["X","X","X","X"],["X","X","X","X"],["X","O","X","X"]]
//
// Explanation:
//
// In the above diagram, the bottom region is not captured because it is on the edge of the board and cannot be surrounded.
//
// Constraints:
// m == board.length
// 	n == board[i].length
// 	1 <= m, n <= 200
// 	board[i][j] is 'X' or 'O'.
//

void solve(char** board, int boardSize, int* boardColSize) {
    if (boardSize == 0 || boardColSize[0] == 0) return;

    int rows = boardSize;
    int cols = boardColSize[0];

    // Helper function for DFS
    void dfs(int r, int c) {
        if (r < 0 || c < 0 || r >= rows || c >= cols || board[r][c] != 'O') return;
        board[r][c] = 'T'; // Temporarily mark the cell
        dfs(r + 1, c);
        dfs(r - 1, c);
        dfs(r, c + 1);
        dfs(r, c - 1);
    }

    // Start DFS from 'O's on the borders
    for (int r = 0; r < rows; r++) {
        if (board[r][0] == 'O') dfs(r, 0);
        if (board[r][cols - 1] == 'O') dfs(r, cols - 1);
    }
    for (int c = 0; c < cols; c++) {
        if (board[0][c] == 'O') dfs(0, c);
        if (board[rows - 1][c] == 'O') dfs(rows - 1, c);
    }

    // Flip all remaining 'O's to 'X's and 'T's back to 'O's
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (board[r][c] == 'O') {
                board[r][c] = 'X';
            } else if (board[r][c] == 'T') {
                board[r][c] = 'O';
            }
        }
    }       
}
