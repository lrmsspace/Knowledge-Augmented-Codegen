// Source: https://leetcode.com/problems/making-a-large-island/   |   Difficulty: Hard
//
// Problem Description:
// You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
//
// Return the size of the largest island in grid after applying this operation.
//
// An island is a 4-directionally connected group of 1s.
//
// Example:
// Input: grid = [[1,0],[0,1]]
// Output: 3
// Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.
//
// Constraints:
// n == grid.length
// 	n == grid[i].length
// 	1 <= n <= 500
// 	grid[i][j] is either 0 or 1.
//

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> dirs = {{1,0},{-1,0},{0,1},{0,-1}};
        unordered_map<int, int> areaMap; // island_id -> area
        int islandId = 2; // start from 2 to avoid confusion with 0 and 1
        int maxArea = 0;
        
        // DFS to label islands and calculate their areas
        function<int(int, int, int)> dfs = [&](int x, int y, int id) {
            if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] != 1) return 0;
            grid[x][y] = id;
            int area = 1;
            for (auto& dir : dirs) {
                area += dfs(x + dir[0], y + dir[1], id);
            }
            return area;
        };
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    int area = dfs(i, j, islandId);
                    areaMap[islandId] = area;
                    maxArea = max(maxArea, area);
                    islandId++;
                }
            }
        }
        
        // Check each 0 cell to see the potential island size if flipped
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    unordered_set<int> neighborIslands;
                    for (auto& dir : dirs) {
                        int ni = i + dir[0];
                        int nj = j + dir[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] > 1) {
                            neighborIslands.insert(grid[ni][nj]);
                        }
                    }
                    int newArea = 1; // flip this 0 to 1
                    for (int id : neighborIslands) {
                        newArea += areaMap[id];
                    }
                    maxArea = max(maxArea, newArea);
                }
            }
        }
        
        return maxArea;         
    }
};
