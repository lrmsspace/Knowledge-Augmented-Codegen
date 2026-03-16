// Source: https://leetcode.com/problems/dice-roll-simulation/   |   Difficulty: Hard
//
// Problem Description:
// A die simulator generates a random number from 1 to 6 for each roll. You introduced a constraint to the generator such that it cannot roll the number i more than rollMax[i] (1-indexed) consecutive times.
//
// Given an array of integers rollMax and an integer n, return the number of distinct sequences that can be obtained with exact n rolls. Since the answer may be too large, return it modulo 109 + 7.
//
// Two sequences are considered different if at least one element differs from each other.
//
// Example:
// Input: n = 2, rollMax = [1,1,2,2,2,3]
// Output: 34
// Explanation: There will be 2 rolls of die, if there are no constraints on the die, there are 6 * 6 = 36 possible combinations. In this case, looking at rollMax array, the numbers 1 and 2 appear at most once consecutively, therefore sequences (1,1) and (2,2) cannot occur, so the final answer is 36-2 = 34.
//
// Constraints:
// 1 <= n <= 5000
// 	rollMax.length == 6
// 	1 <= rollMax[i] <= 15
//

class Solution {
    public int dieSimulator(int n, int[] rollMax) {
        int MOD = 1_000_000_007;
        int[][] dp = new int[n + 1][6];
        int[] sum = new int[n + 1];

        for (int i = 0; i < 6; i++) {
            dp[1][i] = 1;
        }
        sum[1] = 6;

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < 6; j++) {
                dp[i][j] = sum[i - 1];

                if (i - rollMax[j] - 1 >= 0) {
                    dp[i][j] = (dp[i][j] - (sum[i - rollMax[j] - 1] - dp[i - rollMax[j] - 1][j]) + MOD) % MOD;
                } else if (i - rollMax[j] - 1 == -1) {
                    dp[i][j] = (dp[i][j] - 1 + MOD) % MOD;
                }
            }

            sum[i] = 0;
            for (int j = 0; j < 6; j++) {
                sum[i] = (sum[i] + dp[i][j]) % MOD;
            }
        }

        return sum[n];                  
    }
}
