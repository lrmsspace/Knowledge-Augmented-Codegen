// Source: https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, find three non-overlapping subarrays of length k with maximum sum and return them.
//
// Return the result as a list of indices representing the starting position of each interval (0-indexed). If there are multiple answers, return the lexicographically smallest one.
//
// Example:
// Input: nums = [1,2,1,2,6,7,5,1], k = 2
// Output: [0,3,5]
// Explanation: Subarrays [1, 2], [2, 6], [7, 5] correspond to the starting indices [0, 3, 5].
// We could have also taken [2, 1], but an answer of [1, 3, 5] would be lexicographically larger.
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] < 216
// 	1 <= k <= floor(nums.length / 3)
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSumOfThreeSubarrays(int* nums, int numsSize, int k, int* returnSize) {
    if (!returnSize || numsSize < 3 * k) return NULL;
    *returnSize = 3;
    int *res = (int*)malloc(3 * sizeof(int));
    if (!res) return NULL;

    int n = numsSize;
    int *sum = (int*)malloc((n - k + 1) * sizeof(int));
    if (!sum) { free(res); return NULL; }

    int windowSum = 0;
    for (int i = 0; i < k; ++i) windowSum += nums[i];
    sum[0] = windowSum;
    for (int i = 1; i <= n - k; ++i) {
        windowSum += nums[i + k - 1] - nums[i - 1];
        sum[i] = windowSum;
    }

    int *left = (int*)malloc((n - k + 1) * sizeof(int));
    int *right = (int*)malloc((n - k + 1) * sizeof(int));
    if (!left || !right) {
        free(res); free(sum); free(left); free(right);
        return NULL;
    }

    int bestLeft = 0;
    for (int i = 0; i <= n - k; ++i) {
        if (sum[i] > sum[bestLeft]) bestLeft = i;
        left[i] = bestLeft;
    }

    int bestRight = n - k;
    for (int i = n - k; i >= 0; --i) {
        if (sum[i] >= sum[bestRight]) bestRight = i;
        right[i] = bestRight;
    }

    int maxTotal = 0;
    for (int j = k; j <= n - 2 * k; ++j) {
        int i = left[j - k];
        int l = right[j + k];
        int total = sum[i] + sum[j] + sum[l];
        if (total > maxTotal) {
            maxTotal = total;
            res[0] = i; res[1] = j; res[2] = l;
        }
    }

    free(sum); free(left); free(right);
    return res;     
}
