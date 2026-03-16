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
    public int ways(String[] pizza, int k) {
        int rows = pizza.length;
        int cols = pizza[0].length();
        int MOD = 1_000_000_007;

        int[][] apples = new int[rows + 1][cols + 1];
        for (int r = rows - 1; r >= 0; r--) {
            for (int c = cols - 1; c >= 0; c--) {
                apples[r][c] = apples[r + 1][c] + apples[r][c + 1] - apples[r + 1][c + 1] + (pizza[r].charAt(c) == 'A' ? 1 : 0);
            }
        }

        int[][] dp = new int[rows][cols];
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                dp[r][c] = apples[r][c] > 0 ? 1 : 0;
            }
        }

        for (int cut = 1; cut < k; cut++) {
            int[][] newDp = new int[rows][cols];
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < cols; c++) {
                    for (int nr = r + 1; nr < rows; nr++) {
                        if (apples[r][c] - apples[nr][c] > 0) {
                            newDp[r][c] = (newDp[r][c] + dp[nr][c]) % MOD;
                        }
                    }
                    for (int nc = c + 1; nc < cols; nc++) {
                        if (apples[r][c] - apples[r][nc] > 0) {
                            newDp[r][c] = (newDp[r][c] + dp[r][nc]) % MOD;
                        }
                    }
                }
            }
            dp = newDp;
        }

        return dp[0][0];                    
    }
}
