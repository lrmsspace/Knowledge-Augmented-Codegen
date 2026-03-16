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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minDays(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> directions{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        auto countIslands = [&]() {
            vector<vector<bool>> visited(m, vector<bool>(n));
            int count = 0;

            function<void(int, int)> dfs = [&](int x, int y) {
                visited[x][y] = true;
                for (auto& dir : directions) {
                    int newX = x + dir[0], newY = y + dir[1];
                    if (newX >= 0 && newX < m && newY >= 0 && newY < n && grid[newX][newY] == 1 && !visited[newX][newY]) {
                        dfs(newX, newY);
                    }
                }
            };

            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (grid[i][j] == 1 && !visited[i][j]) {
                        dfs(i, j);
                        ++count;
                    }
                }
            }
            return count;
        };

        int initialIslands = countIslands();
        if (initialIslands != 1) return 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    grid[i][j] = 0;
                    if (countIslands() != 1) return 1;
                    grid[i][j] = 1; // revert change
                }
            }
        }

        return 2;           
    }
};
