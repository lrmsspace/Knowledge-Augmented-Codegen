// Source: https://leetcode.com/problems/maximum-or/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of length n and an integer k. In an operation, you can choose an element and multiply it by 2.
//
// Return the maximum possible value of nums[0] | nums[1] | ... | nums[n - 1] that can be obtained after applying the operation on nums at most k times.
//
// Note that a | b denotes the bitwise or between two integers a and b.
//
// Example:
// Input: nums = [12,9], k = 1
// Output: 30
// Explanation: If we apply the operation to index 1, our new array nums will be equal to [12,18]. Thus, we return the bitwise or of 12 and 18, which is 30.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= k <= 15
//

long long maximumOr(int* nums, int numsSize, int k) {
    long long prefix[numsSize];
    long long suffix[numsSize];
    long long result = 0;
    long long power = 1LL << k;

    prefix[0] = 0;
    for (int i = 1; i < numsSize; i++) {
        prefix[i] = prefix[i - 1] | nums[i - 1];
    }

    suffix[numsSize - 1] = 0;
    for (int i = numsSize - 2; i >= 0; i--) {
        suffix[i] = suffix[i + 1] | nums[i + 1];
    }

    for (int i = 0; i < numsSize; i++) {
        long long current = prefix[i] | (nums[i] * power) | suffix[i];
        if (current > result) {
            result = current;
        }
    }

    return result;      
}
