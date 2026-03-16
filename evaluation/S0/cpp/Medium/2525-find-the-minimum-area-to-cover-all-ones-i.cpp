// Source: https://leetcode.com/problems/find-the-minimum-area-to-cover-all-ones-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D binary array grid. Find a rectangle with horizontal and vertical sides with the smallest area, such that all the 1's in grid lie inside this rectangle.
//
// Return the minimum possible area of the rectangle.
//
// Example:
// Input: grid = [[0,1,0],[1,0,1]]
//
// Output: 6
//
// Explanation:
//
//
//
// The smallest rectangle has a height of 2 and a width of 3, so it has an area of 2 * 3 = 6.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 1000
// 	grid[i][j] is either 0 or 1.
// 	The input is generated such that there is at least one 1 in grid.
//

class Solution {
public:
    int minimumArea(vector<vector<int>>& grid) {
        int minRow = grid.size(), maxRow = -1;
        int minCol = grid[0].size(), maxCol = -1;

        for (int r = 0; r < grid.size(); ++r) {
            for (int c = 0; c < grid[0].size(); ++c) {
                if (grid[r][c] == 1) {
                    minRow = min(minRow, r);
                    maxRow = max(maxRow, r);
                    minCol = min(minCol, c);
                    maxCol = max(maxCol, c);
                }
            }
        }

        int height = maxRow - minRow + 1;
        int width = maxCol - minCol + 1;

        return height * width;          
    }
};
