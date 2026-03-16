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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int profitableSchemes(int n, int minProfit, int[] group, int[] profit) {
        int mod = 1_000_000_007;
        int[][] dp = new int[n + 1][minProfit + 1];
        dp[0][0] = 1; // Base case: one way to achieve zero profit with zero members

        for (int i = 0; i < group.length; i++) {
            int membersRequired = group[i];
            int profitGenerated = profit[i];

            // Update the dp array in reverse order to avoid overwriting results
            for (int j = n; j >= membersRequired; j--) {
                for (int k = minProfit; k >= 0; k--) {
                    int newProfit = Math.min(k + profitGenerated, minProfit);
                    dp[j][newProfit] = (dp[j][newProfit] + dp[j - membersRequired][k]) % mod;
                }
            }
        }

        int result = 0;
        for (int j = 0; j <= n; j++) {
            result = (result + dp[j][minProfit]) % mod;
        }

        return result;          
    }
}
