// Source: https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums.
//
// Return the maximum value over all triplets of indices (i, j, k) such that i < j < k. If all such triplets have a negative value, return 0.
//
// The value of a triplet of indices (i, j, k) is equal to (nums[i] - nums[j]) * nums[k].
//
// Example:
// Input: nums = [12,6,1,2,7]
// Output: 77
// Explanation: The value of the triplet (0, 2, 4) is (nums[0] - nums[2]) * nums[4] = 77.
// It can be shown that there are no ordered triplets of indices with a value greater than 77.
//
// Constraints:
// 3 <= nums.length <= 105
// 	1 <= nums[i] <= 106
//

long long maximumTripletValue(int* nums, int numsSize) {
    long long max_value = 0;
    int max_num = nums[numsSize - 1];
    int min_num = nums[0];

    for (int j = numsSize - 2; j > 0; j--) {
        long long current_value = (long long)(max_num - min_num) * nums[j];
        if (current_value > max_value) {
            max_value = current_value;
        }
        if (nums[j] > max_num) {
            max_num = nums[j];
        }
        if (nums[j - 1] < min_num) {
            min_num = nums[j - 1];
        }
    }

    return max_value;       
}
