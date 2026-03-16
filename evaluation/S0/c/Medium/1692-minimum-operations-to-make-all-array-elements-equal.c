// Source: https://leetcode.com/problems/minimum-operations-to-make-all-array-elements-equal/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array nums consisting of positive integers.
//
// You are also given an integer array queries of size m. For the ith query, you want to make all of the elements of nums equal to queries[i]. You can perform the following operation on the array any number of times:
//
//
// 	Increase or decrease an element of the array by 1.
//
//
// Return an array answer of size m where answer[i] is the minimum number of operations to make all elements of nums equal to queries[i].
//
// Note that after each query the array is reset to its original state.
//
// Example:
// Input: nums = [3,1,6,8], queries = [1,5]
// Output: [14,10]
// Explanation: For the first query we can do the following operations:
// - Decrease nums[0] 2 times, so that nums = [1,1,6,8].
// - Decrease nums[2] 5 times, so that nums = [1,1,1,8].
// - Decrease nums[3] 7 times, so that nums = [1,1,1,1].
// So the total number of operations for the first query is 2 + 5 + 7 = 14.
// For the second query we can do the following operations:
// - Increase nums[0] 2 times, so that nums = [5,1,6,8].
// - Increase nums[1] 4 times, so that nums = [5,5,6,8].
// - Decrease nums[2] 1 time, so that nums = [5,5,5,8].
// - Decrease nums[3] 3 times, so that nums = [5,5,5,5].
// So the total number of operations for the second query is 2 + 4 + 1 + 3 = 10.
//
// Constraints:
// n == nums.length
// 	m == queries.length
// 	1 <= n, m <= 105
// 	1 <= nums[i], queries[i] <= 109
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* minOperations(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize){
    // Sort nums
    qsort(nums, numsSize, sizeof(int), (int (*)(const void*, const void*)) (int (*)(int, int)) [](int a, int b) { return a - b; });

    // Precompute prefix sums
    long long* prefixSums = (long long*)malloc((numsSize + 1) * sizeof(long long));
    prefixSums[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefixSums[i + 1] = prefixSums[i] + nums[i];
    }

    // Prepare result array
    long long* result = (long long*)malloc(queriesSize * sizeof(long long));
    *returnSize = queriesSize;

    // Process each query
    for (int i = 0; i < queriesSize; i++) {
        int query = queries[i];

        // Binary search to find the partition index
        int left = 0, right = numsSize;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < query) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        int partitionIndex = left;

        // Calculate the total operations
        long long leftOperations = (long long)query * partitionIndex - prefixSums[partitionIndex];
        long long rightOperations = (prefixSums[numsSize] - prefixSums[partitionIndex]) - (long long)query * (numsSize - partitionIndex);
        result[i] = leftOperations + rightOperations;
    }

    free(prefixSums);
    return result;
}
