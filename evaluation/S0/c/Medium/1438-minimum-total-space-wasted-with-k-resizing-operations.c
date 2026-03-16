// Source: https://leetcode.com/problems/minimum-total-space-wasted-with-k-resizing-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are currently designing a dynamic array. You are given a 0-indexed integer array nums, where nums[i] is the number of elements that will be in the array at time i. In addition, you are given an integer k, the maximum number of times you can resize the array (to any size).
//
// The size of the array at time t, sizet, must be at least nums[t] because there needs to be enough space in the array to hold all the elements. The space wasted at time t is defined as sizet - nums[t], and the total space wasted is the sum of the space wasted across every time t where 0 <= t < nums.length.
//
// Return the minimum total space wasted if you can resize the array at most k times.
//
// Note: The array can have any size at the start and does not count towards the number of resizing operations.
//
// Example:
// Input: nums = [10,20], k = 0
// Output: 10
// Explanation: size = [20,20].
// We can set the initial size to be 20.
// The total wasted space is (20 - 10) + (20 - 20) = 10.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i] <= 106
// 	0 <= k <= nums.length - 1
//

int minSpaceWastedKResizing(int* nums, int numsSize, int k) {
    int dp[numsSize + 1][k + 2];
    for (int i = 0; i <= numsSize; i++) {
        for (int j = 0; j <= k + 1; j++) {
            dp[i][j] = 1000000000;
        }
    }
    dp[0][0] = 0;

    for (int i = 1; i <= numsSize; i++) {
        for (int j = 0; j <= k; j++) {
            int maxn = 0, sum = 0;
            for (int p = i; p >= 1; p--) {
                maxn = fmax(maxn, nums[p - 1]);
                sum += nums[p - 1];
                dp[i][j + 1] = fmin(dp[i][j + 1], dp[p - 1][j] + maxn * (i - p + 1) - sum);
            }
        }
    }

    return dp[numsSize][k + 1];     
}
