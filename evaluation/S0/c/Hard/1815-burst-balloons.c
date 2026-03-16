// Source: https://leetcode.com/problems/burst-balloons/   |   Difficulty: Hard
//
// Problem Description:
// You are given n balloons, indexed from 0 to n - 1. Each balloon is painted with a number on it represented by an array nums. You are asked to burst all the balloons.
//
// If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then treat it as if there is a balloon with a 1 painted on it.
//
// Return the maximum coins you can collect by bursting the balloons wisely.
//
// Example:
// Input: nums = [3,1,5,8]
// Output: 167
// Explanation:
// nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
// coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167
//
// Constraints:
// n == nums.length
// 	1 <= n <= 300
// 	0 <= nums[i] <= 100
//

int maxCoins(int* nums, int numsSize) {
    if (numsSize <= 0) return 0;

    int n = numsSize + 2;
    int *arr = (int*)malloc(n * sizeof(int));
    if (!arr) return 0;
    arr[0] = 1;
    arr[n - 1] = 1;
    for (int i = 0; i < numsSize; ++i) {
        arr[i + 1] = nums[i];
    }

    int **dp = (int**)malloc(n * sizeof(int*));
    if (!dp) { free(arr); return 0; }
    for (int i = 0; i < n; ++i) {
        dp[i] = (int*)calloc(n, sizeof(int));
        if (!dp[i]) {
            for (int j = 0; j < i; ++j) free(dp[j]);
            free(dp); free(arr); return 0;
        }
    }

    for (int length = 2; length < n; ++length) {
        for (int left = 0; left < n - length; ++left) {
            int right = left + length;
            for (int k = left + 1; k < right; ++k) {
                int coins = arr[left] * arr[k] * arr[right];
                coins += dp[left][k] + dp[k][right];
                if (coins > dp[left][right]) {
                    dp[left][right] = coins;
                }
            }
        }
    }

    int result = dp[0][n - 1];

    for (int i = 0; i < n; ++i) free(dp[i]);
    free(dp);
    free(arr);

    return result;      
}
