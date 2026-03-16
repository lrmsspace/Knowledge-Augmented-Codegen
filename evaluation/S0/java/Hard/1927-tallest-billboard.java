// Source: https://leetcode.com/problems/tallest-billboard/   |   Difficulty: Hard
//
// Problem Description:
// You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.
//
// You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
//
// Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.
//
// Example:
// Input: rods = [1,2,3,6]
// Output: 6
// Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
//
// Constraints:
// 1 <= rods.length <= 20
// 	1 <= rods[i] <= 1000
// 	sum(rods[i]) <= 5000
//

class Solution {
    public int tallestBillboard(int[] rods) {
        int n = rods.length;
        int sum = 0;
        for (int rod : rods) {
            sum += rod;
        }

        int[][] dp = new int[n + 1][sum + 1];
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= sum; j++) {
                dp[i][j] = Integer.MIN_VALUE / 2;
            }
        }
        dp[0][0] = 0;

        for (int i = 1; i <= n; i++) {
            int rod = rods[i - 1];
            for (int j = 0; j <= sum; j++) {
                dp[i][j] = dp[i - 1][j];
                if (j - rod >= 0) {
                    dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - rod] + rod);
                }
                if (j + rod <= sum) {
                    dp[i][j] = Math.max(dp[i][j], dp[i - 1][j + rod]);
                }
            }
        }

        return dp[n][0];                    
    }
}
