// Source: https://leetcode.com/problems/rotting-oranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n grid where each cell can have one of three values:
//
//
// 	0 representing an empty cell,
// 	1 representing a fresh orange, or
// 	2 representing a rotten orange.
//
//
// Every minute, any fresh orange that is 4-directionally adjacent to a rotten orange becomes rotten.
//
// Return the minimum number of minutes that must elapse until no cell has a fresh orange. If this is impossible, return -1.
//
// Example:
// Input: grid = [[2,1,1],[1,1,0],[0,1,1]]
// Output: 4
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 10
// 	grid[i][j] is 0, 1, or 2.
//

int orangesRotting(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int fresh_count = 0;
    int minutes = 0;
    int directions[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
    
    // Count fresh oranges and enqueue rotten oranges
    int queue[rows * cols][2];
    int front = 0, rear = 0;
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (grid[r][c] == 1) {
                fresh_count++;
            } else if (grid[r][c] == 2) {
                queue[rear][0] = r;
                queue[rear][1] = c;
                rear++;
            }
        }
    }
    
    // BFS to rot adjacent fresh oranges
    while (front < rear && fresh_count > 0) {
        int size = rear - front;
        for (int i = 0; i < size; i++) {
            int r = queue[front][0];
            int c = queue[front][1];
            front++;
            
            for (int d = 0; d < 4; d++) {
                int nr = r + directions[d][0];
                int nc = c + directions[d][1];
                
                if (nr >= 0 && nr < rows && nc >= 0 && nc < cols && grid[nr][nc] == 1) {
                    grid[nr][nc] = 2;
                    fresh_count--;
                    queue[rear][0] = nr;
                    queue[rear][1] = nc;
                    rear++;
                }
            }
        }
        minutes++;
    }
    
    return fresh_count == 0 ? minutes : -1;     
}
