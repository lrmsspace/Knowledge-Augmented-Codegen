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

int knightDialer(int n) {
    const int MOD = 1000000007;
    // Possible moves from each digit
    int moves[10][3] = {
        {4, 6, -1}, // from 0
        {6, 8, -1}, // from 1
        {7, 9, -1}, // from 2
        {4, 8, -1}, // from 3
        {3, 9, 0},  // from 4
        {-1, -1, -1}, // from 5 (no moves)
        {1, 7, 0},  // from 6
        {2, 6, -1}, // from 7
        {1, 3, -1}, // from 8
        {2, 4, -1}  // from 9
    };

    long dp[5001][10] = {0};

    // Base case: for length 1, there's one way to be on each digit
    for (int i = 0; i < 10; i++) {
        dp[1][i] = 1;
    }

    // Fill the dp table
    for (int len = 2; len <= n; len++) {
        for (int digit = 0; digit < 10; digit++) {
            for (int k = 0; k < 3; k++) {
                int next_digit = moves[digit][k];
                if (next_digit != -1) {
                    dp[len][digit] = (dp[len][digit] + dp[len - 1][next_digit]) % MOD;
                }
            }
        }
    }

    // Sum all ways to end on any digit for length n
    long result = 0;
    for (int i = 0; i < 10; i++) {
        result = (result + dp[n][i]) % MOD;
    }

    return (int)result;     
}
