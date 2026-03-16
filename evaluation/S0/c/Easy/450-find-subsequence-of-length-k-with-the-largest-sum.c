// Source: https://leetcode.com/problems/find-subsequence-of-length-k-with-the-largest-sum/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k. You want to find a subsequence of nums of length k that has the largest sum.
//
// Return any such subsequence as an integer array of length k.
//
// A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [2,1,3,3], k = 2
// Output: [3,3]
// Explanation:
// The subsequence has the largest sum of 3 + 3 = 6.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-105 <= nums[i] <= 105
// 	1 <= k <= nums.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maxSubsequence(int* nums, int numsSize, int k, int* returnSize) {
    int* result = (int*)malloc(k * sizeof(int));
    int* indices = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        indices[i] = i;
    }

    // Sort indices based on the values in nums in descending order
    qsort(indices, numsSize, sizeof(int), 
        (int (*)(const void*, const void*)) 
        [](const int* a, const int* b) {
            return nums[*b] - nums[*a];
        });

    // Select the top k indices
    int* selectedIndices = (int*)malloc(k * sizeof(int));
    for (int i = 0; i < k; i++) {
        selectedIndices[i] = indices[i];
    }

    // Sort the selected indices to maintain the original order
    qsort(selectedIndices, k, sizeof(int), 
        (int (*)(const void*, const void*)) 
        [](const int* a, const int* b) {
            return *a - *b;
        });

    // Build the result array
    for (int i = 0; i < k; i++) {
        result[i] = nums[selectedIndices[i]];
    }

    free(indices);
    free(selectedIndices);

    *returnSize = k;
    return result;      
}
