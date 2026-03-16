// Source: https://leetcode.com/problems/minimum-moves-to-spread-stones-over-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer matrix grid of size 3 * 3, representing the number of stones in each cell. The grid contains exactly 9 stones, and there can be multiple stones in a single cell.
//
// In one move, you can move a single stone from its current cell to any other cell if the two cells share a side.
//
// Return the minimum number of moves required to place one stone in each cell.
//
// Example:
// Input: grid = [[1,1,0],[1,1,1],[1,2,1]]
// Output: 3
// Explanation: One possible sequence of moves to place one stone in each cell is: 
// 1- Move one stone from cell (2,1) to cell (2,2).
// 2- Move one stone from cell (2,2) to cell (1,2).
// 3- Move one stone from cell (1,2) to cell (0,2).
// In total, it takes 3 moves to place one stone in each cell of the grid.
// It can be shown that 3 is the minimum number of moves required to place one stone in each cell.
//
// Constraints:
// grid.length == grid[i].length == 3
// 	0 <= grid[i][j] <= 9
// 	Sum of grid is equal to 9.
//

class Solution {
    public int minimumMoves(int[][] grid) {
        int moves = 0;
        int stones = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                stones += grid[i][j];
                if (stones > 1) {
                    moves += stones - 1;
                    stones = 1;
                } else if (stones == 0) {
                    moves += 1;
                }
            }
        }

        return moves;           
    }
}
