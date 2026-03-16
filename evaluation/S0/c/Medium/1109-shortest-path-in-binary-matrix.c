// Source: https://leetcode.com/problems/shortest-path-in-binary-matrix/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n binary matrix grid, return the length of the shortest clear path in the matrix. If there is no clear path, return -1.
//
// A clear path in a binary matrix is a path from the top-left cell (i.e., (0, 0)) to the bottom-right cell (i.e., (n - 1, n - 1)) such that:
//
//
// 	All the visited cells of the path are 0.
// 	All the adjacent cells of the path are 8-directionally connected (i.e., they are different and they share an edge or a corner).
//
//
// The length of a clear path is the number of visited cells of this path.
//
// Example:
// Input: grid = [[0,1],[1,0]]
// Output: 2
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
//

int shortestPathBinaryMatrix(int** grid, int gridSize, int* gridColSize) {
    if (grid[0][0] == 1 || grid[gridSize - 1][*gridColSize - 1] == 1) {
        return -1;
    }

    int directions[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},          {0, 1},
        {1, -1},  {1, 0}, {1, 1}
    };

    int queue[10000][2];
    int front = 0, rear = 0;
    queue[rear][0] = 0;
    queue[rear][1] = 0;
    rear++;
    grid[0][0] = 1; // Mark as visited with distance 1

    while (front < rear) {
        int x = queue[front][0];
        int y = queue[front][1];
        front++;

        if (x == gridSize - 1 && y == *gridColSize - 1) {
            return grid[x][y];
        }

        for (int i = 0; i < 8; i++) {
            int newX = x + directions[i][0];
            int newY = y + directions[i][1];

            if (newX >= 0 && newX < gridSize && newY >= 0 && newY < *gridColSize && grid[newX][newY] == 0) {
                queue[rear][0] = newX;
                queue[rear][1] = newY;
                rear++;
                grid[newX][newY] = grid[x][y] + 1; // Update distance
            }
        }
    }

    return -1;      
}
