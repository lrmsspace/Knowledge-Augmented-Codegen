// Source: https://leetcode.com/problems/max-increase-to-keep-city-skyline/   |   Difficulty: Medium
//
// Problem Description:
// There is a city composed of n x n blocks, where each block contains a single building shaped like a vertical square prism. You are given a 0-indexed n x n integer matrix grid where grid[r][c] represents the height of the building located in the block at row r and column c.
//
// A city's skyline is the outer contour formed by all the building when viewing the side of the city from a distance. The skyline from each cardinal direction north, east, south, and west may be different.
//
// We are allowed to increase the height of any number of buildings by any amount (the amount can be different per building). The height of a 0-height building can also be increased. However, increasing the height of a building should not affect the city's skyline from any cardinal direction.
//
// Return the maximum total sum that the height of the buildings can be increased by without changing the city's skyline from any cardinal direction.
//
// Example:
// Input: grid = [[3,0,8,4],[2,4,5,7],[9,2,6,3],[0,3,1,0]]
// Output: 35
// Explanation: The building heights are shown in the center of the above image.
// The skylines when viewed from each cardinal direction are drawn in red.
// The grid after increasing the height of buildings without affecting skylines is:
// gridNew = [ [8, 4, 8, 7],
//             [7, 4, 7, 7],
//             [9, 4, 8, 7],
//             [3, 3, 3, 3] ]
//
// Constraints:
// n == grid.length
// 	n == grid[r].length
// 	2 <= n <= 50
// 	0 <= grid[r][c] <= 100
//

class Solution {
    public int maxIncreaseKeepingSkyline(int[][] grid) {
        int n = grid.length;
        int[] maxRow = new int[n];
        int[] maxCol = new int[n];

        // Find the maximum height for each row
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                maxRow[r] = Math.max(maxRow[r], grid[r][c]);
            }
        }

        // Find the maximum height for each column
        for (int c = 0; c < n; c++) {
            for (int r = 0; r < n; r++) {
                maxCol[c] = Math.max(maxCol[c], grid[r][c]);
            }
        }

        int totalIncrease = 0;

        // Calculate the total possible increase
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                int allowedHeight = Math.min(maxRow[r], maxCol[c]);
                totalIncrease += allowedHeight - grid[r][c];
            }
        }

        return totalIncrease;           
    }
}
