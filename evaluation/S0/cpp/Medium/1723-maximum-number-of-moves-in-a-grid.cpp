// Source: https://leetcode.com/problems/maximum-number-of-moves-in-a-grid/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed m x n matrix grid consisting of positive integers.
//
// You can start at any cell in the first column of the matrix, and traverse the grid in the following way:
//
//
// 	From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell.
//
//
// Return the maximum number of moves that you can perform.
//
// Example:
// Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
// Output: 3
// Explanation: We can start at the cell (0, 0) and make the following moves:
// - (0, 0) -> (0, 1).
// - (0, 1) -> (1, 2).
// - (1, 2) -> (2, 3).
// It can be shown that it is the maximum number of moves that can be made.
//
// Constraints:
// m == grid.length
// 	n == grid[i].length
// 	2 <= m, n <= 1000
// 	4 <= m * n <= 105
// 	1 <= grid[i][j] <= 106
//

class Solution {
public:
    int maxMoves(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> dp(m, 0);
        int maxMoves = 0;

        for (int col = 1; col < n; ++col) {
            vector<int> newDp(m, 0);
            for (int row = 0; row < m; ++row) {
                // Check the three possible previous positions
                for (int dRow : {-1, 0, 1}) {
                    int prevRow = row + dRow;
                    if (prevRow >= 0 && prevRow < m && grid[prevRow][col - 1] < grid[row][col]) {
                        newDp[row] = max(newDp[row], dp[prevRow] + 1);
                    }
                }
                maxMoves = max(maxMoves, newDp[row]);
            }
            dp = move(newDp);
        }

        return maxMoves;            
    }
};
