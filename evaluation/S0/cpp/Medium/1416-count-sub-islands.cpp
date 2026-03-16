// Source: https://leetcode.com/problems/count-sub-islands/   |   Difficulty: Medium
//
// Problem Description:
// You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or vertical). Any cells outside of the grid are considered water cells.
//
// An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.
//
// Return the number of islands in grid2 that are considered sub-islands.
//
// Example:
// Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
// Output: 3
// Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
// The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.
//
// Constraints:
// m == grid1.length == grid2.length
// 	n == grid1[i].length == grid2[i].length
// 	1 <= m, n <= 500
// 	grid1[i][j] and grid2[i][j] are either 0 or 1.
//

class Solution {
public:
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size();
        int n = grid1[0].size();
        int subIslandCount = 0;

        vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};

        function<bool(int, int)> dfs = [&](int x, int y) {
            if (x < 0 || x >= m || y < 0 || y >= n || grid2[x][y] == 0) {
                return true;
            }

            grid2[x][y] = 0; // Mark as visited
            bool isSubIsland = true;

            if (grid1[x][y] == 0) {
                isSubIsland = false;
            }

            for (const auto& dir : directions) {
                int newX = x + dir.first;
                int newY = y + dir.second;
                if (!dfs(newX, newY)) {
                    isSubIsland = false;
                }
            }

            return isSubIsland;
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid2[i][j] == 1) {
                    if (dfs(i, j)) {
                        ++subIslandCount;
                    }
                }
            }
        }

        return subIslandCount;          
    }
};
