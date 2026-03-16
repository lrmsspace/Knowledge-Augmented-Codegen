// Source: https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/   |   Difficulty: Hard
//
// Problem Description:
// You are given an m x n integer matrix grid, where you can move from a cell to any adjacent cell in all 4 directions.
//
// Return the number of strictly increasing paths in the grid such that you can start from any cell and end at any cell. Since the answer may be very large, return it modulo 109 + 7.
//
// Two paths are considered different if they do not have exactly the same sequence of visited cells.
//
// Example:
// Input: grid = [[1,1],[3,4]]
// Output: 8
// Explanation: The strictly increasing paths are:
// - Paths with length 1: [1], [1], [3], [4].
// - Paths with length 2: [1 -> 3], [1 -> 4], [3 -> 4].
// - Paths with length 3: [1 -> 3 -> 4].
// The total number of paths is 4 + 3 + 1 = 8.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 1000
// 	1 <= m * n <= 105
// 	1 <= grid[i][j] <= 105
//

class Solution {
public:
    int countPaths(vector<vector<int>>& grid) {
        const int MOD = 1e9 + 7;
        int m = grid.size();
        int n = grid[0].size();
        
        vector<vector<int>> dp(m, vector<int>(n, 0));
        vector<pair<int, pair<int, int>>> cells; // (value, (i, j))
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cells.push_back({grid[i][j], {i, j}});
            }
        }
        
        sort(cells.begin(), cells.end());
        
        int directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (auto& cell : cells) {
            int value = cell.first;
            int i = cell.second.first;
            int j = cell.second.second;
            
            dp[i][j] = (dp[i][j] + 1) % MOD; // Count the path of length 1
            
            for (auto& dir : directions) {
                int ni = i + dir[0];
                int nj = j + dir[1];
                
                if (ni >= 0 && ni < m && nj >= 0 && nj < n && grid[ni][nj] < value) {
                    dp[i][j] = (dp[i][j] + dp[ni][nj]) % MOD;
                }
            }
        }
        
        int result = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                result = (result + dp[i][j]) % MOD;
            }
        }
        
        return result;          
    }
};
