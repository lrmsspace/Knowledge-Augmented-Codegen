// Source: https://leetcode.com/problems/largest-divisible-subset/   |   Difficulty: Medium
//
// Problem Description:
// Given a set of distinct positive integers nums, return the largest subset answer such that every pair (answer[i], answer[j]) of elements in this subset satisfies:
//
//
// 	answer[i] % answer[j] == 0, or
// 	answer[j] % answer[i] == 0
//
//
// If there are multiple solutions, return any of them.
//
// Example:
// Input: nums = [1,2,3]
// Output: [1,2]
// Explanation: [1,3] is also accepted.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= 2 * 109
// 	All the integers in nums are unique.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
    // Sort the input array
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    // dp[i] will hold the size of the largest divisible subset that ends with nums[i]
    int* dp = (int*)calloc(numsSize, sizeof(int));
    // prev[i] will hold the index of the previous element in the largest divisible subset ending with nums[i]
    int* prev = (int*)calloc(numsSize, sizeof(int));

    int maxSize = 0;
    int maxIndex = -1;

    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1; // Each number is a subset of size 1
        prev[i] = -1; // Initialize previous index

        for (int j = 0; j < i; j++) {
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                prev[i] = j;
            }
        }

        if (dp[i] > maxSize) {
            maxSize = dp[i];
            maxIndex = i;
        }
    }

    // Reconstruct the largest divisible subset
    int* result = (int*)malloc(maxSize * sizeof(int));
    int k = maxSize - 1;
    while (maxIndex != -1) {
        result[k--] = nums[maxIndex];
        maxIndex = prev[maxIndex];
    }

    *returnSize = maxSize;

    free(dp);
    free(prev);

    return result;      
}
