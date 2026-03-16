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

class Solution {
public:
    int uniquePathsIII(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        int emptyCount = 0;
        int startX, startY;
        
        // Count empty squares and find starting point
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    emptyCount++;
                } else if (grid[i][j] == 1) {
                    startX = i;
                    startY = j;
                }
            }
        }
        
        int pathCount = 0;
        
        function<void(int, int, int)> dfs = [&](int x, int y, int remain) {
            // If out of bounds or on obstacle
            if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == -1) {
                return;
            }
            
            // If reached end
            if (grid[x][y] == 2) {
                if (remain == -1) { // All empty squares visited
                    pathCount++;
                }
                return;
            }
            
            // Mark as visited
            int temp = grid[x][y];
            grid[x][y] = -1;
            
            // Explore 4 directions
            dfs(x + 1, y, remain - 1);
            dfs(x - 1, y, remain - 1);
            dfs(x, y + 1, remain - 1);
            dfs(x, y - 1, remain - 1);
            
            // Backtrack
            grid[x][y] = temp;
        };
        
        dfs(startX, startY, emptyCount);
        
        return pathCount;           
    }
};
