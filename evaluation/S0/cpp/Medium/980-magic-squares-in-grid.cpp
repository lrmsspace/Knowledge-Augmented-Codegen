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

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int count = 0;

        for (int r = 0; r <= rows - 3; ++r) {
            for (int c = 0; c <= cols - 3; ++c) {
                if (isMagicSquare(grid, r, c)) {
                    count++;
                }
            }
        }

        return count;           
    }
};
