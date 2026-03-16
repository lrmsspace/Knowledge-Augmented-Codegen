// Source: https://leetcode.com/problems/find-the-safest-path-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D matrix grid of size n x n, where (r, c) represents:
//
//
// 	A cell containing a thief if grid[r][c] = 1
// 	An empty cell if grid[r][c] = 0
//
//
// You are initially positioned at cell (0, 0). In one move, you can move to any adjacent cell in the grid, including cells containing thieves.
//
// The safeness factor of a path on the grid is defined as the minimum manhattan distance from any cell in the path to any thief in the grid.
//
// Return the maximum safeness factor of all paths leading to cell (n - 1, n - 1).
//
// An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c - 1), (r + 1, c) and (r - 1, c) if it exists.
//
// The Manhattan distance between two cells (a, b) and (x, y) is equal to |a - x| + |b - y|, where |val| denotes the absolute value of val.
//
// Example:
// Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
// Output: 0
// Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves in cells (0, 0) and (n - 1, n - 1).
//
// Constraints:
// 1 <= grid.length == n <= 400
// 	grid[i].length == n
// 	grid[i][j] is either 0 or 1.
// 	There is at least one thief in the grid.
//

class Solution {
public:
    int maximumSafenessFactor(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
        queue<pair<int, int>> q;

        // Multi-source BFS from all thieves
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    dist[i][j] = 0;
                    q.push({i, j});
                }
            }
        }

        vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (const auto& dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;
                if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
                    if (dist[nx][ny] > dist[x][y] + 1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny});
                    }
                }
            }
        }

        // Binary search for maximum safeness factor
        int left = 0, right = n * 2;
        auto canReach = [&](int safeness) {
            vector<vector<bool>> visited(n, vector<bool>(n, false));
            queue<pair<int, int>> q;
            if (dist[0][0] < safeness) return false;
            q.push({0, 0});
            visited[0][0] = true;

            while (!q.empty()) {
                auto [x, y] = q.front(); q.pop();
                if (x == n - 1 && y == n - 1) return true;
                for (const auto& dir : directions) {
                    int nx = x + dir.first;
                    int ny = y + dir.second;
                    if (nx >= 0 && nx < n && ny >= 0 && ny < n && !visited[nx][ny] && dist[nx][ny] >= safeness) {
                        visited[nx][ny] = true;
                        q.push({nx, ny});
                    }
                }
            }
            return false;
        };          
    }
};
