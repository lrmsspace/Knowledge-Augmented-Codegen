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
public:
    int minCost(vector<int>& houses, vector<vector<int>>& cost, int m, int n, int target) {
        const int INF = 1e9;
        // dp[i][j][k]: min cost to paint first i houses with j neighborhoods, ending with color k
        vector<vector<vector<int>>> dp(m + 1, vector<vector<int>>(target + 1, vector<int>(n + 1, INF)));
        
        dp[0][0][0] = 0;  // No houses, no neighborhoods, no color
        
        for (int i = 1; i <= m; i++) {
            int houseColor = houses[i - 1];
            for (int j = 1; j <= target; j++) {
                for (int k = 1; k <= n; k++) {
                    if (houseColor != 0 && houseColor != k) {
                        // House already painted with different color
                        continue;
                    }
                    
                    int paintCost = (houseColor == 0) ? cost[i - 1][k - 1] : 0;
                    
                    for (int p = 1; p <= n; p++) {
                        if (p == k) {
                            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + paintCost);
                        } else {
                            dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j - 1][p] + paintCost);
                        }
                    }
                }
            }
        }
        
        int result = INF;
        for (int k = 1; k <= n; k++) {
            result = min(result, dp[m][target][k]);
        }
        
        return (result == INF) ? -1 : result;           
    }
};
