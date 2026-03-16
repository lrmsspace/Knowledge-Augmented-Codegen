// Source: https://leetcode.com/problems/minimum-number-of-operations-to-satisfy-conditions/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D matrix grid of size m x n. In one operation, you can change the value of any cell to any non-negative number. You need to perform some operations such that each cell grid[i][j] is:
//
//
// 	Equal to the cell below it, i.e. grid[i][j] == grid[i + 1][j] (if it exists).
// 	Different from the cell to its right, i.e. grid[i][j] != grid[i][j + 1] (if it exists).
//
//
// Return the minimum number of operations needed.
//
// Example:
// Input: grid = [[1,0,2],[1,0,2]]
//
// Output: 0
//
// Explanation:
//
//
//
// All the cells in the matrix already satisfy the properties.
//
// Constraints:
// 1 <= n, m <= 1000
// 	0 <= grid[i][j] <= 9
//

int minimumOperations(int** grid, int gridSize, int* gridColSize) {
    int rows = gridSize;
    int cols = gridColSize[0];
    int operations = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Check the cell below
            if (i < rows - 1 && grid[i][j] != grid[i + 1][j]) {
                operations++;
                grid[i + 1][j] = grid[i][j]; // Make them equal
            }
            // Check the cell to the right
            if (j < cols - 1 && grid[i][j] == grid[i][j + 1]) {
                operations++;
                grid[i][j + 1] = (grid[i][j] + 1) % 10; // Change to a different value
            }
        }
    }

    return operations;      
}
