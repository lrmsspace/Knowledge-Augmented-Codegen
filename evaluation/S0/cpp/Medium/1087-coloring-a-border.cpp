// Source: https://leetcode.com/problems/coloring-a-border/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n integer matrix grid, and three integers row, col, and color. Each value in the grid represents the color of the grid square at that location.
//
// Two squares are called adjacent if they are next to each other in any of the 4 directions.
//
// Two squares belong to the same connected component if they have the same color and they are adjacent.
//
// The border of a connected component is all the squares in the connected component that are either adjacent to (at least) a square not in the component, or on the boundary of the grid (the first or last row or column).
//
// You should color the border of the connected component that contains the square grid[row][col] with color.
//
// Return the final grid.
//
// Example:
// Input: grid = [[1,1],[1,2]], row = 0, col = 0, color = 3
// Output: [[3,3],[3,2]]
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	1 <= grid[i][j], color <= 1000
// 	0 <= row < m
// 	0 <= col < n
//

class Solution {
public:
    vector<vector<int>> colorBorder(vector<vector<int>>& grid, int row, int col, int color) {
        int m = grid.size();
        int n = grid[0].size();
        int originalColor = grid[row][col];
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<pair<int, int>> directions = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        vector<pair<int, int>> borderCells;

        function<void(int, int)> dfs = [&](int r, int c) {
            visited[r][c] = true;
            bool isBorder = false;

            for (const auto& dir : directions) {
                int nr = r + dir.first;
                int nc = c + dir.second;

                if (nr < 0 || nr >= m || nc < 0 || nc >= n || grid[nr][nc] != originalColor) {
                    isBorder = true;
                } else if (!visited[nr][nc]) {
                    dfs(nr, nc);
                }
            }

            if (isBorder) {
                borderCells.push_back({r, c});
            }
        };

        dfs(row, col);

        for (const auto& cell : borderCells) {
            grid[cell.first][cell.second] = color;
        }

        return grid;            
    }
};
