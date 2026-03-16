// Source: https://leetcode.com/problems/magic-squares-in-grid/   |   Difficulty: Medium
//
// Problem Description:
// A 3 x 3 magic square is a 3 x 3 grid filled with distinct numbers from 1 to 9 such that each row, column, and both diagonals all have the same sum.
//
// Given a row x col grid of integers, how many 3 x 3 magic square subgrids are there?
//
// Note: while a magic square can only contain numbers from 1 to 9, grid may contain numbers up to 15.
//
// Example:
// Input: grid = [[4,3,8,4],[9,5,1,9],[2,7,6,2]]
// Output: 1
// Explanation: 
// The following subgrid is a 3 x 3 magic square:
//
// while this one is not:
//
// In total, there is only one magic square inside the given grid.
//
// Constraints:
// row == grid.length
// 	col == grid[i].length
// 	1 <= row, col <= 10
// 	0 <= grid[i][j] <= 15
//

int numMagicSquaresInside(int** grid, int gridSize, int* gridColSize) {
    int count = 0;
    for (int i = 0; i <= gridSize - 3; i++) {
        for (int j = 0; j <= gridColSize[0] - 3; j++) {
            int nums[10] = {0};
            int isMagic = 1;
            for (int x = 0; x < 3; x++) {
                for (int y = 0; y < 3; y++) {
                    int val = grid[i + x][j + y];
                    if (val < 1 || val > 9 || nums[val]) {
                        isMagic = 0;
                        break;
                    }
                    nums[val] = 1;
                }
                if (!isMagic) break;
            }
            if (!isMagic) continue;

            int sum = grid[i][j] + grid[i][j + 1] + grid[i][j + 2];
            if (grid[i + 1][j] + grid[i + 1][j + 1] + grid[i + 1][j + 2] != sum ||
                grid[i + 2][j] + grid[i + 2][j + 1] + grid[i + 2][j + 2] != sum ||
                grid[i][j] + grid[i + 1][j] + grid[i + 2][j] != sum ||
                grid[i][j + 1] + grid[i + 1][j + 1] + grid[i + 2][j + 1] != sum ||
                grid[i][j + 2] + grid[i + 1][j + 2] + grid[i + 2][j + 2] != sum ||
                grid[i][j] + grid[i + 1][j + 1] + grid[i + 2][j + 2] != sum ||
                grid[i][j + 2] + grid[i + 1][j + 1] + grid[i + 2][j] != sum) {
                continue;
            }
            count++;
        }
    }
    return count;       
}
