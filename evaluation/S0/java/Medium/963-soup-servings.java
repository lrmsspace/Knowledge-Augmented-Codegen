// Source: https://leetcode.com/problems/soup-servings/   |   Difficulty: Medium
//
// Problem Description:
// You have two soups, A and B, each starting with n mL. On every turn, one of the following four serving operations is chosen at random, each with probability 0.25 independent of all previous turns:
//
//
// 	pour 100 mL from type A and 0 mL from type B
// 	pour 75 mL from type A and 25 mL from type B
// 	pour 50 mL from type A and 50 mL from type B
// 	pour 25 mL from type A and 75 mL from type B
//
//
// Note:
//
//
// 	There is no operation that pours 0 mL from A and 100 mL from B.
// 	The amounts from A and B are poured simultaneously during the turn.
// 	If an operation asks you to pour more than you have left of a soup, pour all that remains of that soup.
//
//
// The process stops immediately after any turn in which one of the soups is used up.
//
// Return the probability that A is used up before B, plus half the probability that both soups are used up in the same turn. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: n = 50
// Output: 0.62500
// Explanation: 
// If we perform either of the first two serving operations, soup A will become empty first.
// If we perform the third operation, A and B will become empty at the same time.
// If we perform the fourth operation, B will become empty first.
// So the total probability of A becoming empty first plus half the probability that A and B become empty at the same time, is 0.25 * (1 + 1 + 0.5 + 0) = 0.625.
//
// Constraints:
// 0 <= n <= 109
//

class Solution {
    public double soupServings(int n) {
        if (n >= 4800) {
            return 1.0;
        }
        int size = (n + 24) / 25;
        double[][] dp = new double[size + 1][size + 1];
        dp[0][0] = 0.5;
        for (int i = 1; i <= size; i++) {
            dp[0][i] = 1.0;
        }
        for (int i = 1; i <= size; i++) {
            for (int j = 1; j <= size; j++) {
                dp[i][j] = 0.25 * (dp[Math.max(0, i - 4)][j] +
                                  dp[Math.max(0, i - 3)][Math.max(0, j - 1)] +
                                  dp[Math.max(0, i - 2)][Math.max(0, j - 2)] +
                                  dp[Math.max(0, i - 1)][Math.max(0, j - 3)]);
            }
        }
        return dp[size][size];          
    }
}
