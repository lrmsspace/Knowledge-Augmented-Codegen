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

class Solution {
public:
    int waysToReachStair(int k) {
        const int MOD = 1e9 + 7;
        // dp[jump][pos] = number of ways to reach pos with current jump value
        // jump can be at most 45 because 2*0 + 2*1 + ... + 2*44 = 1980 < 1e9 < 2*45 + ...
        long long dp[46][1005] = {0};
        dp[0][1] = 1;  // start at stair 1 with jump=0
        
        for (int jump = 0; jump <= 44; jump++) {
            for (int pos = 0; pos <= k + 2 * jump; pos++) {
                if (dp[jump][pos] == 0) continue;
                
                // Operation 1: go down to pos-1
                if (pos > 0) {
                    dp[jump][pos - 1] = (dp[jump][pos - 1] + dp[jump][pos]) % MOD;
                }
                
                // Operation 2: go up to pos + 2*jump
                int newPos = pos + 2 * jump;
                if (newPos <= k + 2 * (jump + 1)) {
                    dp[jump + 1][newPos] = (dp[jump + 1][newPos] + dp[jump][pos]) % MOD;
                }
            }
        }
        
        // Sum all ways to reach stair k with any jump value
        long long result = 0;
        for (int jump = 0; jump <= 45; jump++) {
            result = (result + dp[jump][k]) % MOD;
        }
        
        return (int)result;         
    }
};
