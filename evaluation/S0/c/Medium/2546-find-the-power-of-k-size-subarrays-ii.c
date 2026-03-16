// Source: https://leetcode.com/problems/find-the-power-of-k-size-subarrays-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of integers nums of length n and a positive integer k.
//
// The power of an array is defined as:
//
//
// 	Its maximum element if all of its elements are consecutive and sorted in ascending order.
// 	-1 otherwise.
//
//
// You need to find the power of all subarrays of nums of size k.
//
// Return an integer array results of size n - k + 1, where results[i] is the power of nums[i..(i + k - 1)].
//
// Example:
// Input: nums = [1,2,3,4,3,2,5], k = 3
//
// Output: [3,4,-1,-1,-1]
//
// Explanation:
//
// There are 5 subarrays of nums of size 3:
//
//
// 	[1, 2, 3] with the maximum element 3.
// 	[2, 3, 4] with the maximum element 4.
// 	[3, 4, 3] whose elements are not consecutive.
// 	[4, 3, 2] whose elements are not sorted.
// 	[3, 2, 5] whose elements are not consecutive.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 106
// 	1 <= k <= n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultsArray(int* nums, int numsSize, int k, int* returnSize) {
    int* result = (int*)malloc((numsSize - k + 1) * sizeof(int));
    *returnSize = numsSize - k + 1;

    for (int i = 0; i <= numsSize - k; i++) {
        int isConsecutive = 1;
        int maxElement = nums[i];

        for (int j = 1; j < k; j++) {
            if (nums[i + j] != nums[i + j - 1] + 1) {
                isConsecutive = 0;
                break;
            }
            if (nums[i + j] > maxElement) {
                maxElement = nums[i + j];
            }
        }

        if (isConsecutive) {
            result[i] = maxElement;
        } else {
            result[i] = -1;
        }
    }

    return result;      
}
