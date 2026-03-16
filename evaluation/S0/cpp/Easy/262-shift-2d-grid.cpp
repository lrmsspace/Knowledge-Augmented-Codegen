// Source: https://leetcode.com/problems/shift-2d-grid/   |   Difficulty: Easy
//
// Problem Description:
// Given a 2D grid of size m x n and an integer k. You need to shift the grid k times.
//
// In one shift operation:
//
//
// 	Element at grid[i][j] moves to grid[i][j + 1].
// 	Element at grid[i][n - 1] moves to grid[i + 1][0].
// 	Element at grid[m - 1][n - 1] moves to grid[0][0].
//
//
// Return the 2D grid after applying shift operation k times.
//
// Example:
// Input: grid = [[1,2,3],[4,5,6],[7,8,9]], k = 1
// Output: [[9,1,2],[3,4,5],[6,7,8]]
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	1 <= m <= 50
// 	1 <= n <= 50
// 	-1000 <= grid[i][j] <= 1000
// 	0 <= k <= 100
//

class Solution {
public:
    vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> result(m, vector<int>(n, 0));
        
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int newPos = (i * n + j + k) % (m * n);
                int newRow = newPos / n;
                int newCol = newPos % n;
                result[newRow][newCol] = grid[i][j];
            }
        }
        
        return result;          
    }
};
