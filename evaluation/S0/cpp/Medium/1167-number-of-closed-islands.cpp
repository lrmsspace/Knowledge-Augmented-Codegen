// Source: https://leetcode.com/problems/number-of-closed-islands/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid consists of 0s (land) and 1s (water).  An island is a maximal 4-directionally connected group of 0s and a closed island is an island totally (all left, top, right, bottom) surrounded by 1s.
//
// Return the number of closed islands.
//
// Example:
// Input: grid = [[1,1,1,1,1,1,1,0],[1,0,0,0,0,1,1,0],[1,0,1,0,1,1,1,0],[1,0,0,0,0,1,0,1],[1,1,1,1,1,1,1,0]]
// Output: 2
// Explanation: 
// Islands in gray are closed because they are completely surrounded by water (group of 1s).
//
// Constraints:
// 1 <= grid.length, grid[0].length <= 100
// 	0 <= grid[i][j] <=1
//

class Solution {
public:
    int closedIsland(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int closedIslands = 0;

        function<void(int, int)> dfs = [&](int r, int c) {
            if (r < 0 || r >= rows || c < 0 || c >= cols || grid[r][c] != 0) {
                return;
            }
            grid[r][c] = -1; // Mark as visited
            dfs(r + 1, c);
            dfs(r - 1, c);
            dfs(r, c + 1);
            dfs(r, c - 1);
        };

        // Eliminate islands connected to the borders
        for (int r = 0; r < rows; ++r) {
            if (grid[r][0] == 0) dfs(r, 0);
            if (grid[r][cols - 1] == 0) dfs(r, cols - 1);
        }
        for (int c = 0; c < cols; ++c) {
            if (grid[0][c] == 0) dfs(0, c);
            if (grid[rows - 1][c] == 0) dfs(rows - 1, c);
        }

        // Count closed islands
        for (int r = 1; r < rows - 1; ++r) {
            for (int c = 1; c < cols - 1; ++c) {
                if (grid[r][c] == 0) {
                    closedIslands++;
                    dfs(r, c);
                }
            }
        }

        return closedIslands;           
    }
};
