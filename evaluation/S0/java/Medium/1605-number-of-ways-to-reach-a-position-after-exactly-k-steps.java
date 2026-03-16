// Source: https://leetcode.com/problems/number-of-ways-to-reach-a-position-after-exactly-k-steps/   |   Difficulty: Medium
//
// Problem Description:
// You are given two positive integers startPos and endPos. Initially, you are standing at position startPos on an infinite number line. With one step, you can move either one position to the left, or one position to the right.
//
// Given a positive integer k, return the number of different ways to reach the position endPos starting from startPos, such that you perform exactly k steps. Since the answer may be very large, return it modulo 109 + 7.
//
// Two ways are considered different if the order of the steps made is not exactly the same.
//
// Note that the number line includes negative integers.
//
// Example:
// Input: startPos = 1, endPos = 2, k = 3
// Output: 3
// Explanation: We can reach position 2 from 1 in exactly 3 steps in three ways:
// - 1 -> 2 -> 3 -> 2.
// - 1 -> 2 -> 1 -> 2.
// - 1 -> 0 -> 1 -> 2.
// It can be proven that no other way is possible, so we return 3.
//
// Constraints:
// 1 <= startPos, endPos, k <= 1000
//

class Solution {
    public int numberOfWays(int startPos, int endPos, int k) {
        int MOD = 1_000_000_007;
        int distance = Math.abs(endPos - startPos);
        
        // If the distance is greater than k or if the parity of distance and k is different, return 0
        if (distance > k || (k - distance) % 2 != 0) {
            return 0;
        }
        
        int rightSteps = (k + distance) / 2;
        
        // Calculate C(k, rightSteps) % MOD using dynamic programming
        long[][] dp = new long[k + 1][rightSteps + 1];
        
        for (int i = 0; i <= k; i++) {
            for (int j = 0; j <= Math.min(i, rightSteps); j++) {
                if (j == 0 || j == i) {
                    dp[i][j] = 1;
                } else {
                    dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % MOD;
                }
            }
        }
        
        return (int) dp[k][rightSteps];         
    }
}
