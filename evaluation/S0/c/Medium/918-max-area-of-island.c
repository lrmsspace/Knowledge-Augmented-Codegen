// Source: https://leetcode.com/problems/max-area-of-island/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
//
// The area of an island is the number of cells with a value 1 in the island.
//
// Return the maximum area of an island in grid. If there is no island, return 0.
//
// Example:
// Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
// Output: 6
// Explanation: The answer is not 11, because the island must be connected 4-directionally.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	grid[i][j] is either 0 or 1.
//

int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize) {
    int max_area = 0;
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            if (grid[i][j] == 1) {
                int area = 0;
                // DFS stack
                int stack[2500][2];
                int top = -1;
                stack[++top][0] = i;
                stack[top][1] = j;
                grid[i][j] = 0; // mark as visited
                
                while (top >= 0) {
                    int x = stack[top][0];
                    int y = stack[top--][1];
                    area++;
                    
                    for (int d = 0; d < 4; d++) {
                        int newX = x + directions[d][0];
                        int newY = y + directions[d][1];
                        
                        if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridColSize[newX] && grid[newX][newY] == 1) {
                            stack[++top][0] = newX;
                            stack[top][1] = newY;
                            grid[newX][newY] = 0; // mark as visited
                        }
                    }
                }
                
                if (area > max_area) {
                    max_area = area;
                }
            }
        }
    }
    
    return max_area;        
}
