// Source: https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums of 2 * n integers. You need to partition nums into two arrays of length n to minimize the absolute difference of the sums of the arrays. To partition nums, put each element of nums into one of the two arrays.
//
// Return the minimum possible absolute difference.
//
// Example:
// Input: nums = [3,9,7,3]
// Output: 2
// Explanation: One optimal partition is: [3,9] and [7,3].
// The absolute difference between the sums of the arrays is abs((3 + 9) - (7 + 3)) = 2.
//
// Constraints:
// 1 <= n <= 15
// 	nums.length == 2 * n
// 	-107 <= nums[i] <= 107
//

int minimumDifference(int* nums, int numsSize) {
    int n = numsSize / 2;
    int totalSum = 0;
    for (int i = 0; i < numsSize; ++i) {
        totalSum += nums[i];
    }

    int halfSum = totalSum / 2;
    int maxSubsetSize = n;
    int maxSum = halfSum + 1;

    // DP array to track achievable sums with specific subset sizes
    int **dp = (int **)malloc((maxSubsetSize + 1) * sizeof(int *));
    for (int i = 0; i <= maxSubsetSize; ++i) {
        dp[i] = (int *)calloc(maxSum, sizeof(int));
    }
    dp[0][0] = 1; // sum 0 is achievable with 0 elements

    for (int i = 0; i < numsSize; ++i) {
        int num = nums[i];
        for (int size = maxSubsetSize - 1; size >= 0; --size) {
            for (int sum = 0; sum + num < maxSum; ++sum) {
                if (dp[size][sum]) {
                    dp[size + 1][sum + num] = 1;
                }
            }
        }
    }

    int bestSum = 0;
    for (int sum = halfSum; sum >= 0; --sum) {
        if (dp[maxSubsetSize][sum]) {
            bestSum = sum;
            break;
        }
    }

    for (int i = 0; i <= maxSubsetSize; ++i) {
        free(dp[i]);
    }
    free(dp);

    return abs(totalSum - 2 * bestSum);     
}
