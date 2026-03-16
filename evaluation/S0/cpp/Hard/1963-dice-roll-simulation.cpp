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
public:
    int dieSimulator(int n, vector<int>& rollMax) {
        const int MOD = 1e9 + 7;
        // dp[i][j][k]: number of sequences of length i, ending with j, with k consecutive j's
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(7, vector<long long>(16, 0)));
        
        // Base case: sequences of length 1
        for (int j = 1; j <= 6; j++) {
            dp[1][j][1] = 1;
        }
        
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= 6; j++) {
                for (int k = 1; k <= rollMax[j - 1]; k++) {
                    // If we continue the same number j
                    if (k > 1) {
                        dp[i][j][k] = dp[i - 1][j][k - 1];
                    }
                    // If we switch to number j from a different number
                    for (int m = 1; m <= 6; m++) {
                        if (m != j) {
                            for (int l = 1; l <= rollMax[m - 1]; l++) {
                                dp[i][j][1] = (dp[i][j][1] + dp[i - 1][m][l]) % MOD;
                            }
                        }
                    }
                }
            }
        }
        
        long long result = 0;
        for (int j = 1; j <= 6; j++) {
            for (int k = 1; k <= rollMax[j - 1]; k++) {
                result = (result + dp[n][j][k]) % MOD;
            }
        }
        
        return (int)result;         
    }
};
