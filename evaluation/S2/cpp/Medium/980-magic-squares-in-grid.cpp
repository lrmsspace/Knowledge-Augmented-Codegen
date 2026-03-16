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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numMagicSquaresInside(vector<vector<int>>& grid) {
        int count = 0;
        for (int i = 0; i < grid.size() - 2; ++i) {
            for (int j = 0; j < grid[0].size() - 2; ++j) {
                if (isMagicSquare(grid, i, j)) {
                    ++count;
                }
            }
        }
        return count;           
    }
};
