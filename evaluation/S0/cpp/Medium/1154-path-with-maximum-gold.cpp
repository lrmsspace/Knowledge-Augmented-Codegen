// Source: https://leetcode.com/problems/path-with-maximum-gold/   |   Difficulty: Medium
//
// Problem Description:
// In a gold mine grid of size m x n, each cell in this mine has an integer representing the amount of gold in that cell, 0 if it is empty.
//
// Return the maximum amount of gold you can collect under the conditions:
//
//
// 	Every time you are located in a cell you will collect all the gold in that cell.
// 	From your position, you can walk one step to the left, right, up, or down.
// 	You can't visit the same cell more than once.
// 	Never visit a cell with 0 gold.
// 	You can start and stop collecting gold from any position in the grid that has some gold.
//
// Example:
// Input: grid = [[0,6,0],[5,8,7],[0,9,0]]
// Output: 24
// Explanation:
// [[0,6,0],
//  [5,8,7],
//  [0,9,0]]
// Path to get the maximum gold, 9 -> 8 -> 7.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 15
// 	0 <= grid[i][j] <= 100
// 	There are at most 25 cells containing gold.
//

class Solution {
public:
    int getMaximumGold(vector<vector<int>>& grid) {
        int maxGold = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        function<void(int, int, int)> dfs = [&](int r, int c, int currentGold) {
            maxGold = max(maxGold, currentGold);
            vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
            for (const auto& dir : directions) {
                int newRow = r + dir.first;
                int newCol = c + dir.second;
                if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                    grid[newRow][newCol] > 0 && !visited[newRow][newCol]) {
                    visited[newRow][newCol] = true;
                    dfs(newRow, newCol, currentGold + grid[newRow][newCol]);
                    visited[newRow][newCol] = false;
                }
            }
        };

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] > 0) {
                    visited[i][j] = true;
                    dfs(i, j, grid[i][j]);
                    visited[i][j] = false;
                }
            }
        }

        return maxGold;         
    }
};
