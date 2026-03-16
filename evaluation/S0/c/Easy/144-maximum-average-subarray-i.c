// Source: https://leetcode.com/problems/maximum-average-subarray-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums consisting of n elements, and an integer k.
//
// Find a contiguous subarray whose length is equal to k that has the maximum average value and return this value. Any answer with a calculation error less than 10-5 will be accepted.
//
// Example:
// Input: nums = [1,12,-5,-6,50,3], k = 4
// Output: 12.75000
// Explanation: Maximum average is (12 - 5 - 6 + 50) / 4 = 51 / 4 = 12.75
//
// Constraints:
// n == nums.length
// 	1 <= k <= n <= 105
// 	-104 <= nums[i] <= 104
//

double findMaxAverage(int* nums, int numsSize, int k) {
    double max_sum = 0.0;
    double current_sum = 0.0;

    // Calculate the sum of the first 'k' elements
    for (int i = 0; i < k; i++) {
        current_sum += nums[i];
    }
    max_sum = current_sum;

    // Use a sliding window to calculate the sum of each subarray of size 'k'
    for (int i = k; i < numsSize; i++) {
        current_sum += nums[i] - nums[i - k];
        if (current_sum > max_sum) {
            max_sum = current_sum;
        }
    }

    // Return the maximum average
    return max_sum / k;     
}
