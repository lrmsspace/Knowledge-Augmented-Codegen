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
    public int waysToReachStair(int k) {
        int MOD = 1_000_000_007;
        long res = 0;
        for (int n = 1; ; n++) {
            long jumpSum = (long) n * (n - 1);
            if (jumpSum / 2 > k + 1) break;
            if ((k + 1 - jumpSum / 2) % n == 0) {
                res = (res + nCr(k + 1 - jumpSum / 2 + n - 1, n - 1, MOD)) % MOD;
            }
        }
        return (int) res;           
    }
}
