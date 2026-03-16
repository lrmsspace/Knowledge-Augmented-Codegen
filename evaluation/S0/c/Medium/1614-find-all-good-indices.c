// Source: https://leetcode.com/problems/find-all-good-indices/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums of size n and a positive integer k.
//
// We call an index i in the range k <= i < n - k good if the following conditions are satisfied:
//
//
// 	The k elements that are just before the index i are in non-increasing order.
// 	The k elements that are just after the index i are in non-decreasing order.
//
//
// Return an array of all good indices sorted in increasing order.
//
// Example:
// Input: nums = [2,1,1,1,3,4,1], k = 2
// Output: [2,3]
// Explanation: There are two good indices in the array:
// - Index 2. The subarray [2,1] is in non-increasing order, and the subarray [1,3] is in non-decreasing order.
// - Index 3. The subarray [1,1] is in non-increasing order, and the subarray [3,4] is in non-decreasing order.
// Note that the index 4 is not good because [4,1] is not non-decreasing.
//
// Constraints:
// n == nums.length
// 	3 <= n <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= n / 2
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* goodIndices(int* nums, int numsSize, int k, int* returnSize) {
    int* result = (int*)malloc(numsSize * sizeof(int));
    *returnSize = 0;

    int* left = (int*)malloc(numsSize * sizeof(int));
    int* right = (int*)malloc(numsSize * sizeof(int));

    left[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] <= nums[i - 1]) {
            left[i] = left[i - 1] + 1;
        } else {
            left[i] = 1;
        }
    }

    right[numsSize - 1] = 1;
    for (int i = numsSize - 2; i >= 0; i--) {
        if (nums[i] <= nums[i + 1]) {
            right[i] = right[i + 1] + 1;
        } else {
            right[i] = 1;
        }
    }

    for (int i = k; i < numsSize - k; i++) {
        if (left[i - 1] >= k && right[i + 1] >= k) {
            result[(*returnSize)++] = i;
        }
    }

    free(left);
    free(right);

    return result;      
}
