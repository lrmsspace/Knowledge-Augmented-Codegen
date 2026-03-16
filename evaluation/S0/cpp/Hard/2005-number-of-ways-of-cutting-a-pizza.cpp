// Source: https://leetcode.com/problems/number-of-ways-of-cutting-a-pizza/   |   Difficulty: Hard
//
// Problem Description:
// Given a rectangular pizza represented as a rows x cols matrix containing the following characters: 'A' (an apple) and '.' (empty cell) and given the integer k. You have to cut the pizza into k pieces using k-1 cuts. 
//
// For each cut you choose the direction: vertical or horizontal, then you choose a cut position at the cell boundary and cut the pizza into two pieces. If you cut the pizza vertically, give the left part of the pizza to a person. If you cut the pizza horizontally, give the upper part of the pizza to a person. Give the last piece of pizza to the last person.
//
// Return the number of ways of cutting the pizza such that each piece contains at least one apple. Since the answer can be a huge number, return this modulo 10^9 + 7.
//
// Example:
// Input: pizza = ["A..","AAA","..."], k = 3
// Output: 3 
// Explanation: The figure above shows the three ways to cut the pizza. Note that pieces must contain at least one apple.
//
// Constraints:
// 1 <= rows, cols <= 50
// 	rows == pizza.length
// 	cols == pizza[i].length
// 	1 <= k <= 10
// 	pizza consists of characters 'A' and '.' only.
//

class Solution {
public:
    int ways(vector<string>& pizza, int k) {
        int MOD = 1e9 + 7;
        int rows = pizza.size();
        int cols = pizza[0].size();
        
        // Precompute prefix sums for apples
        vector<vector<int>> prefix(rows + 1, vector<int>(cols + 1, 0));
        for (int r = rows - 1; r >= 0; r--) {
            for (int c = cols - 1; c >= 0; c--) {
                prefix[r][c] = prefix[r + 1][c] + prefix[r][c + 1] - prefix[r + 1][c + 1] + (pizza[r][c] == 'A' ? 1 : 0);
            }
        }
        
        // DP array
        vector<vector<vector<int>>> dp(k + 1, vector<vector<int>>(rows, vector<int>(cols, 0)));
        
        // Base case: k = 1
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                dp[1][r][c] = (prefix[r][c] > 0) ? 1 : 0;
            }
        }
        
        // Fill DP table
        for (int cuts = 2; cuts <= k; cuts++) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    // Horizontal cuts
                    for (int nr = r + 1; nr < rows; nr++) {
                        if (prefix[r][c] - prefix[nr][c] > 0) { // at least one apple in upper part
                            dp[cuts][r][c] = (dp[cuts][r][c] + dp[cuts - 1][nr][c]) % MOD;
                        }
                    }
                    // Vertical cuts
                    for (int nc = c + 1; nc < cols; nc++) {
                        if (prefix[r][c] - prefix[r][nc] > 0) { // at least one apple in left part
                            dp[cuts][r][c] = (dp[cuts][r][c] + dp[cuts - 1][r][nc]) % MOD;
                        }
                    }
                }  
            }
                     
        }
        
        return dp[k][0][0];
    }
};
