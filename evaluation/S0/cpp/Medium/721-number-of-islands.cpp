// Source: https://leetcode.com/problems/number-of-islands/   |   Difficulty: Medium
//
// Problem Description:
// Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
//
// An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water.
//
// Example:
// Input: grid = [
//   ["1","1","1","1","0"],
//   ["1","1","0","1","0"],
//   ["1","1","0","0","0"],
//   ["0","0","0","0","0"]
// ]
// Output: 1
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 300
// 	grid[i][j] is '0' or '1'.
//

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty() || grid[0].empty()) return 0;
        int m = grid.size();
        int n = grid[0].size();
        int islandCount = 0;

        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    ++islandCount;
                    // BFS to mark all connected lands
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    visited[i][j] = true;

                    while (!q.empty()) {
                        auto [x, y] = q.front();
                        q.pop();

                        for (const auto& dir : directions) {
                            int newX = x + dir.first;
                            int newY = y + dir.second;

                            if (newX >= 0 && newX < m && newY >= 0 && newY < n &&
                                grid[newX][newY] == '1' && !visited[newX][newY]) {
                                visited[newX][newY] = true;
                                q.push({newX, newY});
                            }
                        }
                    }
                }
            }
        }

        return islandCount;         
    }
};
