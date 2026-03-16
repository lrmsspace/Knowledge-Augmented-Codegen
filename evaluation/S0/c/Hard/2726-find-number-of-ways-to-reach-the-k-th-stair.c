// Source: https://leetcode.com/problems/find-number-of-ways-to-reach-the-k-th-stair/   |   Difficulty: Hard
//
// Problem Description:
// You are given a non-negative integer k. There exists a staircase with an infinite number of stairs, with the lowest stair numbered 0.
//
// Alice has an integer jump, with an initial value of 0. She starts on stair 1 and wants to reach stair k using any number of operations. If she is on stair i, in one operation she can:
//
//
// 	Go down to stair i - 1. This operation cannot be used consecutively or on stair 0.
// 	Go up to stair i + 2jump. And then, jump becomes jump + 1.
//
//
// Return the total number of ways Alice can reach stair k.
//
// Note that it is possible that Alice reaches the stair k, and performs some operations to reach the stair k again.
//
// Example:
// Input: k = 0
//
// Output: 2
//
// Explanation:
//
// The 2 possible ways of reaching stair 0 are:
//
//
// 	Alice starts at stair 1.
// 	
// 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
// 	
// 	
// 	Alice starts at stair 1.
// 	
// 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
// 		Using an operation of the second type, she goes up 20 stairs to reach stair 1.
// 		Using an operation of the first type, she goes down 1 stair to reach stair 0.
//
// Constraints:
// 0 <= k <= 109
//

int waysToReachStair(int k) {
    const int MOD = 1000000007;
    long long dp[2][450] = {0}; // dp[i][j]: number of ways to reach stair i with jump j
    dp[1][0] = 1; // start at stair 1 with jump 0

    for (int stair = 1; stair <= k + 200; ++stair) {
        int curr = stair % 2;
        int prev = 1 - curr;
        memset(dp[curr], 0, sizeof(dp[curr]));

        for (int jump = 0; jump < 450; ++jump) {
            // Move up to stair + 2 * jump
            int nextStair = stair + 2 * jump;
            if (nextStair <= k + 200) {
                dp[nextStair % 2][jump + 1] = (dp[nextStair % 2][jump + 1] + dp[prev][jump]) % MOD;
            }

            // Move down to stair - 1
            if (stair > 0 && jump > 0) {
                dp[(stair - 1) % 2][jump - 1] = (dp[(stair - 1) % 2][jump - 1] + dp[prev][jump]) % MOD;
            }
        }
    }

    long long result = 0;
    for (int jump = 0; jump < 450; ++jump) {
        result = (result + dp[k % 2][jump]) % MOD;
    }

    return (int)result;     
}
