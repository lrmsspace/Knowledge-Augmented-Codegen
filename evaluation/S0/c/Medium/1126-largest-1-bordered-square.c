// Source: https://leetcode.com/problems/largest-1-bordered-square/   |   Difficulty: Medium
//
// Problem Description:
// Given a 2D grid of 0s and 1s, return the number of elements in the largest square subgrid that has all 1s on its border, or 0 if such a subgrid doesn't exist in the grid.
//
// Example:
// Input: grid = [[1,1,1],[1,0,1],[1,1,1]]
// Output: 9
//
// Constraints:
// 1 <= grid.length <= 100
// 	1 <= grid[0].length <= 100
// 	grid[i][j] is 0 or 1
//



int largest1BorderedSquare(int** grid, int gridSize, int* gridColSize){
    int m = gridSize, n = gridColSize[0];
    int right[m][n], down[m][n];
    memset(right, 0, sizeof(right));
    memset(down, 0, sizeof(down));
    
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            if (grid[i][j] == 1) {
                right[i][j] = 1 + (j + 1 < n ? right[i][j + 1] : 0);
                down[i][j] = 1 + (i + 1 < m ? down[i + 1][j] : 0);
            }
        }
    }
    
    int maxSide = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            int small = right[i][j] < down[i][j] ? right[i][j] : down[i][j];
            for (int side = small; side > maxSide; --side) {
                if (right[i + side - 1][j] >= side && down[i][j + side - 1] >= side) {
                    maxSide = side;
                    break;
                }
            }
        }
    }
    
    return maxSide * maxSide;
}
