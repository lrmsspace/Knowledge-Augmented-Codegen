// Source: https://leetcode.com/problems/paint-house-iii/   |   Difficulty: Hard
//
// Problem Description:
// There is a row of m houses in a small city, each house must be painted with one of the n colors (labeled from 1 to n), some houses that have been painted last summer should not be painted again.
//
// A neighborhood is a maximal group of continuous houses that are painted with the same color.
//
//
// 	For example: houses = [1,2,2,3,3,2,1,1] contains 5 neighborhoods [{1}, {2,2}, {3,3}, {2}, {1,1}].
//
//
// Given an array houses, an m x n matrix cost and an integer target where:
//
//
// 	houses[i]: is the color of the house i, and 0 if the house is not painted yet.
// 	cost[i][j]: is the cost of paint the house i with the color j + 1.
//
//
// Return the minimum cost of painting all the remaining houses in such a way that there are exactly target neighborhoods. If it is not possible, return -1.
//
// Example:
// Input: houses = [0,0,0,0,0], cost = [[1,10],[10,1],[10,1],[1,10],[5,1]], m = 5, n = 2, target = 3
// Output: 9
// Explanation: Paint houses of this way [1,2,2,1,1]
// This array contains target = 3 neighborhoods, [{1}, {2,2}, {1,1}].
// Cost of paint all houses (1 + 1 + 1 + 1 + 5) = 9.
//
// Constraints:
// m == houses.length == cost.length
// 	n == cost[i].length
// 	1 <= m <= 100
// 	1 <= n <= 20
// 	1 <= target <= m
// 	0 <= houses[i] <= n
// 	1 <= cost[i][j] <= 104
//

int minCost(int* houses, int housesSize, int** cost, int costSize, int* costColSize, int m, int n, int target) {
    const int INF = 1000000000;
    int dp[m][n][target + 1];
    memset(dp, 0x3f, sizeof(dp));

    for (int j = 0; j < n; ++j) {
        if (houses[0] == 0 || houses[0] == j + 1) {
            dp[0][j][1] = (houses[0] == 0) ? cost[0][j] : 0;
        }
    }

    for (int i = 1; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (houses[i] != 0 && houses[i] != j + 1) continue;
            for (int k = 1; k <= target; ++k) {
                for (int pj = 0; pj < n; ++pj) {
                    if (pj == j) {
                        if (dp[i - 1][pj][k] < INF) {
                            int costToAdd = (houses[i] == 0) ? cost[i][j] : 0;
                            if (dp[i - 1][pj][k] + costToAdd < dp[i][j][k]) {
                                dp[i][j][k] = dp[i - 1][pj][k] + costToAdd;
                            }
                        }
                    } else {
                        if (k > 1 && dp[i - 1][pj][k - 1] < INF) {
                            int costToAdd = (houses[i] == 0) ? cost[i][j] : 0;
                            if (dp[i - 1][pj][k - 1] + costToAdd < dp[i][j][k]) {
                                dp[i][j][k] = dp[i - 1][pj][k - 1] + costToAdd;
                            }
                        }
                    }
                }
            }
        }
    }

    int ans = INF;
    for (int j = 0; j < n; ++j) {
        if (dp[m - 1][j][target] < ans) {
            ans = dp[m - 1][j][target];
        }
    }

    return (ans == INF) ? -1 : ans;     
}
