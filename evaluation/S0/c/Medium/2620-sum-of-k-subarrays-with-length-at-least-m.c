// Source: https://leetcode.com/problems/sum-of-k-subarrays-with-length-at-least-m/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and two integers, k and m.
//
// Return the maximum sum of k non-overlapping subarrays of nums, where each subarray has a length of at least m.
//
// Example:
// Input: nums = [1,2,-1,3,3,4], k = 2, m = 2
//
// Output: 13
//
// Explanation:
//
// The optimal choice is:
//
//
// 	Subarray nums[3..5] with sum 3 + 3 + 4 = 10 (length is 3 >= m).
// 	Subarray nums[0..1] with sum 1 + 2 = 3 (length is 2 >= m).
//
//
// The total sum is 10 + 3 = 13.
//
// Constraints:
// 1 <= nums.length <= 2000
// 	-104 <= nums[i] <= 104
// 	1 <= k <= floor(nums.length / m)
// 	1 <= m <= 3
//

int maxSum(int* nums, int numsSize, int k, int m) {
    int prefixSum[numsSize + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + nums[i];
    }

    int dp[k + 1][numsSize + 1];
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= numsSize; j++) {
            dp[i][j] = (i == 0) ? 0 : -2147483648; // INT_MIN
        }
    }

    for (int i = 1; i <= k; i++) {
        for (int j = i * m; j <= numsSize; j++) {
            for (int l = m; l <= j - (i - 1) * m + 1; l++) {
                int currentSum = prefixSum[j] - prefixSum[j - l];
                if (dp[i - 1][j - l] + currentSum > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j - l] + currentSum;
                }
            }
        }
    }

    return dp[k][numsSize];     
}
