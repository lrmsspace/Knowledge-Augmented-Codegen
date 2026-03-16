// Source: https://leetcode.com/problems/island-perimeter/   |   Difficulty: Easy
//
// Problem Description:
// You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.
//
// Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).
//
// The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.
//
// Example:
// Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
// Output: 16
// Explanation: The perimeter is the 16 yellow stripes in the image above.
//
// Constraints:
// row == grid.length
// 	col == grid[i].length
// 	1 <= row, col <= 100
// 	grid[i][j] is 0 or 1.
// 	There is exactly one island in grid.
//

class Solution {
public:
    int islandPerimeter(vector<vector<int>>& grid) {
        int perimeter = 0;
        int rows = grid.size();
        int cols = grid[0].size();

        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 1) {
                    // Check all four directions
                    // Up
                    if (r == 0 || grid[r - 1][c] == 0) perimeter++;
                    // Down
                    if (r == rows - 1 || grid[r + 1][c] == 0) perimeter++;
                    // Left
                    if (c == 0 || grid[r][c - 1] == 0) perimeter++;
                    // Right
                    if (c == cols - 1 || grid[r][c + 1] == 0) perimeter++;
                }
            }
        }

        return perimeter;           
    }
};
