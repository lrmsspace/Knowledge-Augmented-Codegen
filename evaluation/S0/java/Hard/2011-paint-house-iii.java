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

class Solution {
    public int minCost(int[] houses, int[][] cost, int m, int n, int target) {
        int MAX = Integer.MAX_VALUE / 2;
        int[][][] dp = new int[m + 1][n + 1][target + 1];

        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= target; k++) {
                    dp[i][j][k] = MAX;
                }
            }
        }

        dp[0][0][0] = 0;

        for (int i = 1; i <= m; i++) {
            int color = houses[i - 1];
            for (int j = 1; j <= n; j++) {
                for (int k = 1; k <= target; k++) {
                    if (color != 0 && color != j) {
                        continue;
                    }
                    int currCost = (color == 0) ? cost[i - 1][j - 1] : 0;
                    for (int p = 1; p <= n; p++) {
                        if (p == j) {
                            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][p][k] + currCost);
                        } else {
                            dp[i][j][k] = Math.min(dp[i][j][k], dp[i - 1][p][k - 1] + currCost);
                        }
                    }
                }
            }
        }

        int result = MAX;
        for (int j = 1; j <= n; j++) {
            result = Math.min(result, dp[m][j][target]);
        }

        return result == MAX ? -1 : result;                 
    }
}
