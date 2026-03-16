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

class Solution {
public:
    int minimumOperations(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, INT_MAX));

        // Initialize the first row
        for (int j = 0; j < n; ++j) {
            dp[0][j] = 0;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k <= 9; ++k) {
                    if (i > 0) {
                        // Cell below must be equal
                        if (grid[i][j] != k) {
                            dp[i][j] = min(dp[i][j], dp[i - 1][j] + 1);
                        } else {
                            dp[i][j] = min(dp[i][j], dp[i - 1][j]);
                        }
                    }
                    if (j > 0) {
                        // Cell to the right must be different
                        if (grid[i][j] == k) {
                            dp[i][j] = min(dp[i][j], dp[i][j - 1] + 1);
                        } else {
                            dp[i][j] = min(dp[i][j], dp[i][j - 1]);
                        }
                    }
                }
            }
        }

        return dp[m - 1][n - 1];            
    }
};
