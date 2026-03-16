// Source: https://leetcode.com/problems/surface-area-of-3d-shapes/   |   Difficulty: Easy
//
// Problem Description:
// You are given an n x n grid where you have placed some 1 x 1 x 1 cubes. Each value v = grid[i][j] represents a tower of v cubes placed on top of cell (i, j).
//
// After placing these cubes, you have decided to glue any directly adjacent cubes to each other, forming several irregular 3D shapes.
//
// Return the total surface area of the resulting shapes.
//
// Note: The bottom face of each shape counts toward its surface area.
//
// Example:
// Input: grid = [[1,2],[3,4]]
// Output: 34
//
// Constraints:
// n == grid.length == grid[i].length
// 	1 <= n <= 50
// 	0 <= grid[i][j] <= 50
//

class Solution {
public:
    int surfaceArea(vector<vector<int>>& grid) {
        int n = grid.size();
        int area = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] > 0) {
                    area += 2; // Top and bottom faces

                    // Front face
                    if (i == 0) {
                        area += grid[i][j];
                    } else {
                        area += max(0, grid[i][j] - grid[i - 1][j]);
                    }

                    // Back face
                    if (i == n - 1) {
                        area += grid[i][j];
                    } else {
                        area += max(0, grid[i][j] - grid[i + 1][j]);
                    }

                    // Left face
                    if (j == 0) {
                        area += grid[i][j];
                    } else {
                        area += max(0, grid[i][j] - grid[i][j - 1]);
                    }

                    // Right face
                    if (j == n - 1) {
                        area += grid[i][j];
                    } else {
                        area += max(0, grid[i][j] - grid[i][j + 1]);
                    }
                }
            }
        }

        return area;            
    }
};
