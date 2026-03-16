// Source: https://leetcode.com/problems/partition-array-for-maximum-sum/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr, partition the array into (contiguous) subarrays of length at most k. After partitioning, each subarray has their values changed to become the maximum value of that subarray.
//
// Return the largest sum of the given array after partitioning. Test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: arr = [1,15,7,9,2,5,10], k = 3
// Output: 84
// Explanation: arr becomes [15,15,15,9,10,10,10]
//
// Constraints:
// 1 <= arr.length <= 500
// 	0 <= arr[i] <= 109
// 	1 <= k <= arr.length
//

int maxSumAfterPartitioning(int* arr, int arrSize, int k) {
    int dp[arrSize + 1];
    dp[0] = 0;

    for (int i = 1; i <= arrSize; i++) {
        int maxVal = arr[i - 1];
        dp[i] = 0;

        for (int j = 1; j <= k && i - j >= 0; j++) {
            if (arr[i - j] > maxVal) {
                maxVal = arr[i - j];
            }
            int currentSum = dp[i - j] + maxVal * j;
            if (currentSum > dp[i]) {
                dp[i] = currentSum;
            }
        }
    }

    return dp[arrSize];     
}
