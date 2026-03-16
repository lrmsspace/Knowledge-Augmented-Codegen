// Source: https://leetcode.com/problems/regions-cut-by-slashes/   |   Difficulty: Medium
//
// Problem Description:
// An n x n grid is composed of 1 x 1 squares where each 1 x 1 square consists of a '/', '\', or blank space ' '. These characters divide the square into contiguous regions.
//
// Given the grid grid represented as a string array, return the number of regions.
//
// Note that backslash characters are escaped, so a '\' is represented as '\\'.
//
// Example:
// Input: grid = [" /","/ "]
// Output: 2
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 30
// 	grid[i][j] is either '/', '\', or ' '.
//

int regionsBySlashes(char** grid, int gridSize) {
    int n = gridSize;
    int size = n * 3;
    int** g = (int**)malloc(size * sizeof(int*));
    for (int i = 0; i < size; i++) {
        g[i] = (int*)calloc(size, sizeof(int));
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == '/') {
                g[i * 3][j * 3 + 2] = 1;
                g[i * 3 + 1][j * 3 + 1] = 1;
                g[i * 3 + 2][j * 3] = 1;
            } else if (grid[i][j] == '\\') {
                g[i * 3][j * 3] = 1;
                g[i * 3 + 1][j * 3 + 1] = 1;
                g[i * 3 + 2][j * 3 + 2] = 1;
            }
        }
    }

    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int regions = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (g[i][j] == 0) {
                regions++;
                // DFS to mark all connected cells
                void dfs(int x, int y) {
                    g[x][y] = 1;
                    for (int d = 0; d < 4; d++) {
                        int newX = x + directions[d][0];
                        int newY = y + directions[d][1];
                        if (newX >= 0 && newX < size && newY >= 0 && newY < size && g[newX][newY] == 0) {
                            dfs(newX, newY);
                        }
                    }
                }
                dfs(i, j);
            }
        }
    }
    for (int i = 0; i < size; i++) {
        free(g[i]);
    }
    free(g);
    return regions;     
}
