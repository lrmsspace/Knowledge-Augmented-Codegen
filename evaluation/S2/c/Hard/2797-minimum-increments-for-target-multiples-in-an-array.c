// Source: https://leetcode.com/problems/minimum-increments-for-target-multiples-in-an-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays, nums and target.
//
// In a single operation, you may increment any element of nums by 1.
//
// Return the minimum number of operations required so that each element in target has at least one multiple in nums.
//
// Example:
// Input: nums = [1,2,3], target = [4]
//
// Output: 1
//
// Explanation:
//
// The minimum number of operations required to satisfy the condition is 1.
//
//
// 	Increment 3 to 4 with just one operation, making 4 a multiple of itself.
//
// Constraints:
// 1 <= nums.length <= 5 * 104
// 	1 <= target.length <= 4
// 	target.length <= nums.length
// 	1 <= nums[i], target[i] <= 104
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minimumIncrements(int* nums, int numsSize, int* target, int targetSize) {
    // Sort the nums array
    qsort(nums, numsSize, sizeof(int), compare);

    int increments = 0;

    // For each target element, find the smallest multiple in nums
    for (int i = 0; i < targetSize; i++) {
        int t = target[i];
        int found = 0;

        for (int j = 0; j < numsSize; j++) {
            if (nums[j] % t == 0) {
                found = 1;
                break;
            }
        }

        if (!found) {
            // If no multiple is found, we need to increment the largest number in nums
            increments += t - (nums[numsSize - 1] % t);
            nums[numsSize - 1] += increments; // Increment the largest number
        }
    }

    return increments;      
}
