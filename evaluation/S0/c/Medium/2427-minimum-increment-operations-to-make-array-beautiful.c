// Source: https://leetcode.com/problems/minimum-increment-operations-to-make-array-beautiful/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums having length n, and an integer k.
//
// You can perform the following increment operation any number of times (including zero):
//
//
// 	Choose an index i in the range [0, n - 1], and increase nums[i] by 1.
//
//
// An array is considered beautiful if, for any subarray with a size of 3 or more, its maximum element is greater than or equal to k.
//
// Return an integer denoting the minimum number of increment operations needed to make nums beautiful.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,3,0,0,2], k = 4
// Output: 3
// Explanation: We can perform the following increment operations to make nums beautiful:
// Choose index i = 1 and increase nums[1] by 1 -> [2,4,0,0,2].
// Choose index i = 4 and increase nums[4] by 1 -> [2,4,0,0,3].
// Choose index i = 4 and increase nums[4] by 1 -> [2,4,0,0,4].
// The subarrays with a size of 3 or more are: [2,4,0], [4,0,0], [0,0,4], [2,4,0,0], [4,0,0,4], [2,4,0,0,4].
// In all the subarrays, the maximum element is equal to k = 4, so nums is now beautiful.
// It can be shown that nums cannot be made beautiful with fewer than 3 increment operations.
// Hence, the answer is 3.
//
// Constraints:
// 3 <= n == nums.length <= 105
// 	0 <= nums[i] <= 109
// 	0 <= k <= 109
//

long long minIncrementOperations(int* nums, int numsSize, int k) {
    long long increments = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] < k) {
            increments += (long long)(k - nums[i]);
        }
    }
    return increments;      
}
