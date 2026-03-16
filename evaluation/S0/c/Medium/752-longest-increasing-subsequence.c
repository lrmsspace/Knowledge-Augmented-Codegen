// Source: https://leetcode.com/problems/longest-increasing-subsequence/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the length of the longest strictly increasing subsequence.
//
// Example:
// Input: nums = [10,9,2,5,3,7,101,18]
// Output: 4
// Explanation: The longest increasing subsequence is [2,3,7,101], therefore the length is 4.
//
// Constraints:
// 1 <= nums.length <= 2500
// 	-104 <= nums[i] <= 104
//
//
//  
// Follow up: Can you come up with an algorithm that runs in O(n log(n)) time complexity?
//

int lengthOfLIS(int* nums, int numsSize) {
    if (numsSize == 0) return 0;

    int* dp = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1;
    }

    int maxLen = 1;
    for (int i = 1; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[i] > nums[j]) {
                dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
            }
        }
        maxLen = maxLen > dp[i] ? maxLen : dp[i];
    }

    free(dp);
    return maxLen;      
}
