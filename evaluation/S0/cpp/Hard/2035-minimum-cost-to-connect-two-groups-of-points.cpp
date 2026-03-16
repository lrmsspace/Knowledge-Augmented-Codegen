// Source: https://leetcode.com/problems/minimum-cost-to-connect-two-groups-of-points/   |   Difficulty: Hard
//
// Problem Description:
// You are given two groups of points where the first group has size1 points, the second group has size2 points, and size1 >= size2.
//
// The cost of the connection between any two points are given in an size1 x size2 matrix where cost[i][j] is the cost of connecting point i of the first group and point j of the second group. The groups are connected if each point in both groups is connected to one or more points in the opposite group. In other words, each point in the first group must be connected to at least one point in the second group, and each point in the second group must be connected to at least one point in the first group.
//
// Return the minimum cost it takes to connect the two groups.
//
// Example:
// Input: cost = [[15, 96], [36, 2]]
// Output: 17
// Explanation: The optimal way of connecting the groups is:
// 1--A
// 2--B
// This results in a total cost of 17.
//
// Constraints:
// size1 == cost.length
// 	size2 == cost[i].length
// 	1 <= size1, size2 <= 12
// 	size1 >= size2
// 	0 <= cost[i][j] <= 100
//

class Solution {
public:
    int connectTwoGroups(vector<vector<int>>& cost) {
        int m = cost.size();
        int n = cost[0].size();
        int maxMask = 1 << n;
        
        vector<int> minCostForSecondGroup(n, INT_MAX);
        for (int j = 0; j < n; j++) {
            for (int i = 0; i < m; i++) {
                minCostForSecondGroup[j] = min(minCostForSecondGroup[j], cost[i][j]);
            }
        }
        
        vector<vector<int>> dp(m + 1, vector<int>(maxMask, INT_MAX));
        dp[0][0] = 0;
        
        for (int i = 1; i <= m; i++) {
            for (int mask = 0; mask < maxMask; mask++) {
                for (int j = 0; j < n; j++) {
                    int newMask = mask | (1 << j);
                    if (dp[i - 1][mask] != INT_MAX) {
                        dp[i][newMask] = min(dp[i][newMask], dp[i - 1][mask] + cost[i - 1][j]);
                    }
                }
            }
        }
        
        int result = INT_MAX;
        for (int mask = 0; mask < maxMask; mask++) {
            int totalCost = dp[m][mask];
            for (int j = 0; j < n; j++) {
                if ((mask & (1 << j)) == 0) {
                    totalCost += minCostForSecondGroup[j];
                }
            }
            result = min(result, totalCost);
        }
        
        return result;          
    }
};
