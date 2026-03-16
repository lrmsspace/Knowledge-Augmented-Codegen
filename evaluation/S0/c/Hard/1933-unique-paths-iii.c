// Source: https://leetcode.com/problems/unique-paths-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer array grid where grid[i][j] could be:
//
//
// 	1 representing the starting square. There is exactly one starting square.
// 	2 representing the ending square. There is exactly one ending square.
// 	0 representing empty squares we can walk over.
// 	-1 representing obstacles that we cannot walk over.
//
//
// Return the number of 4-directional walks from the starting square to the ending square, that walk over every non-obstacle square exactly once.
//
// Example:
// Input: grid = [[1,0,0,0],[0,0,0,0],[0,0,2,-1]]
// Output: 2
// Explanation: We have the following two paths: 
// 1. (0,0),(0,1),(0,2),(0,3),(1,3),(1,2),(1,1),(1,0),(2,0),(2,1),(2,2)
// 2. (0,0),(1,0),(2,0),(2,1),(1,1),(0,1),(0,2),(0,3),(1,3),(1,2),(2,2)
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 20
// 	1 <= m * n <= 20
// 	-1 <= grid[i][j] <= 2
// 	There is exactly one starting cell and one ending cell.
//

int uniquePathsIII(int** grid, int gridSize, int* gridColSize) {
    int emptyCount = 0;
    int startX = -1, startY = -1;
    for (int i = 0; i < gridSize; ++i) {
        for (int j = 0; j < gridColSize[i]; ++j) {
            if (grid[i][j] == 0) {
                emptyCount++;
            } else if (grid[i][j] == 1) {
                startX = i;
                startY = j;
            }
        }
    }

    int pathCount = 0;

    void backtrack(int x, int y, int remain) {
        if (grid[x][y] == 2) {
            if (remain == -1) { // all empty squares visited
                pathCount++;
            }
            return;
        }

        int temp = grid[x][y];
        grid[x][y] = -4; // mark as visited

        int directions[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        for (int d = 0; d < 4; ++d) {
            int newX = x + directions[d][0];
            int newY = y + directions[d][1];
            if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridColSize[newX] &&
                (grid[newX][newY] == 0 || grid[newX][newY] == 2)) {
                backtrack(newX, newY, remain - 1);
            }
        }

        grid[x][y] = temp; // unmark
    }

    backtrack(startX, startY, emptyCount);

    return pathCount;       
}
