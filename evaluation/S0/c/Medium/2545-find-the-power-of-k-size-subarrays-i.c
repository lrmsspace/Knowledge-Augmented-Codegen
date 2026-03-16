// Source: https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/   |   Difficulty: Medium
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
// 1 <= n == nums.length <= 500
// 	1 <= nums[i] <= 105
// 	1 <= k <= n
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* resultsArray(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize - k + 1;
    int* result = (int*)malloc((*returnSize) * sizeof(int));
    for (int i = 0; i <= numsSize - k; i++) {
        int min = nums[i];
        int max = nums[i];
        int isConsecutive = 1;
        for (int j = i; j < i + k; j++) {
            if (nums[j] < min) min = nums[j];
            if (nums[j] > max) max = nums[j];
        }
        if (max - min + 1 != k) {
            isConsecutive = 0;
        } else {
            int* count = (int*)calloc(k, sizeof(int));
            for (int j = i; j < i + k; j++) {
                count[nums[j] - min]++;
                if (count[nums[j] - min] > 1) {
                    isConsecutive = 0;
                    break;
                }
            }
            free(count);
        }
        result[i] = isConsecutive ? max : -1;
    }
    return result;      
}
