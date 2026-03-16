// Source: https://leetcode.com/problems/check-knight-tour-configuration/   |   Difficulty: Medium
//
// Problem Description:
// There is a knight on an n x n chessboard. In a valid configuration, the knight starts at the top-left cell of the board and visits every cell on the board exactly once.
//
// You are given an n x n integer matrix grid consisting of distinct integers from the range [0, n * n - 1] where grid[row][col] indicates that the cell (row, col) is the grid[row][col]th cell that the knight visited. The moves are 0-indexed.
//
// Return true if grid represents a valid configuration of the knight's movements or false otherwise.
//
// Note that a valid knight move consists of moving two squares vertically and one square horizontally, or two squares horizontally and one square vertically. The figure below illustrates all the possible eight moves of a knight from some cell.
//
// Example:
// Input: grid = [[0,11,16,5,20],[17,4,19,10,15],[12,1,8,21,6],[3,18,23,14,9],[24,13,2,7,22]]
// Output: true
// Explanation: The above diagram represents the grid. It can be shown that it is a valid configuration.
//
// Constraints:
// n == grid.length == grid[i].length
// 	3 <= n <= 7
// 	0 <= grid[row][col] < n * n
// 	All integers in grid are unique.
//

bool checkValidGrid(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    if (grid[0][0] != 0) return false;

    int directions[8][2] = {
        {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
        {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
    };

    int posX = 0, posY = 0;

    for (int step = 1; step < n * n; step++) {
        int found = 0;
        for (int d = 0; d < 8; d++) {
            int newX = posX + directions[d][0];
            int newY = posY + directions[d][1];

            if (newX >= 0 && newX < n && newY >= 0 && newY < n && grid[newX][newY] == step) {
                posX = newX;
                posY = newY;
                found = 1;
                break;
            }
        }
        if (!found) return false;
    }

    return true;        
}
