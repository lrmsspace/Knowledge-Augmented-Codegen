// Source: https://leetcode.com/problems/maximum-ascending-subarray-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given an array of positive integers nums, return the maximum possible sum of an strictly increasing subarray in nums.
//
// A subarray is defined as a contiguous sequence of numbers in an array.
//
// Example:
// Input: nums = [10,20,30,5,10,50]
// Output: 65
// Explanation: [5,10,50] is the ascending subarray with the maximum sum of 65.
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
//

int maxAscendingSum(int* nums, int numsSize) {
    int max_sum = 0;
    int current_sum = nums[0];

    for (int i = 1; i < numsSize; i++) {
        if (nums[i] > nums[i - 1]) {
            current_sum += nums[i];
        } else {
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
            current_sum = nums[i];
        }
    }

    if (current_sum > max_sum) {
        max_sum = current_sum;
    }

    return max_sum;     
}
