// Source: https://leetcode.com/problems/special-permutations/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums containing n distinct positive integers. A permutation of nums is called special if:
//
//
// 	For all indexes 0 <= i < n - 1, either nums[i] % nums[i+1] == 0 or nums[i+1] % nums[i] == 0.
//
//
// Return the total number of special permutations. As the answer could be large, return it modulo 109 + 7.
//
// Example:
// Input: nums = [2,3,6]
// Output: 2
// Explanation: [3,6,2] and [2,6,3] are the two special permutations of nums.
//
// Constraints:
// 2 <= nums.length <= 14
// 	1 <= nums[i] <= 109
//

int specialPerm(int* nums, int numsSize) {
    #define MOD 1000000007
    int graph[numsSize][numsSize];
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            graph[i][j] = (nums[i] % nums[j] == 0 || nums[j] % nums[i] == 0) ? 1 : 0;
        }
    }

    int dp[1 << numsSize][numsSize];
    for (int mask = 0; mask < (1 << numsSize); mask++) {
        for (int i = 0; i < numsSize; i++) {
            dp[mask][i] = 0;
        }
    }

    for (int i = 0; i < numsSize; i++) {
        dp[1 << i][i] = 1;
    }

    for (int mask = 1; mask < (1 << numsSize); mask++) {
        for (int u = 0; u < numsSize; u++) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < numsSize; v++) {
                if (mask & (1 << v)) continue;
                if (graph[u][v]) {
                    dp[mask | (1 << v)][v] = (dp[mask | (1 << v)][v] + dp[mask][u]) % MOD;
                }
            }
        }
    }

    int result = 0;
    for (int i = 0; i < numsSize; i++) {
        result = (result + dp[(1 << numsSize) - 1][i]) % MOD;
    }

    return result;      
}
