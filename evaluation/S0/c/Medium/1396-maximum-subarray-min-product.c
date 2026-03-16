// Source: https://leetcode.com/problems/maximum-subarray-min-product/   |   Difficulty: Medium
//
// Problem Description:
// The min-product of an array is equal to the minimum value in the array multiplied by the array's sum.
//
//
// 	For example, the array [3,2,5] (minimum value is 2) has a min-product of 2 * (3+2+5) = 2 * 10 = 20.
//
//
// Given an array of integers nums, return the maximum min-product of any non-empty subarray of nums. Since the answer may be large, return it modulo 109 + 7.
//
// Note that the min-product should be maximized before performing the modulo operation. Testcases are generated such that the maximum min-product without modulo will fit in a 64-bit signed integer.
//
// A subarray is a contiguous part of an array.
//
// Example:
// Input: nums = [1,2,3,2]
// Output: 14
// Explanation: The maximum min-product is achieved with the subarray [2,3,2] (minimum value is 2).
// 2 * (2+3+2) = 2 * 7 = 14.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 107
//

int maxSumMinProduct(int* nums, int numsSize) {
    long long mod = 1e9 + 7;
    long long max_product = 0;

    long long prefix_sum[numsSize + 1];
    prefix_sum[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + nums[i];
    }

    int left[numsSize];
    int right[numsSize];

    // Find the nearest smaller element to the left
    int stack[numsSize];
    int top = -1;
    for (int i = 0; i < numsSize; i++) {
        while (top >= 0 && nums[stack[top]] >= nums[i]) {
            top--;
        }
        left[i] = (top == -1) ? -1 : stack[top];
        stack[++top] = i;
    }

    // Find the nearest smaller element to the right
    top = -1;
    for (int i = numsSize - 1; i >= 0; i--) {
        while (top >= 0 && nums[stack[top]] >= nums[i]) {
            top--;
        }
        right[i] = (top == -1) ? numsSize : stack[top];
        stack[++top] = i;
    }

    // Calculate max min-product
    for (int i = 0; i < numsSize; i++) {
        long long total_sum = prefix_sum[right[i]] - prefix_sum[left[i] + 1];
        long long min_product = total_sum * nums[i];
        if (min_product > max_product) {
            max_product = min_product;
        }
    }

    return (int)(max_product % mod);        
}
