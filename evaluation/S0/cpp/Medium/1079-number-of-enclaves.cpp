// Source: https://leetcode.com/problems/number-of-enclaves/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid, where 0 represents a sea cell and 1 represents a land cell.
//
// A move consists of walking from one land cell to another adjacent (4-directionally) land cell or walking off the boundary of the grid.
//
// Return the number of land cells in grid for which we cannot walk off the boundary of the grid in any number of moves.
//
// Example:
// Input: grid = [[0,0,0,0],[1,0,1,0],[0,1,1,0],[0,0,0,0]]
// Output: 3
// Explanation: There are three 1s that are enclosed by 0s, and one 1 that is not enclosed because its on the boundary.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 500
// 	grid[i][j] is either 0 or 1.
//

class Solution {
public:
    int numEnclaves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        
        // Directions for moving up, down, left, right
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        
        // DFS to mark reachable land cells from the boundary
        function<void(int, int)> dfs = [&](int x, int y) {
            visited[x][y] = true;
            for (const auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                    grid[newX][newY] == 1 && !visited[newX][newY]) {
                    dfs(newX, newY);
                }
            }
        };
        
        // Start DFS from the boundary cells
        for (int i = 0; i < m; ++i) {
            if (grid[i][0] == 1 && !visited[i][0]) dfs(i, 0);
            if (grid[i][n-1] == 1 && !visited[i][n-1]) dfs(i, n-1);
        }
        for (int j = 0; j < n; ++j) {
            if (grid[0][j] == 1 && !visited[0][j]) dfs(0, j);
            if (grid[m-1][j] == 1 && !visited[m-1][j]) dfs(m-1, j);
        }
        
        // Count the number of land cells that are not visited
        int enclaveCount = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    enclaveCount++;
                }
            }
        }
        
        return enclaveCount;            
    }
};
