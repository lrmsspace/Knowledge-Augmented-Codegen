// Source: https://leetcode.com/problems/maximum-score-from-grid-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D matrix grid of size n x n. Initially, all cells of the grid are colored white. In one operation, you can select any cell of indices (i, j), and color black all the cells of the jth column starting from the top row down to the ith row.
//
// The grid score is the sum of all grid[i][j] such that cell (i, j) is white and it has a horizontally adjacent black cell.
//
// Return the maximum score that can be achieved after some number of operations.
//
// Example:
// Input: grid = [[0,0,0,0,0],[0,0,3,0,0],[0,1,0,0,0],[5,0,0,3,0],[0,0,0,0,2]]
//
// Output: 11
//
// Explanation:
//
// In the first operation, we color all cells in column 1 down to row 3, and in the second operation, we color all cells in column 4 down to the last row. The score of the resulting grid is grid[3][0] + grid[1][2] + grid[3][3] which is equal to 11.
//
// Constraints:
// 1 <= n == grid.length <= 100
// 	n == grid[i].length
// 	0 <= grid[i][j] <= 109
//

long long maximumScore(int** grid, int gridSize, int* gridColSize) {
    int n = gridSize;
    long long res = 0;
    for (int j = 0; j < n; ++j) {
        int maxCol = 0;
        for (int i = 0; i < n; ++i) {
            if (grid[i][j] > maxCol) {
                maxCol = grid[i][j];
            }
        }
        res += maxCol;
    }
    return res;     
}
