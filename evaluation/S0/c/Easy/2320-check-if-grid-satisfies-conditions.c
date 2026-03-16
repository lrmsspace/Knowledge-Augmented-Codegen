// Source: https://leetcode.com/problems/check-if-grid-satisfies-conditions/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D matrix grid of size m x n. You need to check if each cell grid[i][j] is:
//
//
// 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
// 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
//
//
// Return true if all the cells satisfy these conditions, otherwise, return false.
//
// Example:
// Input: grid = [[1,0,2],[1,0,2]]
//
// Output: true
//
// Explanation:
//
//
//
// All the cells in the grid satisfy the conditions.
//
// Constraints:
// 1 <= n, m <= 10
// 	0 <= grid[i][j] <= 9
//

bool satisfiesConditions(int** grid, int gridSize, int* gridColSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridColSize[i]; j++) {
            // Check the cell below
            if (i + 1 < gridSize) {
                if (grid[i][j] != grid[i + 1][j]) {
                    return false;
                }
            }
            // Check the cell to the right
            if (j + 1 < gridColSize[i]) {
                if (grid[i][j] == grid[i][j + 1]) {
                    return false;
                }
            }
        }
    }
    return true;        
}
