// Source: https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/   |   Difficulty: Hard
//
// Problem Description:
// You have a pointer at index 0 in an array of size arrLen. At each step, you can move 1 position to the left, 1 position to the right in the array, or stay in the same place (The pointer should not be placed outside the array at any time).
//
// Given two integers steps and arrLen, return the number of ways such that your pointer is still at index 0 after exactly steps steps. Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: steps = 3, arrLen = 2
// Output: 4
// Explanation: There are 4 differents ways to stay at index 0 after 3 steps.
// Right, Left, Stay
// Stay, Right, Left
// Right, Stay, Left
// Stay, Stay, Stay
//
// Constraints:
// 1 <= steps <= 500
// 	1 <= arrLen <= 106
//

class Solution {
    public int numWays(int steps, int arrLen) {
        int MOD = 1_000_000_007;
        int maxPos = Math.min(steps / 2 + 1, arrLen);
        int[] dp = new int[maxPos];
        dp[0] = 1;

        for (int step = 1; step <= steps; step++) {
            int[] newDp = new int[maxPos];
            for (int pos = 0; pos < maxPos; pos++) {
                newDp[pos] = dp[pos]; // stay
                if (pos - 1 >= 0) {
                    newDp[pos] = (newDp[pos] + dp[pos - 1]) % MOD; // left
                }
                if (pos + 1 < maxPos) {
                    newDp[pos] = (newDp[pos] + dp[pos + 1]) % MOD; // right
                }
            }
            dp = newDp;
        }

        return dp[0];                   
    }
}
