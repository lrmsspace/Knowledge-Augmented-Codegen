// Source: https://leetcode.com/problems/number-of-enclaves/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
//
// A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
//
// Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.
//
// Example:
// Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
// Output: 3
// Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 500
// 	grid[i][j] is either 0 or 1.
//

int numEnclaves(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    void dfs(int r, int c) {
        if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] == 0) {
            return;
        }
        grid[r][c] = 0; // Mark as visited
        for (int i = 0; i < 4; i++) {
            dfs(r + directions[i][0], c + directions[i][1]);
        }
    }
    
    // Eliminate land cells connected to the boundary
    for (int r = 0; r < rows; r++) {
        if (grid[r][0] == 1) dfs(r, 0);
        if (grid[r][cols - 1] == 1) dfs(r, cols - 1);
    }
    for (int c = 0; c < cols; c++) {
        if (grid[0][c] == 1) dfs(0, c);
        if (grid[rows - 1][c] == 1) dfs(rows - 1, c);
    }
    
    // Count remaining land cells
    int enclaveCount = 0;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                enclaveCount++;
            }
        }
    }
    
    return enclaveCount;        
}
