// Source: https://leetcode.com/problems/greatest-sum-divisible-by-three/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums, return the maximum possible sum of elements of the array such that it is divisible by three.
//
// Example:
// Input: nums = [3,6,5,1,8]
// Output: 18
// Explanation: Pick numbers 3, 6, 1 and 8 their sum is 18 (maximum sum divisible by 3).
//
// Constraints:
// 1 <= nums.length <= 4 * 104
// 	1 <= nums[i] <= 104
//

int maxSumDivThree(int* nums, int numsSize) {
    int dp[3] = {0, INT_MIN, INT_MIN};

    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        int temp[3];
        for (int j = 0; j < 3; j++) {
            temp[j] = dp[j];
        }
        for (int j = 0; j < 3; j++) {
            int new_sum = temp[j] + num;
            int mod = new_sum % 3;
            if (new_sum > dp[mod]) {
                dp[mod] = new_sum;
            }
        }
    }

    return dp[0];       
}
