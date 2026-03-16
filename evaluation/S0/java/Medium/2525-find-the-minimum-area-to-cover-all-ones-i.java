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
    public int minimumArea(int[][] grid) {
        int minRow = grid.length, maxRow = -1, minCol = grid[0].length, maxCol = -1;

        for (int i = 0; i < grid.length; i++) {
            for (int j = 0; j < grid[0].length; j++) {
                if (grid[i][j] == 1) {
                    minRow = Math.min(minRow, i);
                    maxRow = Math.max(maxRow, i);
                    minCol = Math.min(minCol, j);
                    maxCol = Math.max(maxCol, j);
                }
            }
        }

        return (maxRow - minRow + 1) * (maxCol - minCol + 1);           
    }
}
