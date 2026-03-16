// Source: https://leetcode.com/problems/select-cells-in-grid-with-maximum-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D matrix grid consisting of positive integers.
//
// You have to select one or more cells from the matrix such that the following conditions are satisfied:
//
//
// 	No two selected cells are in the same row of the matrix.
// 	The values in the set of selected cells are unique.
//
//
// Your score will be the sum of the values of the selected cells.
//
// Return the maximum score you can achieve.
//
// Example:
// Input: grid = [[1,2,3],[4,3,2],[1,1,1]]
//
// Output: 8
//
// Explanation:
//
//
//
// We can select the cells with values 1, 3, and 4 that are colored above.
//
// Constraints:
// 1 <= grid.length, grid[i].length <= 10
// 	1 <= grid[i][j] <= 100
//

class Solution {
public:
    int maxScore(vector<vector<int>>& grid) {
        int rows = grid.size();
        int cols = grid[0].size();
        int maxScore = 0;
        
        // Use bitmask to represent selected columns
        int totalMasks = 1 << cols;
        
        // DP array to store maximum score for each row and column mask
        vector<vector<int>> dp(rows + 1, vector<int>(totalMasks, 0));
        
        for (int r = 0; r < rows; r++) {
            for (int mask = 0; mask < totalMasks; mask++) {
                // Carry forward the previous row's value
                dp[r + 1][mask] = max(dp[r + 1][mask], dp[r][mask]);
                
                // Try to select a cell in the current row
                for (int c = 0; c < cols; c++) {
                    if ((mask & (1 << c)) == 0) { // If column c is not selected
                        int newMask = mask | (1 << c);
                        dp[r + 1][newMask] = max(dp[r + 1][newMask], dp[r][mask] + grid[r][c]);
                    }
                }
            }
        }
        
        // Find the maximum score from the last row
        for (int mask = 0; mask < totalMasks; mask++) {
            maxScore = max(maxScore, dp[rows][mask]);
        }
        
        return maxScore;            
    }
};
