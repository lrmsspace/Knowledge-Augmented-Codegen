// Source: https://leetcode.com/problems/projection-area-of-3d-shapes/   |   Difficulty: Easy
//
// Problem Description:
// You are given an n x n grid where we place some 1 x 1 x 1 cubes that are axis-aligned with the x, y, and z axes.
//
// Each value v = grid[i][j] represents a tower of v cubes placed on top of the cell (i, j).
//
// We view the projection of these cubes onto the xy, yz, and zx planes.
//
// A projection is like a shadow, that maps our 3-dimensional figure to a 2-dimensional plane. We are viewing the "shadow" when looking at the cubes from the top, the front, and the side.
//
// Return the total area of all three projections.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: 17
// Explanation: Here are the three projections ("shadows") of the shape made with each axis-aligned plane.
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 50
// 	0 <= grid[i][j] <= 50
//

class Solution {
public:
    int projectionArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int area = 0;

        for (int i = 0; i < n; ++i) {
            int maxRow = 0;
            int maxCol = 0;

            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    area++;  // Top-down projection
                }
                maxRow = max(maxRow, grid[i][j]);  // Max in the current row
                maxCol = max(maxCol, grid[j][i]);  // Max in the current column
            }

            area += maxRow;  // Add row max to area
            area += maxCol;  // Add column max to area
        }

        return area;            
    }
};
