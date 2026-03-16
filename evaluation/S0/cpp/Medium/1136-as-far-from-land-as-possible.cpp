// Source: https://leetcode.com/problems/as-far-from-land-as-possible/   |   Difficulty: Medium
//
// Problem Description:
// Given an n x n grid containing only values 0 and 1, where 0 represents water and 1 represents land, find a water cell such that its distance to the nearest land cell is maximized, and return the distance. If no land or water exists in the grid, return -1.
//
// The distance used in this problem is the Manhattan distance: the distance between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.
//
// Example:
// Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
// Output: 2
// Explanation: The cell (1, 1) is as far as possible from all the land with distance 2.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 100
// 	grid[i][j] is 0 or 1
//

class Solution {
public:
    int maxDistance(vector<vector<int>>& grid) {
        int n = grid.size();
        queue<pair<int, int>> q;

        // Enqueue all land cells
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    q.push({i, j});
                }
            }
        }

        // If there is no land or water, return -1
        if (q.empty() || q.size() == n * n) {
            return -1;
        }

        int maxDist = -1;
        vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};

        // Multi-source BFS
        while (!q.empty()) {
            int size = q.size();
            ++maxDist;

            for (int i = 0; i < size; ++i) {
                auto [x, y] = q.front();
                q.pop();

                for (const auto& dir : directions) {
                    int newX = x + dir.first;
                    int newY = y + dir.second;

                    if (newX >= 0 && newX < n && newY >= 0 && newY < n && grid[newX][newY] == 0) {
                        grid[newX][newY] = 1; // Mark as visited
                        q.push({newX, newY});
                    }
                }
            }
        }

        return maxDist;         
    }
};
