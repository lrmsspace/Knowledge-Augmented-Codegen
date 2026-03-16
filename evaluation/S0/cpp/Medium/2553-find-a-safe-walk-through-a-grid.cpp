// Source: https://leetcode.com/problems/find-a-safe-walk-through-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid and an integer health.
//
// You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).
//
// You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.
//
// Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.
//
// Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.
//
// Example:
// Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1
//
// Output: true
//
// Explanation:
//
// The final cell can be reached safely by walking along the gray cells below.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	2 <= m * n
// 	1 <= health <= m + n
// 	grid[i][j] is either 0 or 1.
//

class Solution {
public:
    bool findSafeWalk(vector<vector<int>>& grid, int health) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, -1));
        dp[0][0] = health - grid[0][0];

        queue<pair<int, int>> q;
        q.push({0, 0});

        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();

            for (const auto& dir : directions) {
                int nx = x + dir.first;
                int ny = y + dir.second;

                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    int newHealth = dp[x][y] - grid[nx][ny];
                    if (newHealth > 0 && newHealth > dp[nx][ny]) {
                        dp[nx][ny] = newHealth;
                        q.push({nx, ny});
                    }
                }
            }
        }

        return dp[m - 1][n - 1] > 0;            
    }
};
