// Source: https://leetcode.com/problems/minimum-difference-between-highest-and-lowest-of-k-scores/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums, where nums[i] represents the score of the ith student. You are also given an integer k.
//
// Pick the scores of any k students from the array so that the difference between the highest and the lowest of the k scores is minimized.
//
// Return the minimum possible difference.
//
// Example:
// Input: nums = [90], k = 1
// Output: 0
// Explanation: There is one way to pick score(s) of one student:
// - [90]. The difference between the highest and lowest score is 90 - 90 = 0.
// The minimum possible difference is 0.
//
// Constraints:
// 1 <= k <= nums.length <= 1000
// 	0 <= nums[i] <= 105
//

int minimumDifference(int* nums, int numsSize, int k) {
    if (k == 1) {
        return 0;
    }

    // Sort the array
    for (int i = 0; i < numsSize - 1; i++) {
        for (int j = 0; j < numsSize - i - 1; j++) {
            if (nums[j] > nums[j + 1]) {
                int temp = nums[j];
                nums[j] = nums[j + 1];
                nums[j + 1] = temp;
            }
        }
    }

    int minDiff = nums[numsSize - 1] - nums[0];
    for (int i = 0; i <= numsSize - k; i++) {
        int diff = nums[i + k - 1] - nums[i];
        if (diff < minDiff) {
            minDiff = diff;
        }
    }

    return minDiff;     
}
