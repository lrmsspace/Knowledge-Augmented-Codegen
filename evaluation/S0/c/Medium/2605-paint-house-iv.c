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

long long minCost(int n, int** cost, int costSize, int* costColSize) {
    int dp[n][3];
    for (int j = 0; j < 3; j++) {
        dp[0][j] = cost[0][j];
    }

    for (int i = 1; i < n / 2; i++) {
        for (int j = 0; j < 3; j++) {
            dp[i][j] = cost[i][j] + fmin(dp[i - 1][(j + 1) % 3], dp[i - 1][(j + 2) % 3]);
        }
    }

    long long result = LLONG_MAX;
    for (int firstColor = 0; firstColor < 3; firstColor++) {
        for (int lastColor = 0; lastColor < 3; lastColor++) {
            if (firstColor == lastColor) continue;

            for (int midColor = 0; midColor < 3; midColor++) {
                if (midColor == lastColor) continue;

                long long totalCost = dp[n / 2 - 1][firstColor] + cost[n / 2][midColor];
                for (int i = n / 2 + 1; i < n; i++) {
                    int colorOptions[2];
                    int idx = 0;
                    for (int c = 0; c < 3; c++) {
                        if (c != midColor && c != lastColor) {
                            colorOptions[idx++] = c;
                        }
                    }
                    int chosenColor = colorOptions[0];
                    totalCost += cost[i][chosenColor];
                    midColor = chosenColor;
                }
                result = fmin(result, totalCost);
            }
        }
    }

    return result;      
}
