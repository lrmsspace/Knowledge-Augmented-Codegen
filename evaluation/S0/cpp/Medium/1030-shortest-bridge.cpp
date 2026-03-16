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

class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        queue<pair<int, int>> q;

        // DFS to find and mark the first island
        function<void(int, int)> dfs = [&](int x, int y) {
            if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != 1) return;
            grid[x][y] = 2; // Mark as visited
            q.push({x, y});
            for (const auto& dir : directions) {
                dfs(x + dir.first, y + dir.second);
            }
        };

        // Find the first island and start DFS
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (found) break;
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dfs(i, j);
                    found = true;
                    break;
                }
            }
        }

        // BFS to expand from the first island to reach the second island
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front();
                q.pop();
                for (const auto& dir : directions) {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                        if (grid[nx][ny] == 1) {
                            return steps; // Reached the second island
                        }
                        if (grid[nx][ny] == 0) {
                            grid[nx][ny] = 2; // Mark as visited
                            q.push({nx, ny});
                        }
                    }
                }
            }
            ++steps;
        }

        return -1; // Should never reach here           
    }
};
