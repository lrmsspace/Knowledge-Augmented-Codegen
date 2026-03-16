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

class Solution {
public:
    int minDays(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        auto isConnected = [&](vector<vector<int>>& g) {
            vector<vector<bool>> visited(m, vector<bool>(n, false));
            int landCount = 0;
            int startX = -1, startY = -1;
            
            for (int i = 0; i < m; i++) {
                for (int j = 0; j < n; j++) {
                    if (g[i][j] == 1) {
                        landCount++;
                        startX = i;
                        startY = j;
                    }
                }
            }
            
            if (landCount == 0) return false;
            
            int connectedCount = 0;
            function<void(int, int)> dfs = [&](int x, int y) {
                if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y] || g[x][y] == 0) return;
                visited[x][y] = true;
                connectedCount++;
                dfs(x + 1, y);
                dfs(x - 1, y);
                dfs(x, y + 1);
                dfs(x, y - 1);
            };
            
            dfs(startX, startY);
            return connectedCount == landCount;
        };
        
        if (!isConnected(grid)) return 0;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if (!isConnected(grid)) return 1;
                    grid[i][j] = 1;
                }
            }
        }
        
        return 2;           
    }
};
