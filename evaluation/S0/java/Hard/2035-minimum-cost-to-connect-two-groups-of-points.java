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
    public int connectTwoGroups(List<List<Integer>> cost) {
        int m = cost.size();
        int n = cost.get(0).size();
        int[] minCost2 = new int[n];
        for (int j = 0; j < n; j++) {
            int minCost = Integer.MAX_VALUE;
            for (int i = 0; i < m; i++) {
                minCost = Math.min(minCost, cost.get(i).get(j));
            }
            minCost2[j] = minCost;
        }

        int maxState = 1 << n;
        int[][] dp = new int[m + 1][maxState];
        for (int i = 0; i <= m; i++) {
            Arrays.fill(dp[i], Integer.MAX_VALUE);
        }
        dp[0][0] = 0;

        for (int i = 1; i <= m; i++) {
            for (int state = 0; state < maxState; state++) {
                for (int j = 0; j < n; j++) {
                    int prevState = state & ~(1 << j);
                    dp[i][state] = Math.min(dp[i][state],
                            dp[i - 1][prevState] + cost.get(i - 1).get(j));
                    dp[i][state] = Math.min(dp[i][state],
                            dp[i][state & ~(1 << j)] + cost.get(i - 1).get(j));
                }
            }
        }

        int result = Integer.MAX_VALUE;
        for (int state = 0; state < maxState; state++) {
            int totalCost = dp[m][state];
            for (int j = 0; j < n; j++) {
                if ((state & (1 << j)) == 0) {
                    totalCost += minCost2[j];
                }
            }
            result = Math.min(result, totalCost);
        }

        return result;                  
    }
}
