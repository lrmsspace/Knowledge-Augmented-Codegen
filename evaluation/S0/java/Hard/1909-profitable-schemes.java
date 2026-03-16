// Source: https://leetcode.com/problems/profitable-schemes/   |   Difficulty: Hard
//
// Problem Description:
// There is a group of n members, and a list of various crimes they could commit. The ith crime generates a profit[i] and requires group[i] members to participate in it. If a member participates in one crime, that member can't participate in another crime.
//
// Let's call a profitable scheme any subset of these crimes that generates at least minProfit profit, and the total number of members participating in that subset of crimes is at most n.
//
// Return the number of schemes that can be chosen. Since the answer may be very large, return it modulo 109 + 7.
//
// Example:
// Input: n = 5, minProfit = 3, group = [2,2], profit = [2,3]
// Output: 2
// Explanation: To make a profit of at least 3, the group could either commit crimes 0 and 1, or just crime 1.
// In total, there are 2 schemes.
//
// Constraints:
// 1 <= n <= 100
// 	0 <= minProfit <= 100
// 	1 <= group.length <= 100
// 	1 <= group[i] <= 100
// 	profit.length == group.length
// 	0 <= profit[i] <= 100
//

class Solution {
    public int profitableSchemes(int n, int minProfit, int[] group, int[] profit) {
        int MOD = 1_000_000_007;
        int m = group.length;
        int[][][] dp = new int[m + 1][n + 1][minProfit + 1];
        dp[0][0][0] = 1;

        for (int i = 1; i <= m; i++) {
            int membersNeeded = group[i - 1];
            int profitGenerated = profit[i - 1];

            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= minProfit; k++) {
                    dp[i][j][k] = dp[i - 1][j][k]; // Not committing the crime

                    if (j >= membersNeeded) {
                        int newProfit = Math.max(0, k - profitGenerated);
                        dp[i][j][k] = (dp[i][j][k] + dp[i - 1][j - membersNeeded][newProfit]) % MOD;
                    }
                }
            }
        }

        int result = 0;
        for (int j = 0; j <= n; j++) {
            result = (result + dp[m][j][minProfit]) % MOD;
        }

        return result;          
    }
}
