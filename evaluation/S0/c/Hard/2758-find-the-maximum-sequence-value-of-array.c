// Source: https://leetcode.com/problems/find-the-maximum-sequence-value-of-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and a positive integer k.
//
// The value of a sequence seq of size 2 * x is defined as:
//
//
// 	(seq[0] OR seq[1] OR ... OR seq[x - 1]) XOR (seq[x] OR seq[x + 1] OR ... OR seq[2 * x - 1]).
//
//
// Return the maximum value of any subsequence of nums having size 2 * k.
//
// Example:
// Input: nums = [2,6,7], k = 1
//
// Output: 5
//
// Explanation:
//
// The subsequence [2, 7] has the maximum value of 2 XOR 7 = 5.
//
// Constraints:
// 2 <= nums.length <= 400
// 	1 <= nums[i] < 27
// 	1 <= k <= nums.length / 2
//

int maxValue(int* nums, int numsSize, int k) {
    int dp[201][201] = {0}; // dp[i][j]: max value using first i elements with j pairs
    for (int i = 1; i <= numsSize; ++i) {
        for (int j = 0; j <= k; ++j) {
            // Not take nums[i-1]
            dp[i][j] = dp[i-1][j];
            // Take nums[i-1] as part of a new pair
            if (j > 0) {
                for (int p = 0; p < i - 1; ++p) {
                    int left_or = 0, right_or = 0;
                    for (int x = p; x < i - 1; ++x) left_or |= nums[x];
                    right_or = nums[i - 1];
                    int val = left_or ^ right_or;
                    if (dp[p][j - 1] + val > dp[i][j]) {
                        dp[i][j] = dp[p][j - 1] + val;
                    }
                }
            }
        }
    }
    return dp[numsSize][k];     
}
