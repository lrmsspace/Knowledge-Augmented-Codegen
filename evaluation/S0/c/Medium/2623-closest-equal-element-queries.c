// Source: https://leetcode.com/problems/closest-equal-element-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a circular array nums and an array queries.
//
// For each query i, you have to find the following:
//
//
// 	The minimum distance between the element at index queries[i] and any other index j in the circular array, where nums[j] == nums[queries[i]]. If no such index exists, the answer for that query should be -1.
//
//
// Return an array answer of the same size as queries, where answer[i] represents the result for query i.
//
// Example:
// Input: nums = [1,3,1,4,1,3,2], queries = [0,3,5]
//
// Output: [2,-1,3]
//
// Explanation:
//
//
// 	Query 0: The element at queries[0] = 0 is nums[0] = 1. The nearest index with the same value is 2, and the distance between them is 2.
// 	Query 1: The element at queries[1] = 3 is nums[3] = 4. No other index contains 4, so the result is -1.
// 	Query 2: The element at queries[2] = 5 is nums[5] = 3. The nearest index with the same value is 1, and the distance between them is 3 (following the circular path: 5 -> 6 -> 0 -> 1).
//
// Constraints:
// 1 <= queries.length <= nums.length <= 105
// 	1 <= nums[i] <= 106
// 	0 <= queries[i] < nums.length
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* solveQueries(int* nums, int numsSize, int* queries, int queriesSize, int* returnSize) {
    int* result = (int*)malloc(queriesSize * sizeof(int));
    int* lastIndex = (int*)malloc(1000001 * sizeof(int));
    for (int i = 0; i <= 1000000; i++) {
        lastIndex[i] = -1;
    }

    for (int i = 0; i < queriesSize; i++) {
        int queryIndex = queries[i];
        int queryValue = nums[queryIndex];

        if (lastIndex[queryValue] == -1) {
            result[i] = -1;
        } else {
            int directDistance = abs(queryIndex - lastIndex[queryValue]);
            int circularDistance = numsSize - directDistance;
            result[i] = directDistance < circularDistance ? directDistance : circularDistance;
        }

        lastIndex[queryValue] = queryIndex;
    }

    free(lastIndex);
    *returnSize = queriesSize;
    return result;      
}
