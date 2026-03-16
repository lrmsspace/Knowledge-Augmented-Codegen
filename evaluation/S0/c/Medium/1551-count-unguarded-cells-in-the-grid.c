// Source: https://leetcode.com/problems/count-unguarded-cells-in-the-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integers m and n representing a 0-indexed m x n grid. You are also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli] and walls[j] = [rowj, colj] represent the positions of the ith guard and jth wall respectively.
//
// A guard can see every cell in the four cardinal directions (north, east, south, or west) starting from their position unless obstructed by a wall or another guard. A cell is guarded if there is at least one guard that can see it.
//
// Return the number of unoccupied cells that are not guarded.
//
// Example:
// Input: m = 4, n = 6, guards = [[0,0],[1,1],[2,3]], walls = [[0,1],[2,2],[1,4]]
// Output: 7
// Explanation: The guarded and unguarded cells are shown in red and green respectively in the above diagram.
// There are a total of 7 unguarded cells, so we return 7.
//
// Constraints:
// 1 <= m, n <= 105
// 	2 <= m * n <= 105
// 	1 <= guards.length, walls.length <= 5 * 104
// 	2 <= guards.length + walls.length <= m * n
// 	guards[i].length == walls[j].length == 2
// 	0 <= rowi, rowj < m
// 	0 <= coli, colj < n
// 	All the positions in guards and walls are unique.
//

int countUnguarded(int m, int n, int** guards, int guardsSize, int* guardsColSize, int** walls, int wallsSize, int* wallsColSize) {
    // Create the grid and initialize all cells to 0 (unguarded)
    int** grid = (int**)malloc(m * sizeof(int*));
    for (int i = 0; i < m; i++) {
        grid[i] = (int*)calloc(n, sizeof(int));
    }

    // Mark guards and walls on the grid
    for (int i = 0; i < guardsSize; i++) {
        grid[guards[i][0]][guards[i][1]] = 2; // Guard
    }
    for (int i = 0; i < wallsSize; i++) {
        grid[walls[i][0]][walls[i][1]] = 3; // Wall
    }

    // Directions: up, down, left, right
    int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Mark guarded cells
    for (int i = 0; i < guardsSize; i++) {
        int row = guards[i][0];
        int col = guards[i][1];

        for (int d = 0; d < 4; d++) {
            int r = row + directions[d][0];
            int c = col + directions[d][1];

            while (r >= 0 && r < m && c >= 0 && c < n) {
                if (grid[r][c] == 2 || grid[r][c] == 3) {
                    break; // Stop at guard or wall
                }
                grid[r][c] = 1; // Mark as guarded
                r += directions[d][0];
                c += directions[d][1];
            }
        }
    }

    // Count unguarded cells
    int unguardedCount = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 0) {
                unguardedCount++;
            }
        }
        free(grid[i]);
    }
    free(grid);

    return unguardedCount;      
}
