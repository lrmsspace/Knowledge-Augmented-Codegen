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
    public int numberOfWays(int startPos, int endPos, int k) {
        int mod = 1_000_000_007;
        int distance = Math.abs(endPos - startPos);

        // If the distance is greater than k, it's impossible to reach the target
        if (distance > k) {
            return 0;
        }

        // If the parity of the distance and k is different, it's also impossible
        if ((distance % 2) != (k % 2)) {
            return 0;
        }

        // Calculate the number of steps to the right (r) and left (l)
        int r = (k + distance) / 2; // Steps to the right
        int l = k - r;               // Steps to the left

        // Calculate C(k, r) using a dynamic programming approach
        long[][] dp = new long[k + 1][r + 1];
        for (int i = 0; i <= k; i++) {
            dp[i][0] = 1; // C(i, 0) = 1
            for (int j = 1; j <= Math.min(i, r); j++) {
                dp[i][j] = (dp[i - 1][j - 1] + dp[i - 1][j]) % mod; // C(i, j) = C(i-1, j-1) + C(i-1, j)
            }
        }

        return (int) dp[k][r];          
    }
}
