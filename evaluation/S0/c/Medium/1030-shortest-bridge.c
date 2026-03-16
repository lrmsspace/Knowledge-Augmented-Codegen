// Source: https://leetcode.com/problems/shortest-bridge/   |   Difficulty: Medium
//
// Problem Description:
// You are given an n x n binary matrix grid where 1 represents land and 0 represents water.
//
// An island is a 4-directionally connected group of 1's not connected to any other 1's. There are exactly two islands in grid.
//
// You may change 0's to 1's to connect the two islands to form one island.
//
// Return the smallest number of 0's you must flip to connect the two islands.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 1
//
// Constraints:
// n == grid.length == grid[i].length
// 	2 <= n <= 100
// 	grid[i][j] is either 0 or 1.
// 	There are exactly two islands in grid.
//

int shortestBridge(int** grid, int gridSize, int* gridColSize) {
    int directions[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
    int queue[10000][2];
    int front = 0, back = 0;
    int found = 0;

    void dfs(int x, int y) {
        if (x < 0 || x >= gridSize || y < 0 || y >= gridSize || grid[x][y] != 1) return;
        grid[x][y] = 2;
        queue[back][0] = x;
        queue[back][1] = y;
        back++;
        for (int i = 0; i < 4; i++) {
            dfs(x + directions[i][0], y + directions[i][1]);
        }
    }

    for (int i = 0; i < gridSize; i++) {
        if (found) break;
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 1) {
                dfs(i, j);
                found = 1;
                break;
            }
        }
    }

    int steps = 0;
    while (front < back) {
        int size = back - front;
        for (int i = 0; i < size; i++) {
            int x = queue[front][0];
            int y = queue[front][1];
            front++;
            for (int d = 0; d < 4; d++) {
                int nx = x + directions[d][0];
                int ny = y + directions[d][1];
                if (nx >= 0 && nx < gridSize && ny >= 0 && ny < gridSize) {
                    if (grid[nx][ny] == 1) return steps;
                    if (grid[nx][ny] == 0) {
                        grid[nx][ny] = 2;
                        queue[back][0] = nx;
                        queue[back][1] = ny;
                        back++;
                    }
                }
            }
        }
        steps++;
    }

    return -1; // Should never reach here       
}
