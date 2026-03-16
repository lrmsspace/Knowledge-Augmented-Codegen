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

int ways(char** pizza, int pizzaSize, int k) {
    const int MOD = 1000000007;
    int m = pizzaSize;
    int n = strlen(pizza[0]);

    // Precompute the number of apples in the submatrix from (i, j) to (m-1, n-1)
    int apples[m + 1][n + 1];
    memset(apples, 0, sizeof(apples));
    for (int i = m - 1; i >= 0; --i) {
        for (int j = n - 1; j >= 0; --j) {
            apples[i][j] = apples[i + 1][j] + apples[i][j + 1] - apples[i + 1][j + 1] + (pizza[i][j] == 'A' ? 1 : 0);
        }
    }

    // DP array: dp[cuts][i][j] = number of ways to cut pizza starting from (i, j) with 'cuts' cuts remaining
    int dp[k + 1][m + 1][n + 1];
    memset(dp, 0, sizeof(dp));
    dp[0][0][0] = 1;

    for (int cuts = 0; cuts < k - 1; ++cuts) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (dp[cuts][i][j] == 0) continue;

                // Horizontal cuts
                for (int x = i + 1; x < m; ++x) {
                    if (apples[i][j] - apples[x][j] > 0) {
                        dp[cuts + 1][x][j] = (dp[cuts + 1][x][j] + dp[cuts][i][j]) % MOD;
                    }
                }

                // Vertical cuts
                for (int y = j + 1; y < n; ++y) {
                    if (apples[i][j] - apples[i][y] > 0) {
                        dp[cuts + 1][i][y] = (dp[cuts + 1][i][y] + dp[cuts][i][j]) % MOD;
                    }
                }
            }
        }
    }
    int result = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (apples[i][j] > 0) {
                result = (result + dp[k - 1][i][j]) % MOD;
            }
        }
    }
    return result;
}
