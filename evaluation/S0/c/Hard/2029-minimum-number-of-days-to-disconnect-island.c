// Source: https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n binary grid grid where 1 represents land and 0 represents water. An island is a maximal 4-directionally (horizontal or vertical) connected group of 1's.
//
// The grid is said to be connected if we have exactly one island, otherwise is said disconnected.
//
// In one day, we are allowed to change any single land cell (1) into a water cell (0).
//
// Return the minimum number of days to disconnect the grid.
//
// Example:
// Input: grid = [[0,1,1,0],[0,1,1,0],[0,0,0,0]]
//
// Output: 2
// Explanation: We need at least 2 days to get a disconnected grid.
// Change land grid[1][1] and grid[0][2] to water and get 2 disconnected island.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 30
// 	grid[i][j] is either 0 or 1.
//

int minDays(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int landCells = 0;

    // Count land cells
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                landCells++;
            }
        }
    }

    if (landCells == 0 || landCells == 1) {
        return landCells;
    }

    // Check if the island is already disconnected
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int visited[30][30] = {0};

    void dfs(int r, int c) {
        visited[r][c] = 1;
        for (int d = 0; d < 4; d++) {
            int nr = r + directions[d][0];
            int nc = c + directions[d][1];
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1 && !visited[nr][nc]) {
                dfs(nr, nc);
            }
        }
    }

    // Find first land cell to start DFS
    int startR = -1, startC = -1;
    for (int r = 0; r < rows && startR == -1; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                startR = r;
                startC = c;
                break;
            }
        }
    }

    dfs(startR, startC);

    // Check if all land cells are visited
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1 && !visited[r][c]) {
                return 0; // Already disconnected
            }
        }
    }

    // Check if removing one land cell disconnects the island
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                grid[r][c] = 0; // Remove land cell

                // Reset visited array
                memset(visited, 0, sizeof(visited));

                // Find new starting point for DFS
                int newStartR = -1, newStartC = -1;
                for (int rr = 0; rr < rows && newStartR == -1; rr++) {
                    for (int cc = 0; cc < cols; cc++) {
                        if (grid[rr][cc] == 1) {
                            newStartR = rr;
                            newStartC = cc;
                            break;
                        }
                    }
                }

                if (newStartR != -1) {
                    dfs(newStartR, newStartC);
                }

                // Check if all land cells are visited
                int disconnected = 0;
                for (int rr = 0; rr < rows; rr++) {
                    for (int cc = 0; cc < cols; cc++) {
                        if (grid[rr][cc] == 1 && !visited[rr][cc]) {
                            disconnected = 1;
                            break;
                        }
                    }
                    if (disconnected) break;
                }

                grid[r][c] = 1; // Restore land cell

                if (disconnected) {
                    return 1; // Disconnected by removing one cell
                }
            }
        }
    }
    return 2; // Need to remove at least two cells    
}
