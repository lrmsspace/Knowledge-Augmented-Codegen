// Source: https://leetcode.com/problems/minimum-operations-to-make-array-equal-to-target/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integer arrays nums and target, of the same length.
//
// In a single operation, you can select any subarray of nums and increment each element within that subarray by 1 or decrement each element within that subarray by 1.
//
// Return the minimum number of operations required to make nums equal to the array target.
//
// Example:
// Input: nums = [3,5,1,2], target = [4,6,2,4]
//
// Output: 2
//
// Explanation:
//
// We will perform the following operations to make nums equal to target:
// - Increment nums[0..3] by 1, nums = [4,6,2,3].
// - Increment nums[3..3] by 1, nums = [4,6,2,4].
//
// Constraints:
// 1 <= nums.length == target.length <= 105
// 	1 <= nums[i], target[i] <= 108
//

long long minimumOperations(int* nums, int numsSize, int* target, int targetSize) {
    long long res = 0;
    int diff[numsSize];
    for (int i = 0; i < numsSize; ++i) {
        diff[i] = target[i] - nums[i];
    }

    int prev = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (diff[i] != prev) {
            res += llabs(diff[i] - prev);
            prev = diff[i];
        }
    }

    return res;     
}
