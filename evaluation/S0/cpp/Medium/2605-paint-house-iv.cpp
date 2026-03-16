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
public:
    long long minCost(int n, vector<vector<int>>& cost) {
        vector<vector<long long>> dp(n, vector<long long>(3, LLONG_MAX));

        // Initialize the first house
        for (int color = 0; color < 3; ++color) {
            dp[0][color] = cost[0][color];
        }

        // Fill the dp table
        for (int i = 1; i < n; ++i) {
            for (int color = 0; color < 3; ++color) {
                for (int prevColor = 0; prevColor < 3; ++prevColor) {
                    if (color != prevColor) {
                        // Check the equidistant house condition
                        if (i < n / 2 || color != dp[n - i - 1].index(min_element(dp[n - i - 1].begin(), dp[n - i - 1].end()))) {
                            dp[i][color] = min(dp[i][color], dp[i - 1][prevColor] + cost[i][color]);
                        }
                    }
                }
            }
        }

        // Find the minimum cost from the last house
        long long minCost = LLONG_MAX;
        for (int color = 0; color < 3; ++color) {
            minCost = min(minCost, dp[n - 1][color]);
        }

        return minCost;         
    }
};
