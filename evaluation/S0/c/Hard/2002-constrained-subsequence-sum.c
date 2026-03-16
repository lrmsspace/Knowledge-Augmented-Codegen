// Source: https://leetcode.com/problems/constrained-subsequence-sum/   |   Difficulty: Hard
//
// Problem Description:
// Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.
//
// A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.
//
// Example:
// Input: nums = [10,2,-10,5,20], k = 2
// Output: 37
// Explanation: The subsequence is [10, 2, 5, 20].
//
// Constraints:
// 1 <= k <= nums.length <= 105
// 	-104 <= nums[i] <= 104
//

int constrainedSubsetSum(int* nums, int numsSize, int k) {
    int *dp = (int*)malloc(numsSize * sizeof(int));
    if (!dp) return 0; /* allocation failure */

    /* Deque for maintaining indices of maximum dp values in the current window */
    int *deque = (int*)malloc(numsSize * sizeof(int));
    if (!deque) { free(dp); return 0; } /* allocation failure */
    int front = 0, back = 0;

    int maxSum = nums[0];
    for (int i = 0; i < numsSize; ++i) {
        /* Remove indices from front that are out of the current window */
        while (front < back && deque[front] < i - k) {
            front++;
        }

        /* Calculate dp[i] */
        int bestPrev = (front < back) ? dp[deque[front]] : 0;
        dp[i] = nums[i] + (bestPrev > 0 ? bestPrev : 0);
        if (dp[i] > maxSum) {
            maxSum = dp[i];
        }

        /* Maintain deque: remove from back while dp[i] is greater */
        while (front < back && dp[deque[back - 1]] <= dp[i]) {
            back--;
        }
        deque[back++] = i;
    }

    free(dp);
    free(deque);
    return maxSum;      
}
