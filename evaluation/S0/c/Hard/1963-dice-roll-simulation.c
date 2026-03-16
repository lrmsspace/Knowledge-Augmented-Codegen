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

int dieSimulator(int n, int* rollMax, int rollMaxSize) {
    const int MOD = 1000000007;
    int dp[n + 1][6];
    memset(dp, 0, sizeof(dp));
    for (int j = 0; j < 6; ++j) {
        dp[1][j] = 1;
    }
    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < 6; ++j) {
            for (int k = 1; k <= rollMax[j]; ++k) {
                if (i - k < 0) break;
                int sum = 0;
                for (int m = 0; m < 6; ++m) {
                    if (m == j) continue;
                    sum = (sum + dp[i - k][m]) % MOD;
                }
                if (i - k == 0 && k == 1) {
                    sum = (sum + 1) % MOD;
                }
                dp[i][j] = (dp[i][j] + sum) % MOD;
            }
        }
    }
    int result = 0;
    for (int j = 0; j < 6; ++j) {
        result = (result + dp[n][j]) % MOD;
    }
    return result;      
}
