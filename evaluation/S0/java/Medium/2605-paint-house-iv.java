// Source: https://leetcode.com/problems/paint-house-iv/   |   Difficulty: Medium
//
// Problem Description:
// You are given an even integer n representing the number of houses arranged in a straight line, and a 2D array cost of size n x 3, where cost[i][j] represents the cost of painting house i with color j + 1.
//
// The houses will look beautiful if they satisfy the following conditions:
//
//
// 	No two adjacent houses are painted the same color.
// 	Houses equidistant from the ends of the row are not painted the same color. For example, if n = 6, houses at positions (0, 5), (1, 4), and (2, 3) are considered equidistant.
//
//
// Return the minimum cost to paint the houses such that they look beautiful.
//
// Example:
// Input: n = 4, cost = [[3,5,7],[6,2,9],[4,8,1],[7,3,5]]
//
// Output: 9
//
// Explanation:
//
// The optimal painting sequence is [1, 2, 3, 2] with corresponding costs [3, 2, 1, 3]. This satisfies the following conditions:
//
//
// 	No adjacent houses have the same color.
// 	Houses at positions 0 and 3 (equidistant from the ends) are not painted the same color (1 != 2).
// 	Houses at positions 1 and 2 (equidistant from the ends) are not painted the same color (2 != 3).
//
//
// The minimum cost to paint the houses so that they look beautiful is 3 + 2 + 1 + 3 = 9.
//
// Constraints:
// 2 <= n <= 105
// 	n is even.
// 	cost.length == n
// 	cost[i].length == 3
// 	0 <= cost[i][j] <= 105
//

class Solution {
    public long minCost(int n, int[][] cost) {
        long[][] dp = new long[n / 2][3];

        // Base case for the first pair of houses
        for (int color1 = 0; color1 < 3; color1++) {
            for (int color2 = 0; color2 < 3; color2++) {
                if (color1 != color2) {
                    dp[0][color1] = Math.min(dp[0][color1], cost[0][color1] + cost[n - 1][color2]);
                }
            }
        }

        // Fill the DP table
        for (int i = 1; i < n / 2; i++) {
            for (int color1 = 0; color1 < 3; color1++) {
                dp[i][color1] = Long.MAX_VALUE;
                for (int color2 = 0; color2 < 3; color2++) {
                    if (color1 != color2) {
                        dp[i][color1] = Math.min(dp[i][color1],
                                dp[i - 1][color2] + cost[i][color1] + cost[n - 1 - i][getThirdColor(color1, color2)]);
                    }
                }
            }
        }

        // Find the minimum cost from the last pair of houses
        long minCost = Long.MAX_VALUE;
        for (int color = 0; color < 3; color++) {
            minCost = Math.min(minCost, dp[n / 2 - 1][color]);
        }

        return minCost;         
    }
}
