// Source: https://leetcode.com/problems/maximum-difference-between-increasing-elements/   |   Difficulty: Easy
//
// Problem Description:
// Given a 0-indexed integer array nums of size n, find the maximum difference between nums[i] and nums[j] (i.e., nums[j] - nums[i]), such that 0 <= i < j < n and nums[i] < nums[j].
//
// Return the maximum difference. If no such i and j exists, return -1.
//
// Example:
// Input: nums = [7,1,5,4]
// Output: 4
// Explanation:
// The maximum difference occurs with i = 1 and j = 2, nums[j] - nums[i] = 5 - 1 = 4.
// Note that with i = 1 and j = 0, the difference nums[j] - nums[i] = 7 - 1 = 6, but i > j, so it is not valid.
//
// Constraints:
// n == nums.length
// 	2 <= n <= 1000
// 	1 <= nums[i] <= 109
//

int maximumDifference(int* nums, int numsSize) {
    int max_diff = -1;
    int min_value = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > min_value) {
            int diff = nums[i] - min_value;
            if (diff > max_diff) {
                max_diff = diff;
            }
        } else if (nums[i] < min_value) {
            min_value = nums[i];
        }
    }

    return max_diff;        
}
