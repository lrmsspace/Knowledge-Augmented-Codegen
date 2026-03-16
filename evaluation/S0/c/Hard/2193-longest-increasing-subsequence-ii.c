// Source: https://leetcode.com/problems/longest-increasing-subsequence-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// Find the longest subsequence of nums that meets the following requirements:
//
//
// 	The subsequence is strictly increasing and
// 	The difference between adjacent elements in the subsequence is at most k.
//
//
// Return the length of the longest subsequence that meets the requirements.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [4,2,1,4,3,4,5,8,15], k = 3
// Output: 5
// Explanation:
// The longest subsequence that meets the requirements is [1,3,4,5,8].
// The subsequence has a length of 5, so we return 5.
// Note that the subsequence [1,3,4,5,8,15] does not meet the requirements because 15 - 8 = 7 is larger than 3.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i], k <= 105
//

int lengthOfLIS(int* nums, int numsSize, int k) {
    if (numsSize <= 0) return 0;

    int maxNum = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] > maxNum) maxNum = nums[i];
    }

    int *dp = (int*)calloc(maxNum + 1, sizeof(int));
    if (!dp) return 0;

    int res = 1;
    for (int i = 0; i < numsSize; ++i) {
        int val = nums[i];
        int start = val - k > 0 ? val - k : 0;
        int best = 0;
        for (int j = start; j < val; ++j) {
            if (dp[j] > best) best = dp[j];
        }
        dp[val] = best + 1;
        if (dp[val] > res) res = dp[val];
    }

    free(dp);
    return res;     
}
