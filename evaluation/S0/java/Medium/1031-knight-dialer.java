// Source: https://leetcode.com/problems/knight-dialer/   |   Difficulty: Medium
//
// Problem Description:
// The chess knight has a unique movement, it may move two squares vertically and one square horizontally, or two squares horizontally and one square vertically (with both forming the shape of an L). The possible movements of chess knight are shown in this diagram:
//
// A chess knight can move as indicated in the chess diagram below:
//
// We have a chess knight and a phone pad as shown below, the knight can only stand on a numeric cell (i.e. blue cell).
//
// Given an integer n, return how many distinct phone numbers of length n we can dial.
//
// You are allowed to place the knight on any numeric cell initially and then you should perform n - 1 jumps to dial a number of length n. All jumps should be valid knight jumps.
//
// As the answer may be very large, return the answer modulo 109 + 7.
//
// Example:
// Input: n = 1
// Output: 10
// Explanation: We need to dial a number of length 1, so placing the knight over any numeric cell of the 10 cells is sufficient.
//
// Constraints:
// 1 <= n <= 5000
//

class Solution {
    public int knightDialer(int n) {
        int MOD = 1_000_000_007;
        int[][] moves = {
            {4, 6},    // from 0
            {6, 8},    // from 1
            {7, 9},    // from 2
            {4, 8},    // from 3
            {0, 3, 9}, // from 4
            {},        // from 5
            {0, 1, 7}, // from 6
            {2, 6},    // from 7
            {1, 3},    // from 8
            {2, 4}     // from 9
        };

        long[] dp = new long[10];
        for (int i = 0; i < 10; i++) {
            dp[i] = 1;
        }

        for (int hop = 1; hop < n; hop++) {
            long[] nextDp = new long[10];
            for (int digit = 0; digit <= 9; digit++) {
                for (int move : moves[digit]) {
                    nextDp[move] = (nextDp[move] + dp[digit]) % MOD;
                }
            }
            dp = nextDp;
        }

        long result = 0;
        for (long count : dp) {
            result = (result + count) % MOD;
        }

        return (int) result;            
    }
}
