// Source: https://leetcode.com/problems/max-area-of-island/   |   Difficulty: Medium
//
// Problem Description:
// You are given an m x n binary matrix grid. An island is a group of 1's (representing land) connected 4-directionally (horizontal or vertical.) You may assume all four edges of the grid are surrounded by water.
//
// The area of an island is the number of cells with a value 1 in the island.
//
// Return the maximum area of an island in grid. If there is no island, return 0.
//
// Example:
// Input: grid = [[0,0,1,0,0,0,0,1,0,0,0,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,1,1,0,1,0,0,0,0,0,0,0,0],[0,1,0,0,1,1,0,0,1,0,1,0,0],[0,1,0,0,1,1,0,0,1,1,1,0,0],[0,0,0,0,0,0,0,0,0,0,1,0,0],[0,0,0,0,0,0,0,1,1,1,0,0,0],[0,0,0,0,0,0,0,1,1,0,0,0,0]]
// Output: 6
// Explanation: The answer is not 11, because the island must be connected 4-directionally.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m, n <= 50
// 	grid[i][j] is either 0 or 1.
//

class Solution {
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int maxArea = 0;
        int rows = grid.size();
        int cols = grid[0].size();
        
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        
        vector<pair<int, int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};
        
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1 && !visited[r][c]) {
                    int area = 0;
                    queue<pair<int, int>> q;
                    q.push({r, c});
                    visited[r][c] = true;
                    
                    while (!q.empty()) {
                        auto [curR, curC] = q.front();
                        q.pop();
                        area++;
                        
                        for (const auto& dir : directions) {
                            int newR = curR + dir.first;
                            int newC = curC + dir.second;
                            
                            if (newR >= 0 && newR < rows && newC >= 0 && newC < cols &&
                                grid[newR][newC] == 1 && !visited[newR][newC]) {
                                q.push({newR, newC});
                                visited[newR][newC] = true;
                            }
                        }
                    }
                    
                    maxArea = max(maxArea, area);
                }
            }
        }
        
        return maxArea;         
    }
};
